module ALU_8bit (
		input logic [3:0] mode,
		input logic [7:0] A,
		input logic [7:0] B,
		output logic [7:0] out
		);
		
	parameter S0  = 4'b0000;
			  S1  = 4'b0001;
			  S2  = 4'b0010;
			  S3  = 4'b0011;
			  S4  = 4'b0100;
			  S5  = 4'b0101;
			  S6  = 4'b0110;
			  S7  = 4'b0111;
			  S8  = 4'b1000;
			  S9  = 4'b1001;
			  S10 = 4'b1010;
			  S11 = 4'b1011;
			  S12 = 4'b1100;
			  S13 = 4'b1101;
			  S14 = 4'b1110;
			  S15 = 4'b1111;
			  
	always_comb
	begin
		case(mode)
			S0:	 out = A + B;
			S1:  out = A - B;
			S2:  out = A;
			S3:  out = B;
			S4:  out = &A;
			S5:  out = |A;
			S6:  out = !A;
			S7:  out = ~A;
			S8:  out = A & B;
			S9:  out = A | B;
			S10: out = A ^ B;
			S11: out = A <<< B[2:0];
			S12: out = A >>> B[2:0];
			S13: out = A + 1;
			S14: out = A - 1;
			S15: out = 0 - A;
			default: out = 0;
		endcase
	end
endmodule	