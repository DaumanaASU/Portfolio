module top(
		input logic clock,
		input logic reset,
		input logic [3:0] Trans_Mem1_ADDRB,
		input logic Trans_Mem1_RENB,
		output logic [7:0] Trans_Mem1_DOUTB,
		input logic [3:0] Trans_Mem2_ADDRB,
		input logic Trans_Mem2_RENB,
		output logic [7:0] Trans_Mem2_DOUTB
		);

	logic [21:0] Inst_Mem_Data;
	logic [7:0] A;
	logic [7:0] B;
	logic [3:0] mode;
	logic [7:0] out;
	logic Inst_Mem_CNT_EN;
	logic [3:0] Inst_Mem_ADDRA;
	logic Trans_Mem1_CNT_EN;
	logic Trans_Mem1_WEN;
	logic Trans_Mem1_ADDRA;
	logic Trans_Mem2_CNT_EN;
	logic Trans_Mem2_WEN;
	logic Trans_Mem2_ADDRA;
	
	blk_mem_gen_0 inMem(
				clock,
				1'b1,
				1'b0,
				Inst_Mem_ADDRA,
				22'd0,
				Inst_Mem_Data)
				
	blk_mem_gen_1 TM1(
				clock,
				1'b1,
				Trans_Mem1_WEN,
				Trans_Mem1_ADDRA,
				out,
				clock,
				Trans_Mem1_RENB,
				Trans_Mem1_ADDRB,
				Trans_Mem1_DOUTB);
				
	blk_mem_gen_1 TM2(
				clock,
				1'b1,
				Trans_Mem2_WEN,
				Trans_Mem1_ADDRA,
				out,
				clock,
				Trans_Mem2_RENB,
				Trans_Mem2_ADDRB,
				Trans_Mem2_DOUTB);
								
	
	Controller ctrl0(
				clock,
				reset,
				Inst_Mem_Data,
				A,
				B,
				mode,
				Inst_Mem_CNT_EN,
				Trans_Mem1_CNT_EN,
				Trans_Mem1_WEN,
				Trans_Mem2_CNT_EN,
				Trans_Mem2_WEN);
				
	Counter counter0(
				clock,
				reset,
				Inst_Mem_CNT_EN,
				Inst_Mem_ADDRA);
				
	Counter counter1(
				clock,
				reset,
				Trans_Mem1_CNT_EN,
				Trans_Mem1_ADDRA);
				
	Counter counter2(
				clock,
				reset,
				Trans_Mem2_CNT_EN,
				Trans_Mem2_ADDRA);
				
	ALU_8bit alu0(mode, A, B, out);
	
	
endmodule