#include "udp_receiver.hpp"
#include "market_packet.hpp"

#include <iostream>
#include <cstring>

#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>


UDPReceiver::UDPReceiver(int port) {
    // AF_INET uses Ipv4, SOCK_DGRAM specifics UDP
    sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    sockaddr_in addr{};
    addr.sin_family = AF_INET;
    addr.sin_port = htons(port);
    addr.sin_addr.s_addr = INADDR_ANY;

    bind(sockfd, (sockaddr*)&addr, sizeof(addr));
}


UDPReceiver::~UDPReceiver() {
    close(sockfd);
}


void UDPReceiver::receive() {
    char buffer[1024];
    std::cout << "Waiting..." << "\n";
    while(true) {
        int bytes = recvfrom(sockfd, buffer, sizeof(buffer), 0, nullptr, nullptr);
        std::cout << "Received " << bytes << " bytes\n";
        if (bytes < sizeof(PacketHeader)) continue;

        auto* header = reinterpret_cast<PacketHeader*>(buffer);
        std::cout << "Length: " << header->length << "\n";
        std::cout << "Type: " << (int)header->messageType << "\n";
        std::cout << "Sequence: " << header->sequence << "\n";

        switch (header->messageType) {
            case 1: {
                auto* trade = reinterpret_cast<TradeMessage*>(buffer + sizeof(PacketHeader));
                if (bytes < sizeof(PacketHeader) + sizeof(TradeMessage)) continue;
                std::cout<< "Symbol: "; std::cout.write(trade->symbol, 8); std::cout<<"\n"; // symbol is char array string, may not contain null terminator, use write safer
                std::cout << "Price: " << trade->price << "\n";
                std::cout << "Quantity: " << trade->quantity << "\n";
                std::cout << "\n";
                break;
            }
            case 2: {
                auto* quote = reinterpret_cast<QuoteMessage*>(buffer + sizeof(PacketHeader));
                if (bytes < sizeof(PacketHeader) + sizeof(QuoteMessage)) continue;
                std::cout<< "Symbol: "; std::cout.write(quote->symbol, 8); std::cout<<"\n"; // symbol is char array string, may not contain null terminator, use write safer
                std::cout << "BidPrice: " << quote->bidPrice << "\n";
                std::cout << "AskPrice: " << quote->askPrice << "\n";
                std::cout << "\n";
                break;
            }
        }
    }
}