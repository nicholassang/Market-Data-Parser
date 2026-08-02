`timescale 1ns/1ps


module tb_top;


logic clk;

logic rst;


logic [63:0] packet;

logic valid;


logic [15:0] best_bid;

logic [15:0] best_ask;



top dut(

    .clk(clk),

    .rst(rst),

    .packet(packet),

    .valid(valid),

    .best_bid(best_bid),

    .best_ask(best_ask)

);




// 250MHz clock

always #2 clk = ~clk;



integer cycles;

integer packets_processed;

integer latency;

integer latency_start;

logic waiting;



always @(posedge clk)
begin


    cycles <= cycles + 1;



    if(valid)
    begin

        packets_processed <= packets_processed + 1;

        latency_start <= cycles;

        waiting <= 1;

    end



    if(waiting)
    begin

        if(best_bid != 0 ||
           best_ask != 16'hffff)
        begin

            latency <= cycles-latency_start;

            waiting <= 0;

        end

    end


end




task send_packet(

input logic [15:0] price,

input logic [15:0] quantity,

input logic side

);


begin


packet =
{
    quantity,
    price,
    side,
    31'b0
};


valid = 1;


@(posedge clk);


valid = 0;


end


endtask






initial
begin


clk = 0;

rst = 1;

valid = 0;

packet = 0;



cycles = 0;

packets_processed = 0;

waiting = 0;



#20;


rst = 0;



// Test orders


send_packet(
    16'd100,
    16'd50,
    1'b0
);



send_packet(
    16'd105,
    16'd20,
    1'b0
);



send_packet(
    16'd110,
    16'd30,
    1'b1
);




// Benchmark stream


for(integer i=0;i<1000;i=i+1)

begin


send_packet(

    16'(100+i),

    16'd10,

    i[0]

);


end




#20;



$display("======================");

$display(" FPGA BENCHMARK ");

$display("======================");



$display(
"Packets processed = %0d",
packets_processed
);



$display(
"Cycles = %0d",
cycles
);



$display(
"Packets/cycle = %f",
real'(packets_processed)/
real'(cycles)
);



$display(
"Throughput @250MHz = %f Mpps",
real'(packets_processed)*250.0/
real'(cycles)
);



$display(
"Latency = %0d cycles",
latency
);



$display(
"Latency = %0f ns",
latency*4.0
);



$display(
"Best Bid = %d",
best_bid
);



$display(
"Best Ask = %d",
best_ask
);



$finish;


end



endmodule