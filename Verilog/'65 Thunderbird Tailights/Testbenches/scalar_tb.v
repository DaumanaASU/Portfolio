`timescale 1ns / 1ns

module scalar_tb;
	reg clk;
	reg reset;
	wire scaled_clk;
	
Clock_Scalar DUT (
	.clk(clk),
	.reset(reset),
	.scaled_clk(scaled_clk));
	
	initial
		clk = 0;
	always
		#5
		clk=~clk;
	initial
		begin
			#5
			reset = 1;
			#10
			reset = 0;
			#1000000; $finish;
		end
endmodule