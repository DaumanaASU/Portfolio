module timer(input logic clock,
			input logic reset,
			output logic flag);
		
	integer counter = 0;
	
	always @ (posedge clock, posedge reset)
	begin
		if (reset)
			counter <= 0;
			flag <= 0;
		else if (counter == 200000000)
			begin
				flag <= 1;
				counter <= 0;
			end
		else
			counter = counter+1;
	end
endmodule