#include <iostream>
#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <cstdlib>

namespace ASIO = boost::asio;
namespace SYSTEM = boost::system;

class SessionClient {
public:
    SessionClient(ASIO::io_service &service):
        mService(service), mSocket(service), cnt(0) {
    }
    void connect(const ASIO::ip::tcp::endpoint &endpoint) {
        mSocket.async_connect(endpoint, boost::bind(
            &SessionClient::handleConnect, this, ASIO::placeholders::error));
    }
private:
    void handleConnect(const SYSTEM::error_code &err) {
        if (!err) {
            sendNewMessage();
        } else {
            std::cerr << "Error during connect: " << err.message() << std::endl;
        }
    }
    void handleRead(const SYSTEM::error_code &err, std::size_t bytes) {
        if (!err) {
            if (bytes > BufferSize - 2)
                bytes = BufferSize - 2;
            mBuffer[bytes + 1] = '\0';
            std::cout << "Received: " << mBuffer << std::endl;
            if (cnt == 100) {
                SYSTEM::error_code ec;
                mSocket.close(ec);
                if (ec) {
                    std::cerr << "Error during close: " << ec.message() << std::endl;
                }
            } else {
                sendNewMessage();
            }
        } else {
            std::cerr << "Error during read: " << err.message() << std::endl;
        }
    }
    void handleWrite(const SYSTEM::error_code &err, std::size_t bytes) {
        if (!err) {
            mSocket.async_read_some(ASIO::buffer(mBuffer, BufferSize),
                    boost::bind(&SessionClient::handleRead, this,
                        ASIO::placeholders::error, ASIO::placeholders::bytes_transferred));
        } else {
            std::cerr << "Error during write: " << err.message() << std::endl;
        }
    }
    void sendNewMessage() {
        genNewMessage();
        sleepFor(3);
        mSocket.async_write_some(ASIO::buffer(mBuffer, std::strlen(mBuffer) + 1),
                boost::bind(&SessionClient::handleWrite, this,
                    ASIO::placeholders::error, ASIO::placeholders::bytes_transferred));
        std::cout << "[SERVER] Send: " << mBuffer << std::endl;
    }
    void genNewMessage() {
        std::memset(mBuffer, 0x00, sizeof(mBuffer));
        char *msg = std::strcpy(mBuffer, "Message nr: ");
        std::size_t len = std::strlen(mBuffer);
        std::snprintf(mBuffer + len, BufferSize - len - 1, "%d", ++cnt);
    }
    void sleepFor(int sec) {
        ASIO::deadline_timer timer(mService, boost::posix_time::seconds(sec));
        timer.wait();
    }
    ASIO::io_service &mService;
    ASIO::ip::tcp::socket mSocket;
    enum { BufferSize = 1024 };
    char mBuffer[BufferSize];
    int cnt;
};

int main(int argc, char *argv[]) {
    if (argc < 3) {
        std::cerr << "Usage: client <server_ip> <port>" << std::endl;
        return -1;
    }
    try {
        ASIO::io_service service;
        ASIO::ip::address server = 
            ASIO::ip::address::from_string(argv[1]);
        int port = std::atoi(argv[2]);
        std::cout << "Connect to: " << server << " on: " << port << std::endl;
        ASIO::ip::tcp::endpoint endpointServer(server, port);
        SessionClient clientSession(service);
        clientSession.connect(endpointServer);    
        service.run(); 
    } catch (std::exception &exc) {
        std::cerr << "Exception: " << exc.what() << std::endl;
    }
    return 0;
}
