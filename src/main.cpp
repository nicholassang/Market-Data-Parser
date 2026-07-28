#include "udp_receiver.hpp"

int main() {

    UDPReceiver receiver(9000);

    receiver.receive();

    return 0;
}