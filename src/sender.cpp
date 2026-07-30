#include <iostream>
#include <cstring>

#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>

#include "market_packet.hpp"


int main() {
    int sockfd = socket(AF_INET, SOCK_DGRAM, 0);

    sockaddr_in addr{};
    addr.sin_family = AF_INET;
    addr.sin_port = htons(9000);
    inet_pton(AF_INET, "127.0.0.1", &addr.sin_addr);

    PacketHeader header{};

    // Same Trade Message Sent mutiple times
    for(uint64_t i = 1; i < 30; i++) {
        header.length = sizeof(PacketHeader) + sizeof(TradeMessage); // Testing a trade UDP call
        header.messageType = 1;
        header.sequence = i;
    
        TradeMessage trade{};
        memcpy(trade.symbol, "ABCD", 4);
        trade.price = 18500;
        trade.quantity = 100;
    
        char buffer[1024];
    
        memcpy(buffer, &header, sizeof(PacketHeader));
        memcpy(buffer + sizeof(PacketHeader), &trade, sizeof(TradeMessage));
        sendto(sockfd, buffer, header.length, 0, (sockaddr*)&addr, sizeof(addr));
    }

    std::cout << "Sent trade packet" << "\n";

    close(sockfd);
}