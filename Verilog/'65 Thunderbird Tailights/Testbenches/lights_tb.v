`timescale 1ms / 1ms

module lights_tb;
	reg		clk;
	reg		reset;
	reg		left;
	reg		right;
	wire	la;
	wire	lb;
	wire	lc;
	wire	ra;
	wire	rb;
	wire	rc;
	
Thunderbird_lights DUT(
	.clk(clk),
	.reset(reset),
	.left(left),
	.right(right),
	.la(la),
	.lb(lb),
	.lc(lc),
	.ra(ra),
	.rb(rb),
	.rc(rc));
	
	initial
	clk = 0;
	always
	#5
	clk = ~clk;

	initial
	begin
		reset = 1;
		left = 0;
		right = 0;
		
		#10
		reset = 0;
		
		#10
		left = 1;
		
		#10
		left = 0;
		
		#25
		
		#10
		right = 1;
		
		#10 
		right = 0;
		
		#25
		#25
		left = 1;
		#25
		left = 0;
		
		#25
		#25
		right = 1;
		#25
		right = 1;
		$finish;
	end
endmodule
		