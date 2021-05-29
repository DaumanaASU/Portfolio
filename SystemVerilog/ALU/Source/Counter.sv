module Counter (
		input logic clock,
		input logic reset,
		input logic CNT_EN,
		output logic [3:0] address
		);
		
	always @ (posedge clock)
	begin
		if (reset)
		begin
			address <= 4'b0;
		end
		else if (enable)
		begin
			address <= address + 1;
		end
	end
endmodule