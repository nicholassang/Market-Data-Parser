#pragma once

class Parser {
    public:
        Parser(
            RingBuffer<MarketPacket, 1024>& rb
        );

        void process();
    
    private:
        RingBuffer<MarketPacket, 1024>& ringBuffer;
};