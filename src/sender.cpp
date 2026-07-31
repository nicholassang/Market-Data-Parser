#include <iostream>
#include <cstring>
#include <chrono>

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
    char buffer[1024];
    uint64_t sequence = 1;

    TradeMessage trade{};
    // Same Trade Message Sent mutiple times
    for(uint64_t i = 1; i < 2; i++) {
        header.length = sizeof(PacketHeader) + sizeof(TradeMessage); // Testing a trade UDP call
        header.messageType = 1;
        header.sequence = sequence++;
        header.timestamp = std::chrono::duration_cast<std::chrono::nanoseconds>(duration).count();
    
        memcpy(trade.symbol, "ABCD", 4);
        trade.price = 18500;
        trade.quantity = 100;
        
        memcpy(buffer, &header, sizeof(PacketHeader));
        memcpy(buffer + sizeof(PacketHeader), &trade, sizeof(TradeMessage));
        ssize_t sent = sendto(sockfd, buffer, header.length, 0, (sockaddr*)&addr, sizeof(addr));

        if (sent == -1) {
            perror("sendto");
        }
    }

    std::cout << "Sent trade packet" << "\n";

    QuoteMessage quote{};
    // Same Quote Message Sent mutiple times
    for(uint64_t i = 1; i < 2; i++) {
        header.length = sizeof(PacketHeader) + sizeof(QuoteMessage); // Testing a Quote UDP call
        header.messageType = 2;
        header.sequence = sequence++;
        header.timestamp = std::chrono::duration_cast<std::chrono::nanoseconds>(duration).count();
    
        memcpy(quote.symbol, "ABCD", 4);
        quote.bidPrice = 10000;
        quote.askPrice = 9850;
        
        memcpy(buffer, &header, sizeof(PacketHeader));
        memcpy(buffer + sizeof(PacketHeader), &quote, sizeof(QuoteMessage));
        ssize_t sent = sendto(sockfd, buffer, header.length, 0, (sockaddr*)&addr, sizeof(addr));

        if (sent == -1) {
            perror("sendto");
        }
    }

    std::cout << "Sent quote packet" << "\n";

    close(sockfd);
}