Module Controller(
		input logic clock,
		input logic reset,
		input logic [21:0] Inst_Mem_Data,
		output logic [7:0] A,
		output logic [7:0] B,
		output logic [3:0] Mode,
		output logic Inst_Mem_CNT_EN,
		output logic Trans_Mem1_CNT_EN,
		output logic Trans_Mem1_WEN,
		output logic Trans_Mem2_CNT_EN,
		output logic Trans_Mem2_WEN
		);
		
	logic[1:0] Processor_ID;
	logic[1:0] State;
	logic[7:0] output;
	logic enable;
	
	Parameter ResetSt	= 2'b00001;
			  Fetch		= 2'b00010;
			  Execute	= 2'b00100;
			  Store		= 2'b01000;
			  Terminate = 2'b10000;
	
	always @(posedge clock)
	begin
	if (reset)
		State <= ResetSt;
	else
		case (State)
			ResetSt:
				begin
					A 					<= 8'b00000000;
					B					<= 8'b00000000;
					Mode 				<= 4'b0000;
					Inst_Mem_CNT_EN 	<= 0;
					Trans_Mem1_CNT_EN	<= 0;
					Trans_Mem1_WEN 		<= 0;
					Trans_Mem2_CNT_EN 	<= 0;
					Trans_Mem2_WEN 		<= 0;
					
					State <= Fetch;
				end
			Fetch:
				begin
					assign Processor_ID[1] = Inst_Mem_Data[21];
					assign Processor_ID[0] = Inst_Mem_Data[20];
					assign Mode[3]		   = Inst_Mem_Data[19];
					assign Mode[2]		   = Inst_Mem_Data[18];
					assign Mode[1]		   = Inst_Mem_Data[17];
					assign Mode[0]		   = Inst_Mem_Data[16];
					assign A[7]			   = Inst_Mem_Data[15];
					assign A[6]			   = Inst_Mem_Data[14];
					assign A[5]			   = Inst_Mem_Data[13];
					assign A[4]			   = Inst_Mem_Data[12];
					assign A[3]			   = Inst_Mem_Data[11];
					assign A[2]			   = Inst_Mem_Data[10];
					assign A[1]			   = Inst_Mem_Data[9];
					assign A[0]			   = Inst_Mem_Data[8];
					assign B[7]			   = Inst_Mem_Data[7];
					assign B[6]			   = Inst_Mem_Data[6];
					assign B[5]			   = Inst_Mem_Data[5];
					assign B[4]			   = Inst_Mem_Data[4];
					assign B[3]			   = Inst_Mem_Data[3];
					assign B[2]			   = Inst_Mem_Data[2];
					assign B[1]			   = Inst_Mem_Data[1];
					assign B[0]			   = Inst_Mem_Data[0];
					
					Inst_Mem_CNT_EN <= 1;
					State <= Execute;
				end
			Execute:
				begin
					State <= Store;
				end
			Store:
				begin
					case (Processor_ID)
						2'b00:
							State <= Terminate;
						2'b01:
							begin
								Trans_Mem1_CNT_EN <= 1;
								State <= ResetSt;
							end
						2'b10:
							begin
								Trans_Mem2_CNT_EN <= 1;
								State <= ResetSt;
							end
						2'b11;
							State <= Terminate;
						default:
							State <= ResetSt;
					endcase
				end
			Terminate:
				begin
					$finish;
				end
		endcase
	end
endmodule