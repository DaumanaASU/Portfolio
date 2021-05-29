module seven_segment_display_controller(input logic clock,
								input logic play_number,
								input logic rec_number,
								output logic[7:0] anode,
								output logic[6:0] cathode
								);
								
	integer counter = 28'd0;
	
	always @(posedge clock)
	begin
		if (counter == 28'd100000)
		begin
			anode = 8'b11111110;
			if (!play_number)
				begin	
				cathode = 7'b1111001;
				end
			else
				begin
				cathode = 7'b0100100;
				end
		end
		else if (counter == 28'd200000)
		begin
		    anode = 8'b11101111;
			if (!rec_number)
				begin
				cathode = 7'b1111001;
				end
			else
				begin
				cathode = 7'b0100100;
				end
			counter = 28'd0;
		end
		counter = counter + 28'd1;
		
	end

endmodule
