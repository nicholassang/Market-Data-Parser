`timescale 1ns/1ps


module order_book(

    input logic clk,
    input logic rst,


    input logic valid,

    input logic [15:0] price,
    input logic [15:0] quantity,

    input logic side,


    output logic [15:0] best_bid,

    output logic [15:0] best_ask

);



logic [15:0] bids [0:1023];

logic [15:0] asks [0:1023];


integer i;



always_ff @(posedge clk)
begin


    if(rst)
    begin

        best_bid <= 0;

        best_ask <= 16'hffff;


        for(i=0;i<1024;i=i+1)
        begin

            bids[i] <= 0;

            asks[i] <= 0;

        end

    end



    else
    begin


        if(valid)
        begin


            if(side == 0)
            begin

                bids[price[9:0]] <= quantity;


                if(price > best_bid)
                begin
                    best_bid <= price;
                end

            end



            else
            begin

                asks[price[9:0]] <= quantity;


                if(price < best_ask)
                begin
                    best_ask <= price;
                end

            end


        end


    end


end



endmodule