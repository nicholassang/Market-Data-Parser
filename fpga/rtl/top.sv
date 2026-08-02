`timescale 1ns/1ps


module top(

input logic clk,

input logic rst,


input logic [63:0] packet,

input logic valid,


output logic [15:0] best_bid,

output logic [15:0] best_ask


);



logic parser_valid;


logic [15:0] price;

logic [15:0] quantity;

logic side;



packet_parser parser(

    .clk(clk),

    .rst(rst),

    .data_in(packet),

    .valid_in(valid),


    .valid_out(parser_valid),


    .price(price),

    .quantity(quantity),

    .side(side)

);




order_book book(

    .clk(clk),

    .rst(rst),


    .valid(parser_valid),


    .price(price),

    .quantity(quantity),

    .side(side),


    .best_bid(best_bid),

    .best_ask(best_ask)

);



endmodule