class UDPReceiver {
    public: 
        UDPReceiver(int port);
        ~UDPReceiver();

        void receive();
    private:
        int sockfd;
};