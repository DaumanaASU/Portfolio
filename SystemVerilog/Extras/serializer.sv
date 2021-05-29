module serializer(
    input logic clock_i,  
    input logic enable_i,
    
    output logic done_o,
    input logic [15:0] data_i,
    
    output logic pdm_audio_o,
    output logic pdm_sdaudio_o
);


logic [6:0]count = 7'd0;
logic [4:0]count2 = 5'd0;
logic pdm_clk_o = 1'b0;
assign pdm_sdaudio_o = 1'b1;
assign pdm_audio_o = 1'b0;

always_ff @ (posedge clock_i)
begin
	if(count == 7'd49)
	begin
	   count <= 7'd0;
	   pdm_clk_o <= ~pdm_clk_o;
	end
	else if(enable_i)
	begin
	   count <= count + 7'd1;
	end
end

always_ff @ (posedge pdm_clk_o)
begin
    if(enable_i && count2 <= 5'd15)
    begin
        pdm_audio_o <= data_i[15 - count2];
        count2 <= count2 + 5'd1;
    end
    else if(count2 > 5'd15)
    begin
        done_o <= 1'b1;
        count2 <= 5'd0;
    end
end

always_ff @ (posedge pdm_clk_o)
begin
    if(done_o)
    begin
        done_o <= 1'b0;
    end
end

endmodule
