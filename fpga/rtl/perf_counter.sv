`timescale 1ns/1ps


module perf_counter(

    input logic clk,
    input logic rst,

    input logic packet_valid,

    output logic [63:0] cycles,
    output logic [63:0] packets


);


always_ff @(posedge clk)
begin

    if(rst)
    begin

        cycles <= 0;
        packets <= 0;

    end


    else
    begin

        cycles <= cycles + 1;


        if(packet_valid)
        begin

            packets <= packets + 1;

        end

    end


end


endmodule