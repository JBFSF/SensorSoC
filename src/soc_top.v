`timescale 1ns/1ps

module soc_top #(
    // SRAM: WORDS x 32-bit. Default 4 KB.
    parameter integer MEM_WORDS = 1024,

    // Firmware init file (one 32-bit word per line, hex).
    parameter FIRMWARE_HEX = "",

    // Weight RAM init file (one 32-bit word per line, hex).
    parameter WEIGHT_INIT_HEX = "",

    // Base addresses (MMIO region)
    parameter GPIO_BASE   = 32'h0300_0000,
    parameter PWR_BASE    = 32'h0300_1000,
    parameter TIMER_BASE  = 32'h0300_2000,
    parameter ML_BASE     = 32'h0300_3000,
    parameter IRQC_BASE   = 32'h0300_5000,
    parameter TEST_BASE   = 32'h0300_F000,
    parameter WEIGHT_BASE = 32'h0300_6000
)(
    input  wire        clk,        // always-on clock
    input  wire        resetn,     // active-low reset (always-on)
    input  wire        i2c_scl_i,
    inout  wire        i2c_sda_io,

    output wire [7:0]  gpio_out,   // good for LEDs in FPGA later

    // optional: expose for waveform/debug
    output wire        cpu_clk_o,
    output wire        cpu_awake_o
);

    //FSM - controlled (request) enable
    reg cpu_clk_en;
    //latched enable (updates only when clk is low)
    reg cpu_clk_en_lat;

    always @(negedge clk or negedge resetn) begin
        if (!resetn)
            cpu_clk_en_lat <= 1'b1;     // start awake
        else
            cpu_clk_en_lat <= cpu_clk_en;
    end

    wire cpu_clk = clk & cpu_clk_en_lat;

    assign cpu_clk_o   = cpu_clk;
    assign cpu_awake_o = cpu_clk_en_lat;

    // PicoRV32 bus
    wire        mem_valid;
    wire        mem_instr;
    wire        mem_ready;
    wire [31:0] mem_addr;
    wire [31:0] mem_wdata;
    wire [3:0]  mem_wstrb;
    wire [31:0] mem_rdata;
    wire trap;

    // IRQ wiring is provided by SoC IRQ controller.
    wire [31:0] irq;

    //Tweak these later when I add flash/XIP.
    localparam [31:0] STACKADDR      = 4*MEM_WORDS;
    localparam [31:0] PROGADDR_RESET = 32'h0000_0000;
    localparam [31:0] PROGADDR_IRQ   = 32'h0000_0010;

    picorv32 #(
        .STACKADDR(STACKADDR),
        .PROGADDR_RESET(PROGADDR_RESET),
        .PROGADDR_IRQ(PROGADDR_IRQ),
        .BARREL_SHIFTER(1),
        .COMPRESSED_ISA(1),
        .ENABLE_COUNTERS(1),
        .ENABLE_MUL(1),
        .ENABLE_DIV(1),
        .ENABLE_FAST_MUL(0),
        .ENABLE_IRQ(1),
        .ENABLE_IRQ_QREGS(1)
    ) cpu (
        .clk       (cpu_clk),
        .resetn    (resetn),
        .mem_valid (mem_valid),
        .mem_instr (mem_instr),
        .mem_ready (mem_ready),
        .mem_addr  (mem_addr),
        .mem_wdata (mem_wdata),
        .mem_wstrb (mem_wstrb),
        .mem_rdata (mem_rdata),
        .irq       (irq),
        .trap      (trap) 
    );

    wire bus_valid = mem_valid && cpu_clk_en_lat;
    wire sram_sel = bus_valid && (mem_addr < 4*MEM_WORDS);
    wire mmio_sel = bus_valid && (mem_addr[31:24] == 8'h03);
    wire invalid_sel = bus_valid && !sram_sel && !mmio_sel;

    // SRAM
    wire        sram_ready;
    wire [31:0] sram_rdata;

    simple_sram #(
        .WORDS(MEM_WORDS),
        .INIT_HEX(FIRMWARE_HEX)
    ) sram (
        .clk   (cpu_clk),
        .resetn(resetn),
        .valid (sram_sel),
        .ready (sram_ready),
        .wstrb (mem_wstrb),
        .addr  (mem_addr),
        .wdata (mem_wdata),
        .rdata (sram_rdata)
    );

    // MMIO blocks (always-on clock)
    // Put MMIO on always-on clk so it can wake CPU even if gated.
    // But the CPU accesses MMIO via cpu_clk domain signals.
    //
    // In this starter design:
    // - MMIO registers update on always-on clk using mem_valid/etc which
    //   only toggle when cpu_clk is running.
    // - Timer and ML stub run on always-on clk and can wake CPU.

    // GPIO MMIO (single register at GPIO_BASE)
    wire        gpio_ready;
    wire [31:0] gpio_rdata;

    gpio_mmio #(.BASE_ADDR(GPIO_BASE)) u_gpio (
        .clk      (clk),
        .resetn   (resetn),
        .mem_valid(mmio_sel),
        .mem_addr (mem_addr),
        .mem_wdata(mem_wdata),
        .mem_wstrb(mem_wstrb),
        .mem_ready(gpio_ready),
        .mem_rdata(gpio_rdata),
        .gpio_out (gpio_out)
    );

    // Timer wake block
    wire        timer_ready;
    wire [31:0] timer_rdata;
    wire        timer_event;

    timer_mmio #(.BASE_ADDR(TIMER_BASE)) u_timer (
        .clk      (clk),
        .resetn   (resetn),
        .mem_valid(mmio_sel),
        .mem_addr (mem_addr),
        .mem_wdata(mem_wdata),
        .mem_wstrb(mem_wstrb),
        .mem_ready(timer_ready),
        .mem_rdata(),
        .event_o  (timer_event),
        .rdata_o  (timer_rdata)
    );

    // ML AXI-Lite bridge + taketwo accelerator + weight RAM

    // AXI-Lite: ml_axil_bridge_mmio (master) → taketwo_wrap (slave)
    wire [31:0] ml_saxi_awaddr;
    wire [2:0]  ml_saxi_awprot;
    wire        ml_saxi_awvalid;
    wire        ml_saxi_awready;
    wire [31:0] ml_saxi_wdata;
    wire [3:0]  ml_saxi_wstrb;
    wire        ml_saxi_wvalid;
    wire        ml_saxi_wready;
    wire [1:0]  ml_saxi_bresp;
    wire        ml_saxi_bvalid;
    wire        ml_saxi_bready;
    wire [31:0] ml_saxi_araddr;
    wire [2:0]  ml_saxi_arprot;
    wire        ml_saxi_arvalid;
    wire        ml_saxi_arready;
    wire [31:0] ml_saxi_rdata;
    wire [1:0]  ml_saxi_rresp;
    wire        ml_saxi_rvalid;
    wire        ml_saxi_rready;

    // AXI4: taketwo_wrap (master) → weight_ram_axi (slave)
    wire [0:0]  wram_awid;
    wire [31:0] wram_awaddr;
    wire [7:0]  wram_awlen;
    wire [2:0]  wram_awsize;
    wire [1:0]  wram_awburst;
    wire [0:0]  wram_awlock;
    wire [3:0]  wram_awcache;
    wire [2:0]  wram_awprot;
    wire [3:0]  wram_awqos;
    wire [1:0]  wram_awuser;
    wire        wram_awvalid;
    wire        wram_awready;
    wire [31:0] wram_wdata;
    wire [3:0]  wram_wstrb;
    wire        wram_wlast;
    wire        wram_wvalid;
    wire        wram_wready;
    wire [0:0]  wram_bid;
    wire [1:0]  wram_bresp;
    wire        wram_bvalid;
    wire        wram_bready;
    wire [0:0]  wram_arid;
    wire [31:0] wram_araddr;
    wire [7:0]  wram_arlen;
    wire [2:0]  wram_arsize;
    wire [1:0]  wram_arburst;
    wire [0:0]  wram_arlock;
    wire [3:0]  wram_arcache;
    wire [2:0]  wram_arprot;
    wire [3:0]  wram_arqos;
    wire [1:0]  wram_aruser;
    wire        wram_arvalid;
    wire        wram_arready;
    wire [0:0]  wram_rid;
    wire [31:0] wram_rdata;
    wire [1:0]  wram_rresp;
    wire        wram_rlast;
    wire        wram_rvalid;
    wire        wram_rready;

    wire        ml_irq;   // taketwo inference-done interrupt
    wire signed [15:0] ml_dbg_logit0;
    wire signed [15:0] ml_dbg_logit1;
    wire        ml_ready;
    wire [31:0] ml_rdata;
    wire        test_ready;
    wire [31:0] test_rdata;
    wire [31:0] test_status, test_code;
    wire [31:0] ml_score_hw;  // ML confidence score: test_mmio.score_o → host_i2c_bridge_regs.ml_score_i

    ml_axil_bridge_mmio #(.BASE_ADDR(ML_BASE)) u_ml (
        .clk         (clk),
        .resetn      (resetn),
        .en_i        (1'b1),
        .mem_valid   (mmio_sel),
        .mem_addr    (mem_addr),
        .mem_wdata   (mem_wdata),
        .mem_wstrb   (mem_wstrb),
        .mem_ready   (ml_ready),
        .mem_rdata   (ml_rdata),
        .event_o     (),
        .score_o     (),
        .saxi_awaddr (ml_saxi_awaddr),
        .saxi_awprot (ml_saxi_awprot),
        .saxi_awvalid(ml_saxi_awvalid),
        .saxi_awready(ml_saxi_awready),
        .saxi_wdata  (ml_saxi_wdata),
        .saxi_wstrb  (ml_saxi_wstrb),
        .saxi_wvalid (ml_saxi_wvalid),
        .saxi_wready (ml_saxi_wready),
        .saxi_bresp  (ml_saxi_bresp),
        .saxi_bvalid (ml_saxi_bvalid),
        .saxi_bready (ml_saxi_bready),
        .saxi_araddr (ml_saxi_araddr),
        .saxi_arprot (ml_saxi_arprot),
        .saxi_arvalid(ml_saxi_arvalid),
        .saxi_arready(ml_saxi_arready),
        .saxi_rdata  (ml_saxi_rdata),
        .saxi_rresp  (ml_saxi_rresp),
        .saxi_rvalid (ml_saxi_rvalid),
        .saxi_rready (ml_saxi_rready)
    );

    taketwo_wrap u_taketwo (
        .CLK        (clk),
        .RESETN     (resetn),
        .irq        (ml_irq),
        .dbg_logit0 (ml_dbg_logit0),
        .dbg_logit1 (ml_dbg_logit1),
        // AXI4 master → weight RAM
        .maxi_awid   (wram_awid),
        .maxi_awaddr (wram_awaddr),
        .maxi_awlen  (wram_awlen),
        .maxi_awsize (wram_awsize),
        .maxi_awburst(wram_awburst),
        .maxi_awlock (wram_awlock),
        .maxi_awcache(wram_awcache),
        .maxi_awprot (wram_awprot),
        .maxi_awqos  (wram_awqos),
        .maxi_awuser (wram_awuser),
        .maxi_awvalid(wram_awvalid),
        .maxi_awready(wram_awready),
        .maxi_wdata  (wram_wdata),
        .maxi_wstrb  (wram_wstrb),
        .maxi_wlast  (wram_wlast),
        .maxi_wvalid (wram_wvalid),
        .maxi_wready (wram_wready),
        .maxi_bid    (wram_bid),
        .maxi_bresp  (wram_bresp),
        .maxi_bvalid (wram_bvalid),
        .maxi_bready (wram_bready),
        .maxi_arid   (wram_arid),
        .maxi_araddr (wram_araddr),
        .maxi_arlen  (wram_arlen),
        .maxi_arsize (wram_arsize),
        .maxi_arburst(wram_arburst),
        .maxi_arlock (wram_arlock),
        .maxi_arcache(wram_arcache),
        .maxi_arprot (wram_arprot),
        .maxi_arqos  (wram_arqos),
        .maxi_aruser (wram_aruser),
        .maxi_arvalid(wram_arvalid),
        .maxi_arready(wram_arready),
        .maxi_rid    (wram_rid),
        .maxi_rdata  (wram_rdata),
        .maxi_rresp  (wram_rresp),
        .maxi_rlast  (wram_rlast),
        .maxi_rvalid (wram_rvalid),
        .maxi_rready (wram_rready),
        // AXI-Lite slave ← bridge
        .saxi_awaddr (ml_saxi_awaddr),
        .saxi_awprot (ml_saxi_awprot),
        .saxi_awvalid(ml_saxi_awvalid),
        .saxi_awready(ml_saxi_awready),
        .saxi_wdata  (ml_saxi_wdata),
        .saxi_wstrb  (ml_saxi_wstrb),
        .saxi_wvalid (ml_saxi_wvalid),
        .saxi_wready (ml_saxi_wready),
        .saxi_bresp  (ml_saxi_bresp),
        .saxi_bvalid (ml_saxi_bvalid),
        .saxi_bready (ml_saxi_bready),
        .saxi_araddr (ml_saxi_araddr),
        .saxi_arprot (ml_saxi_arprot),
        .saxi_arvalid(ml_saxi_arvalid),
        .saxi_arready(ml_saxi_arready),
        .saxi_rdata  (ml_saxi_rdata),
        .saxi_rresp  (ml_saxi_rresp),
        .saxi_rvalid (ml_saxi_rvalid),
        .saxi_rready (ml_saxi_rready)
    );

    wire        weight_ready;
    wire [31:0] weight_rdata;

    weight_ram_axi #(
        .WORDS          (4096),
        .BASE_ADDR      (WEIGHT_BASE),
        .WEIGHT_INIT_HEX(WEIGHT_INIT_HEX)
    ) u_weight_ram (
        .clk         (clk),
        .resetn      (resetn),
        // CPU MMIO
        .mem_valid   (mmio_sel),
        .mem_addr    (mem_addr),
        .mem_wdata   (mem_wdata),
        .mem_wstrb   (mem_wstrb),
        .mem_ready   (weight_ready),
        .mem_rdata   (weight_rdata),
        // AXI4 slave ← taketwo maxi_*
        .saxi_awid   (wram_awid),
        .saxi_awaddr (wram_awaddr),
        .saxi_awlen  (wram_awlen),
        .saxi_awsize (wram_awsize),
        .saxi_awburst(wram_awburst),
        .saxi_awlock (wram_awlock),
        .saxi_awcache(wram_awcache),
        .saxi_awprot (wram_awprot),
        .saxi_awqos  (wram_awqos),
        .saxi_awuser (wram_awuser),
        .saxi_awvalid(wram_awvalid),
        .saxi_awready(wram_awready),
        .saxi_wdata  (wram_wdata),
        .saxi_wstrb  (wram_wstrb),
        .saxi_wlast  (wram_wlast),
        .saxi_wvalid (wram_wvalid),
        .saxi_wready (wram_wready),
        .saxi_bid    (wram_bid),
        .saxi_bresp  (wram_bresp),
        .saxi_bvalid (wram_bvalid),
        .saxi_bready (wram_bready),
        .saxi_arid   (wram_arid),
        .saxi_araddr (wram_araddr),
        .saxi_arlen  (wram_arlen),
        .saxi_arsize (wram_arsize),
        .saxi_arburst(wram_arburst),
        .saxi_arlock (wram_arlock),
        .saxi_arcache(wram_arcache),
        .saxi_arprot (wram_arprot),
        .saxi_arqos  (wram_arqos),
        .saxi_aruser (wram_aruser),
        .saxi_arvalid(wram_arvalid),
        .saxi_arready(wram_arready),
        .saxi_rid    (wram_rid),
        .saxi_rdata  (wram_rdata),
        .saxi_rresp  (wram_rresp),
        .saxi_rlast  (wram_rlast),
        .saxi_rvalid (wram_rvalid),
        .saxi_rready (wram_rready)
    );

    // Off-chip host I2C target bridge (always-on domain)
    wire        host_i2c_wr_en;
    wire [7:0]  host_i2c_wr_addr;
    wire [7:0]  host_i2c_wr_data;
    wire [7:0]  host_i2c_rd_addr;
    wire [7:0]  host_i2c_rd_data;
    wire        host_i2c_proto_err;
    wire        host_i2c_irq_event;
    wire        host_i2c_irqc_req;
    wire        host_i2c_irqc_we;
    wire [7:0]  host_i2c_irqc_off;
    wire [31:0] host_i2c_irqc_wdata;
    wire        host_i2c_irqc_ready;
    wire [31:0] host_i2c_irqc_rdata;
    wire [31:0] host_cfg_target_wake_sec;
    wire [31:0] host_cfg_window_sec;
    wire [15:0] host_cfg_step_sec;
    wire [15:0] host_cfg_motion_hi_th;
    wire [7:0]  host_cfg_motion_hi_count;
    wire [7:0]  host_cfg_policy;
    wire [15:0] host_cfg_conf_thr;

    host_i2c_target #(
        .SLAVE_ADDR(7'h42)
    ) u_host_i2c_target (
        .clk       (clk),
        .resetn    (resetn),
        .i2c_scl_i (i2c_scl_i),
        .i2c_sda_io(i2c_sda_io),
        .wr_en_o   (host_i2c_wr_en),
        .wr_addr_o (host_i2c_wr_addr),
        .wr_data_o (host_i2c_wr_data),
        .rd_addr_o (host_i2c_rd_addr),
        .rd_data_i (host_i2c_rd_data),
        .proto_err_o(host_i2c_proto_err)
    );

    host_i2c_bridge_regs u_host_i2c_bridge_regs (
        .clk       (clk),
        .resetn    (resetn),
        .wr_en_i   (host_i2c_wr_en),
        .wr_addr_i (host_i2c_wr_addr),
        .wr_data_i (host_i2c_wr_data),
        .rd_addr_i (host_i2c_rd_addr),
        .rd_data_o (host_i2c_rd_data),
        .proto_err_i(host_i2c_proto_err),
        .ml_score_i(ml_score_hw),
        .event_o   (host_i2c_irq_event),
        .cfg_target_wake_sec_o(host_cfg_target_wake_sec),
        .cfg_window_sec_o(host_cfg_window_sec),
        .cfg_step_sec_o(host_cfg_step_sec),
        .cfg_motion_hi_th_o(host_cfg_motion_hi_th),
        .cfg_motion_hi_count_o(host_cfg_motion_hi_count),
        .cfg_policy_o(host_cfg_policy),
        .cfg_conf_thr_o(host_cfg_conf_thr),
        .irqc_req_o(host_i2c_irqc_req),
        .irqc_we_o (host_i2c_irqc_we),
        .irqc_off_o(host_i2c_irqc_off),
        .irqc_wdata_o(host_i2c_irqc_wdata),
        .irqc_ready_i(host_i2c_irqc_ready),
        .irqc_rdata_i(host_i2c_irqc_rdata)
    );

    // IRQ controller: pending/mask/wake filtering + MMIO visibility.
    wire        irqc_ready;
    wire [31:0] irqc_rdata;
    wire        irqc_wake_req;
    wire [31:0] irq_sources = {29'b0, host_i2c_irq_event, ml_irq, timer_event};

    irq_ctrl_mmio #(.BASE_ADDR(IRQC_BASE)) u_irqc (
        .clk      (clk),
        .resetn   (resetn),
        .mem_valid(mmio_sel),
        .mem_addr (mem_addr),
        .mem_wdata(mem_wdata),
        .mem_wstrb(mem_wstrb),
        .mem_ready(irqc_ready),
        .mem_rdata(irqc_rdata),
        .host_req_i(host_i2c_irqc_req),
        .host_we_i(host_i2c_irqc_we),
        .host_off_i(host_i2c_irqc_off),
        .host_wdata_i(host_i2c_irqc_wdata),
        .host_ready_o(host_i2c_irqc_ready),
        .host_rdata_o(host_i2c_irqc_rdata),
        .irq_src_i(irq_sources),
        .irq_o    (irq),
        .wake_req_o(irqc_wake_req)
    );

    // Power controller MMIO: sleep request + wake status/reason
    wire        pwr_ready;
    wire [31:0] pwr_rdata;
    wire        sleep_req;

    // Wake sources (always-on)
    wire [31:0] wake_sources;
    assign wake_sources = irq_sources;

    pwrctrl_mmio #(.BASE_ADDR(PWR_BASE)) u_pwr (
        .clk        (clk),
        .resetn     (resetn),
        .mem_valid  (mmio_sel),
        .mem_addr   (mem_addr),
        .mem_wdata  (mem_wdata),
        .mem_wstrb  (mem_wstrb),
        .mem_ready  (pwr_ready),
        .mem_rdata  (pwr_rdata),
        .sleep_req_o(sleep_req),
        .wake_src_i (wake_sources),
        .cpu_awake_i(cpu_clk_en_lat)
    );

    test_mmio #(.BASE_ADDR(TEST_BASE)) u_test (
        .clk(clk), .resetn(resetn),
        .mem_valid(mmio_sel),
        .mem_addr(mem_addr),
        .mem_wdata(mem_wdata),
        .mem_wstrb(mem_wstrb),
        .cfg_target_wake_sec_i(host_cfg_target_wake_sec),
        .cfg_window_sec_i(host_cfg_window_sec),
        .cfg_step_sec_i(host_cfg_step_sec),
        .cfg_motion_hi_th_i(host_cfg_motion_hi_th),
        .cfg_motion_hi_count_i(host_cfg_motion_hi_count),
        .cfg_policy_i(host_cfg_policy),
        .cfg_conf_thr_i(host_cfg_conf_thr),
        .mem_ready(test_ready),
        .mem_rdata(test_rdata),
        .status_o(test_status),
        .code_o(test_code),
        .score_o(ml_score_hw)
    );




    // MMIO bus response mux (to PicoRV32)
    wire mmio_ready = gpio_ready | pwr_ready | timer_ready | ml_ready | weight_ready | irqc_ready | test_ready;

    wire [31:0] mmio_rdata =
        gpio_ready   ? gpio_rdata   :
        pwr_ready    ? pwr_rdata    :
        timer_ready  ? timer_rdata  :
        ml_ready     ? ml_rdata     :
        weight_ready ? weight_rdata :
        irqc_ready   ? irqc_rdata   :
        test_ready   ? test_rdata   :
        32'h0000_0000;

    // Overall ready/data to CPU
    assign mem_ready = sram_ready | mmio_ready | invalid_sel;
    assign mem_rdata = sram_ready ? sram_rdata :
                       mmio_ready ? mmio_rdata :
                       32'h0000_0000;

// --------------------------------------
// Sleep / wake state machine (always-on)
// --------------------------------------
reg sleeping;
reg cpu_idle_seen;

reg [31:0] wake_sources_d;

always @(posedge clk) begin
  if (!resetn)
    wake_sources_d <= 32'h0;
  else
    wake_sources_d <= wake_sources;
end

wire [31:0] wake_rise  = wake_sources & ~wake_sources_d;
wire        wake_event = |wake_rise;   // 1-cycle pulse


always @(posedge clk) begin
  if (!resetn) begin
    cpu_clk_en     <= 1'b1;  // start awake
    sleeping       <= 1'b0;
    cpu_idle_seen  <= 1'b0;
  end else begin
    // Track whether we've observed the CPU idle at least once while awake
    if (cpu_clk_en) begin
      cpu_idle_seen <= cpu_idle_seen | (~mem_valid);
    end

    if (sleeping) begin
      // Wake has highest priority when sleeping.
      if (irqc_wake_req || wake_event) begin
        cpu_clk_en    <= 1'b1;
        sleeping      <= 1'b0;
        cpu_idle_seen <= 1'b0; // require a fresh idle observation before sleeping again
      end
    end else begin
      // Only sleep when:
      //  - firmware requested it
      //  - we've observed at least one idle cycle (prevents mid-transaction gating)
      //  - no wake event pending
      if (sleep_req && cpu_idle_seen && !(irqc_wake_req || wake_event)) begin
        cpu_clk_en    <= 1'b0;
        sleeping      <= 1'b1;
        cpu_idle_seen <= 1'b0;
      end
    end
  end
end
endmodule
