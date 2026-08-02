`timescale 1ns/1ps

module packet_parser(

    input logic clk,
    input logic rst,

    input logic [63:0] data_in,
    input logic valid_in,

    output logic valid_out,

    output logic [15:0] price,
    output logic [15:0] quantity,
    output logic side

);


always_ff @(posedge clk)
begin

    if(rst)
    begin
        valid_out <= 0;
        price <= 0;
        quantity <= 0;
        side <= 0;
    end


    else
    begin

        valid_out <= 0;


        if(valid_in)
        begin

            /*
              Packet:

              [63:48] quantity
              [47:32] price
              [31]    side

            */


            quantity <= data_in[63:48];

            price <= data_in[47:32];

            side <= data_in[31];


            valid_out <= 1;

        end

    end

end


endmodule