module Clock_Scaler(input clk,
					input reset,
					output scaled_clk);
		
	reg scaled_clk = 1'b0;
	integer counter = 0;
	
	always @ (posedge clk, posedge reset)
	begin
		if (reset)
			counter <= 0;
		else if (counter == 50000000)
			begin
				scaled_clk <= !scaled_clk;
				counter <= 0;
			end
		else
			counter = counter+1;
	end
endmodule