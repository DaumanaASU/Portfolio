 `timescale 1ns / 1ps  

module top_tb;
	logic clock;
	logic reset;
	logic [3:0] Trans_Mem1_ADDRB;
	logic Trans_Mem1_RENB;
	logic [7:0] Trans_Mem1_DOUTB;
	logic [3:0] Trans_Mem2_ADDRB;
	logic Trans_Mem2_RENB;
	logic [7:0] Trans_Mem2_DOUTB;
	
	top UUT(
			clock,
			reset,
			Trans_Mem1_ADDRB,
			Trans_Mem1_RENB,
			Trans_Mem1_DOUTB,
			Trans_Mem2_ADDRB.
			Trans_Mem2_RENB.
			Trans_Mem2_DOUTB);
	
	clock = 1;
	parameter Time_Period = 10;                
	always 
		#(Time_Period/2) clock = ~clock;

	initial
	begin
	reset = 1;
	Trans_Mem1_RENB = 1;
	Trans_Mem2_RENB = 1;
	#200
	reset = 0;
		
	#250
	for (int i = 0; i<4; i++)
	begin
		#10
		Trans_Mem1_ADDRB = i;
		Trans_Mem2_ADDRB = i;
	end
	
	$finish;
end  

endmodule