module deserializer(
	input logic clock_i,
	input logic enable_i,

	output logic done_o,
	output logic [15:0] data_o,

	output logic pdm_clk_o,
	input logic pdm_data_i,
	output logic pdm_lrsel_o
);

logic [6:0]count = 7'd0;
logic [4:0]count2 = 5'd0;
//assign count2 = 5'd0;
logic [15:0]temp;
assign pdm_clk_o = 1'b0;
assign pdm_lrsel_o = 1'b0;


always_ff @ (posedge clock_i)
begin
	if(count == 7'd49)
	begin
	   count <= 7'd0;
	   pdm_clk_o <= ~pdm_clk_o;
	end
	else if(enable_i)
	begin
	   count <= count + 7'd1;
	end
end

always_ff @ (posedge pdm_clk_o)
begin
    if(enable_i && count2 <= 5'd15)
    begin
        temp[count2] <= pdm_data_i;
        count2 <= count2 + 5'd1;
    end
    else if(count2 > 5'd15)
    begin
        done_o <= 1'b1;
        count2 <= 5'd0;
        data_o <= {<<{temp}};
    end
end

always_ff @ (posedge pdm_clk_o)
begin
    if(done_o)
    begin
        done_o <= 1'b0;  
    end
end


endmodule

