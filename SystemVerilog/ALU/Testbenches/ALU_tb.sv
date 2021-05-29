 `timescale 1ns / 1ps  

module ALU_tb;
//Inputs
 reg[7:0] A;
 reg[7:0] B;
 reg[3:0] mode;

//Outputs
 wire[7:0] out;
 integer i;
 
 ALU_8Bit UUT(
            A,
			B,                 
            mode,
            out
     );
    initial begin
    // hold reset state for 100 ns.
      A = 8'h0A;
      B = 4'h02;
      mode = 4'h0;
      
      for (i=0;i<=15;i=i+1)
      begin
       mode = mode + 8'h01;
       #10;
      end;
      
      A = 8'hF6;
      B = 8'h0A;
      
    end
endmodule