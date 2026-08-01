#include "udp_receiver.hpp"
#include "market_packet.hpp"
#include "ring_buffer.hpp"
#include "runtime.hpp"

#include <iostream>
#include <cstring>

#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/epoll.h>


UDPReceiver::UDPReceiver(int port, RingBuffer<MarketPacket*, 65536>& rb, PacketPool<65536>& p) : ringBuffer(rb), pool(p) {
    std::cout << "UDP Reciver created" << "\n";
    // AF_INET uses Ipv4, SOCK_DGRAM specifics UDP
    sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sockfd < 0) {
        perror("socket");
        std::exit(EXIT_FAILURE);
    }

    // Non blocking
    int flags = fcntl(sockfd, F_GETFL, 0);
    fcntl(sockfd, F_SETFL, flags | O_NONBLOCK);

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

    // Epoll for non-blocking socket
    epollFd = epoll_create1(0);

    if(epollFd < 0){
        perror("epoll_create1");
        exit(EXIT_FAILURE);
    }
    
    
    epoll_event event{};
    event.events = EPOLLIN;
    event.data.fd = sockfd;
    
    
    if(epoll_ctl(
            epollFd,
            EPOLL_CTL_ADD,
            sockfd,
            &event
    ) < 0)
    {
        perror("epoll_ctl");
        exit(EXIT_FAILURE);
    }
}


UDPReceiver::~UDPReceiver(){
    close(sockfd);
    close(epollFd);
}


void UDPReceiver::receive(){
    epoll_event events[1];
    while(Runtime::running){
        int n = epoll_wait(
            epollFd,
            events,
            1,
            1000
        );
        if(n < 0){
            perror("epoll_wait");
            break;
        }
        if(n == 0) {
            continue;
        }

        if(events[0].events & EPOLLIN){
            MarketPacket* packet = pool.acquire();
            // If Empty
            if(packet == nullptr){
                continue;
            }
            ssize_t bytes =
                recvfrom(
                    sockfd,
                    packet->data,
                    sizeof(packet->data),
                    0,
                    nullptr,
                    nullptr
                );
            if(bytes > 0){
                packet->length = bytes;
                // If full
                if(!ringBuffer.push(packet)){
                    pool.release(packet);
                }
            } else{
                pool.release(packet);
            }
        }
    }
}