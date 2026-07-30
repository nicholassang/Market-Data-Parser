#include "udp_receiver.hpp"
#include "market_packet.hpp"
#include "ring_buffer.hpp"

#include <iostream>
#include <cstring>

#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>


UDPReceiver::UDPReceiver(int port, RingBuffer<MarketPacket, 1024>& rb) : ringBuffer(rb) {
    std::cout << "UDP Reciver created" << "\n";
    // AF_INET uses Ipv4, SOCK_DGRAM specifics UDP
    sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sockfd < 0) {
        perror("socket");
        std::exit(EXIT_FAILURE);
    }
    sockaddr_in addr{};

    addr.sin_family = AF_INET;
    addr.sin_port = htons(port);
    addr.sin_addr.s_addr = INADDR_ANY;

    if (bind(sockfd, reinterpret_cast<sockaddr*>(&addr), sizeof(addr)) < 0) {
        perror("bind");
        std::exit(EXIT_FAILURE);
    }
}


UDPReceiver::~UDPReceiver() {
    close(sockfd);
}


void UDPReceiver::receive() {
    char buffer[1024];
    std::cout << "Waiting..." << "\n";
    while(true) {
        ssize_t bytes = recvfrom(sockfd, buffer, sizeof(buffer), 0, nullptr, nullptr);
        std::cout << "Received " << bytes << " bytes\n";
        if (bytes < 0) {
            perror("recvfrom");
            continue;
        }
        MarketPacket packet{};
        if (static_cast<size_t>(bytes) > sizeof(packet.data)) {
            continue;
        }
        packet.length = bytes;
        memcpy(packet.data, buffer, bytes);

        if (!ringBuffer.push(packet)) {
            std::cout << "Ring buffer full!\n";
        }
    }
}