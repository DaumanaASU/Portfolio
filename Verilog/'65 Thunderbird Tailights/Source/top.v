module top(input clk,
		   input reset,
		   input left, right,
		   output la, lb, lc, ra, rb, rc);
		   
	wire	la;
	wire	lb;
	wire	lc;
	wire	ra;
	wire	rb;
	wire	rc;
	wire	scaled_clk;
	
	Clock_Scaler Clock_Scaler_0(
		.clk(clk),
		.reset(reset),
		.scaled_clk(scaled_clk));
	Thunderbird_lights Thunderbird_lights_0(
		.clk(scaled_clk),
		.reset(reset),
		.left(left),
		.right(right),
		.la(la),
		.lb(lb),
		.lc(lc),
		.ra(ra),
		.rb(rb),
		.rc(rc));
	
endmodule