#include "udp_receiver.hpp"
#include "market_packet.hpp"
#include "ring_buffer.hpp"
#include "runtime.hpp"

#include <iostream>
#include <cstring>

#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>


UDPReceiver::UDPReceiver(int port, RingBuffer<MarketPacket*, 65536>& rb, PacketPool<65536>& p) : ringBuffer(rb), pool(p) {
    std::cout << "UDP Reciver created" << "\n";
    // AF_INET uses Ipv4, SOCK_DGRAM specifics UDP
    sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sockfd < 0) {
        perror("socket");
        std::exit(EXIT_FAILURE);
    }

    // Set sockfd to timeout after 1s for Ctrl C to work
    timeval timeout{};
    timeout.tv_sec = 1;
    timeout.tv_usec = 0;
    
    setsockopt(
        sockfd,
        SOL_SOCKET,
        SO_RCVTIMEO,
        &timeout,
        sizeof(timeout)
    );

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
    std::cout << "Waiting..." << "\n";
    while(Runtime::running) {
        MarketPacket* packet = pool.acquire();
        // If empty
        if(packet == nullptr){
            continue;
        }
        ssize_t bytes = recvfrom(sockfd, packet->data, sizeof(packet->data), 0, nullptr, nullptr);
        if(bytes < 0){
            pool.release(packet);
            continue;
        }
        if(static_cast<size_t>(bytes) > sizeof(packet->data)){
            pool.release(packet);
            continue;
        }

        packet->length = bytes;

        // If full
        if(!ringBuffer.push(packet)){
            pool.release(packet);
        }
    }
}