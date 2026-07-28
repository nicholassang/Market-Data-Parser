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
        auto* packet = reinterpret_cast<MarketDataPacket*>(buffer);
        std::cout << "Sequence: " << packet->sequence << "\n";
        std::cout << "Price: " << packet->price << "\n";
        std::cout << "Quantity: " << packet->quantity << "\n";
        std::cout << "\n";
    }
}