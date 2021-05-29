module synchronizer(input logic clock,
                    input logic in,
                    output logic out
    );
    
    logic ffout;
    
    always_ff @ (posedge clock)
    begin
        ffout <= in;
    end
    
    always_ff @ (posedge clock)
    begin
        out <= ffout;
    end
    
    
endmodule
