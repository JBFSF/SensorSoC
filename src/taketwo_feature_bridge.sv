`ifndef TAKETWO_FEATURE_BRIDGE_V_SOURCE
`define TAKETWO_FEATURE_BRIDGE_V_SOURCE

module taketwo_feature_bridge (
    input  logic        clk_i,
    input  logic        reset_i,

    output logic [31:0] axi_x_addr_o,
    output logic        maxi_awready_o,
    output logic        maxi_wready_o,
    output logic [1:0]  maxi_bresp_o,
    output logic        maxi_bvalid_o,
    input  logic        maxi_awvalid_i,
    input  logic [31:0] maxi_awaddr_i,
    input  logic        maxi_wvalid_i,
    input  logic [31:0] maxi_wdata_i,
    input  logic [3:0]  maxi_wstrb_i,
    input  logic        maxi_bready_i,

    output logic        tk_maxi_awready_o,
    output logic        tk_maxi_wready_o,
    output logic [1:0]  tk_maxi_bresp_o,
    output logic        tk_maxi_bvalid_o,
    input  logic        tk_maxi_awvalid_i,
    input  logic [31:0] tk_maxi_awaddr_i,
    input  logic [7:0]  tk_maxi_awlen_i,
    input  logic [2:0]  tk_maxi_awsize_i,
    input  logic [1:0]  tk_maxi_awburst_i,
    input  logic        tk_maxi_wvalid_i,
    input  logic [31:0] tk_maxi_wdata_i,
    input  logic [3:0]  tk_maxi_wstrb_i,
    input  logic        tk_maxi_wlast_i,
    input  logic        tk_maxi_bready_i,

    output logic        tk_maxi_arready_o,
    output logic [31:0] tk_maxi_rdata_o,
    output logic [1:0]  tk_maxi_rresp_o,
    output logic        tk_maxi_rlast_o,
    output logic        tk_maxi_rvalid_o,
    input  logic        tk_maxi_arvalid_i,
    input  logic [31:0] tk_maxi_araddr_i,
    input  logic [7:0]  tk_maxi_arlen_i,
    input  logic [2:0]  tk_maxi_arsize_i,
    input  logic [1:0]  tk_maxi_arburst_i,
    input  logic        tk_maxi_rready_i,

    output logic [3:0]  tk_saxi_awcache_o,
    output logic [2:0]  tk_saxi_awprot_o,
    output logic        tk_saxi_awvalid_o,
    input  logic        tk_saxi_awready_i,
    output logic [31:0] tk_saxi_awaddr_o,
    output logic [31:0] tk_saxi_wdata_o,
    output logic [3:0]  tk_saxi_wstrb_o,
    output logic        tk_saxi_wvalid_o,
    input  logic        tk_saxi_wready_i,
    input  logic [1:0]  tk_saxi_bresp_i,
    input  logic        tk_saxi_bvalid_i,
    output logic        tk_saxi_bready_o,
    output logic [3:0]  tk_saxi_arcache_o,
    output logic [2:0]  tk_saxi_arprot_o,
    output logic        tk_saxi_arvalid_o,
    output logic [31:0] tk_saxi_araddr_o,
    input  logic        tk_saxi_arready_i,
    input  logic [31:0] tk_saxi_rdata_i,
    input  logic [1:0]  tk_saxi_rresp_i,
    input  logic        tk_saxi_rvalid_i,
    output logic        tk_saxi_rready_o,

    input  logic        axi_done_i,
    output logic [31:0] feature_word0_o,
    output logic [31:0] feature_word1_o
);

    localparam logic [31:0] TK_X_WORD0_ADDR    = 32'h0000_0040;
    localparam logic [31:0] TK_X_WORD1_ADDR    = 32'h0000_0044;
    localparam logic [31:0] TK_START_REG_ADDR  = 32'd16;

    typedef enum logic [1:0] {
        TK_SAXI_IDLE,
        TK_SAXI_AW,
        TK_SAXI_W,
        TK_SAXI_B
    } tk_saxi_state_t;

    logic        axi_wr_active_r;
    logic [31:0] axi_wr_addr_r;
    logic        axi_bvalid_r;

    logic        tk_wr_active_r;
    logic [31:0] tk_wr_addr_r;
    logic [7:0]  tk_wr_beats_left_r;
    logic [2:0]  tk_wr_size_r;
    logic [1:0]  tk_wr_burst_r;
    logic        tk_bvalid_r;

    logic        tk_rd_active_r;
    logic [31:0] tk_rd_addr_r;
    logic [7:0]  tk_rd_beats_left_r;
    logic [2:0]  tk_rd_size_r;
    logic [1:0]  tk_rd_burst_r;
    logic [31:0] tk_rdata_r;
    logic        tk_rvalid_r;
    logic        tk_rlast_r;

    logic [31:0] feature_word0_r;
    logic [31:0] feature_word1_r;

    tk_saxi_state_t tk_saxi_state_r;

    logic [31:0] axi_word0_merged_w;
    logic [31:0] axi_word1_merged_w;
    logic [31:0] tk_word0_merged_w;
    logic [31:0] tk_word1_merged_w;

    assign axi_word0_merged_w = {
        maxi_wstrb_i[3] ? maxi_wdata_i[31:24] : feature_word0_r[31:24],
        maxi_wstrb_i[2] ? maxi_wdata_i[23:16] : feature_word0_r[23:16],
        maxi_wstrb_i[1] ? maxi_wdata_i[15:8]  : feature_word0_r[15:8],
        maxi_wstrb_i[0] ? maxi_wdata_i[7:0]   : feature_word0_r[7:0]
    };

    assign axi_word1_merged_w = {
        maxi_wstrb_i[3] ? maxi_wdata_i[31:24] : feature_word1_r[31:24],
        maxi_wstrb_i[2] ? maxi_wdata_i[23:16] : feature_word1_r[23:16],
        maxi_wstrb_i[1] ? maxi_wdata_i[15:8]  : feature_word1_r[15:8],
        maxi_wstrb_i[0] ? maxi_wdata_i[7:0]   : feature_word1_r[7:0]
    };

    assign tk_word0_merged_w = {
        tk_maxi_wstrb_i[3] ? tk_maxi_wdata_i[31:24] : feature_word0_r[31:24],
        tk_maxi_wstrb_i[2] ? tk_maxi_wdata_i[23:16] : feature_word0_r[23:16],
        tk_maxi_wstrb_i[1] ? tk_maxi_wdata_i[15:8]  : feature_word0_r[15:8],
        tk_maxi_wstrb_i[0] ? tk_maxi_wdata_i[7:0]   : feature_word0_r[7:0]
    };

    assign tk_word1_merged_w = {
        tk_maxi_wstrb_i[3] ? tk_maxi_wdata_i[31:24] : feature_word1_r[31:24],
        tk_maxi_wstrb_i[2] ? tk_maxi_wdata_i[23:16] : feature_word1_r[23:16],
        tk_maxi_wstrb_i[1] ? tk_maxi_wdata_i[15:8]  : feature_word1_r[15:8],
        tk_maxi_wstrb_i[0] ? tk_maxi_wdata_i[7:0]   : feature_word1_r[7:0]
    };

    assign axi_x_addr_o      = TK_X_WORD0_ADDR;
    assign maxi_awready_o    = ~reset_i;
    assign maxi_wready_o     = ~reset_i;
    assign maxi_bresp_o      = 2'b00;
    assign maxi_bvalid_o     = axi_bvalid_r;

    assign tk_maxi_awready_o = ~reset_i;
    assign tk_maxi_wready_o  = ~reset_i;
    assign tk_maxi_bresp_o   = 2'b00;
    assign tk_maxi_bvalid_o  = tk_bvalid_r;
    assign tk_maxi_arready_o = ~reset_i & ~tk_rd_active_r;
    assign tk_maxi_rdata_o   = tk_rdata_r;
    assign tk_maxi_rresp_o   = 2'b00;
    assign tk_maxi_rlast_o   = tk_rlast_r;
    assign tk_maxi_rvalid_o  = tk_rvalid_r;

    assign tk_saxi_awcache_o = 4'd0;
    assign tk_saxi_awprot_o  = 3'd0;
    assign tk_saxi_bready_o  = 1'b1;
    assign tk_saxi_arcache_o = 4'd0;
    assign tk_saxi_arprot_o  = 3'd0;
    assign tk_saxi_arvalid_o = 1'b0;
    assign tk_saxi_rready_o  = 1'b1;

    assign feature_word0_o   = feature_word0_r;
    assign feature_word1_o   = feature_word1_r;

    always_ff @(posedge clk_i) begin
        if (reset_i) begin
            axi_wr_active_r    <= 1'b0;
            axi_wr_addr_r      <= 32'd0;
            axi_bvalid_r       <= 1'b0;
            feature_word0_r    <= 32'd0;
            feature_word1_r    <= 32'd0;

            tk_wr_active_r     <= 1'b0;
            tk_wr_addr_r       <= 32'd0;
            tk_wr_beats_left_r <= 8'd0;
            tk_wr_size_r       <= 3'd0;
            tk_wr_burst_r      <= 2'd0;
            tk_bvalid_r        <= 1'b0;

            tk_rd_active_r     <= 1'b0;
            tk_rd_addr_r       <= 32'd0;
            tk_rd_beats_left_r <= 8'd0;
            tk_rd_size_r       <= 3'd0;
            tk_rd_burst_r      <= 2'd0;
            tk_rdata_r         <= 32'd0;
            tk_rvalid_r        <= 1'b0;
            tk_rlast_r         <= 1'b0;

            tk_saxi_state_r    <= TK_SAXI_IDLE;
            tk_saxi_awaddr_o   <= TK_START_REG_ADDR;
            tk_saxi_awvalid_o  <= 1'b0;
            tk_saxi_wdata_o    <= 32'd1;
            tk_saxi_wstrb_o    <= 4'hF;
            tk_saxi_wvalid_o   <= 1'b0;
            tk_saxi_araddr_o   <= 32'd0;
        end else begin
            if (axi_bvalid_r && maxi_bready_i)
                axi_bvalid_r <= 1'b0;

            if (!axi_wr_active_r && maxi_awvalid_i && maxi_awready_o) begin
                axi_wr_active_r <= 1'b1;
                axi_wr_addr_r   <= maxi_awaddr_i;
            end

            if (axi_wr_active_r && maxi_wvalid_i && maxi_wready_o) begin
                if (axi_wr_addr_r == TK_X_WORD0_ADDR)
                    feature_word0_r <= axi_word0_merged_w;
                if (axi_wr_addr_r == TK_X_WORD1_ADDR)
                    feature_word1_r <= axi_word1_merged_w;
                axi_wr_active_r <= 1'b0;
                axi_bvalid_r    <= 1'b1;
            end

            if (tk_bvalid_r && tk_maxi_bready_i)
                tk_bvalid_r <= 1'b0;

            if (!tk_wr_active_r && tk_maxi_awvalid_i && tk_maxi_awready_o) begin
                tk_wr_active_r     <= 1'b1;
                tk_wr_addr_r       <= tk_maxi_awaddr_i;
                tk_wr_beats_left_r <= tk_maxi_awlen_i + 8'd1;
                tk_wr_size_r       <= tk_maxi_awsize_i;
                tk_wr_burst_r      <= tk_maxi_awburst_i;
            end

            if (tk_wr_active_r && tk_maxi_wvalid_i && tk_maxi_wready_o) begin
                if (tk_wr_addr_r == TK_X_WORD0_ADDR)
                    feature_word0_r <= tk_word0_merged_w;
                if (tk_wr_addr_r == TK_X_WORD1_ADDR)
                    feature_word1_r <= tk_word1_merged_w;

                if ((tk_wr_beats_left_r == 8'd1) || tk_maxi_wlast_i) begin
                    tk_wr_active_r <= 1'b0;
                    tk_bvalid_r    <= 1'b1;
                end else begin
                    tk_wr_beats_left_r <= tk_wr_beats_left_r - 8'd1;
                    if (tk_wr_burst_r == 2'b01)
                        tk_wr_addr_r <= tk_wr_addr_r + (32'd1 << tk_wr_size_r);
                end
            end

            if (tk_rvalid_r && tk_maxi_rready_i) begin
                tk_rvalid_r <= 1'b0;
                tk_rlast_r  <= 1'b0;
            end

            if (!tk_rd_active_r && tk_maxi_arvalid_i && tk_maxi_arready_o) begin
                tk_rd_active_r     <= 1'b1;
                tk_rd_addr_r       <= tk_maxi_araddr_i;
                tk_rd_beats_left_r <= tk_maxi_arlen_i + 8'd1;
                tk_rd_size_r       <= tk_maxi_arsize_i;
                tk_rd_burst_r      <= tk_maxi_arburst_i;
            end

            if (tk_rd_active_r && (!tk_rvalid_r || tk_maxi_rready_i)) begin
                case (tk_rd_addr_r)
                    TK_X_WORD0_ADDR: tk_rdata_r <= feature_word0_r;
                    TK_X_WORD1_ADDR: tk_rdata_r <= feature_word1_r;
                    default:         tk_rdata_r <= 32'h0000_0000;
                endcase

                tk_rvalid_r <= 1'b1;
                tk_rlast_r  <= (tk_rd_beats_left_r == 8'd1);

                if (tk_rd_beats_left_r == 8'd1) begin
                    tk_rd_active_r <= 1'b0;
                end else begin
                    tk_rd_beats_left_r <= tk_rd_beats_left_r - 8'd1;
                    if (tk_rd_burst_r == 2'b01)
                        tk_rd_addr_r <= tk_rd_addr_r + (32'd1 << tk_rd_size_r);
                end
            end

            case (tk_saxi_state_r)
                TK_SAXI_IDLE: begin
                    tk_saxi_awaddr_o  <= TK_START_REG_ADDR;
                    tk_saxi_awvalid_o <= 1'b0;
                    tk_saxi_wdata_o   <= 32'd1;
                    tk_saxi_wstrb_o   <= 4'hF;
                    tk_saxi_wvalid_o  <= 1'b0;
                    if (axi_done_i)
                        tk_saxi_state_r <= TK_SAXI_AW;
                end

                TK_SAXI_AW: begin
                    tk_saxi_awvalid_o <= 1'b1;
                    tk_saxi_wvalid_o  <= 1'b1;
                    if (tk_saxi_awready_i) begin
                        tk_saxi_awvalid_o <= 1'b0;
                        tk_saxi_state_r   <= TK_SAXI_W;
                    end
                end

                TK_SAXI_W: begin
                    if (tk_saxi_wready_i) begin
                        tk_saxi_wvalid_o <= 1'b0;
                        tk_saxi_state_r  <= TK_SAXI_B;
                    end
                end

                TK_SAXI_B: begin
                    if (tk_saxi_bvalid_i)
                        tk_saxi_state_r <= TK_SAXI_IDLE;
                end

                default: tk_saxi_state_r <= TK_SAXI_IDLE;
            endcase
        end
    end

endmodule

`endif
