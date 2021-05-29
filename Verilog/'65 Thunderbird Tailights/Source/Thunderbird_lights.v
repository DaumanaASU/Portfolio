module Thunderbird_lights(input clk,
						  input reset,
						  input left, right,      
						  output la, lb, lc, ra, rb, rc);
						 
	reg	la;
	reg	lb;
	reg	lc;
	reg	ra;
	reg	rb;
	reg	rc;
	reg [5:0] light;
	assign {lc, lb, la, ra, rb, rc} = light;
	 
	parameter	off	= 6'b000000,
				1L	= 6'b001000,
				2L	= 6'b011000,
				3L	= 6'b111000,
				1R	= 6'b000100,
				2R	= 6'b000110,
				3R	= 6'b000111;
				
	always @ (posedge clk, posedge reset)
	begin
		if (reset) 
			light <= off;
		else
			case (light)
				off: 
					if (left)
						light <= 1L;
					else if (right)
						light <= 1R;
					else 
						light <= off;
				1L: 
					light <= 2L;
				2L: 
					light <= 3L;
				3L: 
					light <= off;
				1R: 
					light <= 2R;
				2R: 
					light <= 3R;
				3R:
					light <= off;
				default:;
			endcase
	end
endmodule
						 