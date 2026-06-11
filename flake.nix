{
  nixConfig = {
    extra-substituters = [
      "https://nix-cache.fossi-foundation.org"
    ];
    extra-trusted-public-keys = [
      "nix-cache.fossi-foundation.org:3+K59iFwXqKsL7BNu6Guy0v+uTlwsxYQxjspXzqLYQs="
    ];
  };

  inputs = {
    librelane.url = "github:librelane/librelane/3.0.0";
  };

  outputs =
    {
      self,
      librelane,
      ...
    }:
    let
      nix-eda = librelane.inputs.nix-eda;
      devshell = librelane.inputs.devshell;
      nixpkgs = nix-eda.inputs.nixpkgs;
      lib = nixpkgs.lib;
    in
    {
      # Outputs
      legacyPackages = nix-eda.forAllSystems (
        system:
        import nixpkgs {
          inherit system;
          overlays = [
            nix-eda.overlays.default
            devshell.overlays.default
            librelane.overlays.default
          ];
        }
      );

      packages = nix-eda.forAllSystems (system: {
        inherit (self.legacyPackages.${system}.python3.pkgs) ;
      });

      devShells = nix-eda.forAllSystems (
        system:
        let
          pkgs = (self.legacyPackages.${system});
          callPackage = lib.callPackageWith pkgs;
          cocotbext-i2c = pkgs.python3.pkgs.buildPythonPackage rec {
            pname = "cocotbext-i2c";
            version = "0.1.2";
            format = "wheel";
            src = pkgs.fetchurl {
              url = "https://files.pythonhosted.org/packages/d2/21/5e1d2b2b1b30431bec7461df6ccc267fb447629f780ea196b92f1c8b3f50/cocotbext_i2c-${version}-py3-none-any.whl";
              hash = "sha256-1Q0cX4bAhBv6NFbQ3mcAurnOsdJsnmct/WN+ArxPhOI=";
            };
            propagatedBuildInputs = with pkgs.python3.pkgs; [ cocotb ];
            doCheck = false;
          };
          cocotbext-axi = pkgs.python3.pkgs.buildPythonPackage rec {
            pname = "cocotbext-axi";
            version = "0.1.28";
            format = "wheel";
            src = pkgs.fetchurl {
              url = "https://files.pythonhosted.org/packages/29/eb/d1c1f727a52ef2b7d0a2e4ff31817add1ccd42155642ba971b49d9ee089c/cocotbext_axi-${version}-py3-none-any.whl";
              hash = "sha256-r/iLUocz5OWTWfBrjMMFJMx1vzHulR7YpXNpSyaBbrI=";
            };
            propagatedBuildInputs = with pkgs.python3.pkgs; [ cocotb numpy ];
            doCheck = false;
          };
        in
        {
          default = pkgs.librelane-shell.override ({
            extra-packages = with pkgs; [
              # Utilities
              gnumake
              gnugrep
              gawk

              # Simulation
              iverilog
              verilator

              # Waveform viewing
              gtkwave
              surfer
            ];

            extra-python-packages =
              ps: with ps; [
                # Verification
                cocotb
                cocotbext-i2c
                cocotbext-axi

                # For KLayout Python DRC runner
                docopt

                # For logo generation
                pillow
              ];
          });
        }
      );
    };
}
