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

    MarketDataPacket packet{1,18500,100};

    sendto(sockfd, &packet, sizeof(packet), 0, (sockaddr*)&addr, sizeof(addr));

    close(sockfd);
}