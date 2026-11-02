#include <iostream>
#include <boost/asio.hpp>
#include <boost/bind.hpp>


namespace ASIO = boost::asio;
namespace ASIO_IP = boost::asio::ip;

class Session {
public:
    Session(ASIO::io_service &service):
        mSocket(service) {
    }
    ASIO_IP::tcp::socket &getSocket() {
        return mSocket;
    }
    void start() {
        doAsynRead(); 
    }
private:
    void handleRead(const boost::system::error_code &err, std::size_t bytes) {
        if (!err) {
            processData(bytes);
        } else {
            std::cerr << "Error read on socket: " << err.message() << std::endl;
            delete this;
        } 
    }
    void handleWrite(const boost::system::error_code &err) {
        if (!err) {
            doAsynRead();
        } else {
            std::cerr << "Error during write on socket" << std::endl;
            delete this;
        }
    }
    void doAsynRead() {
        mSocket.async_read_some(ASIO::buffer(mBuffer, BufferSize),
            boost::bind(&Session::handleRead, this,
                ASIO::placeholders::error, ASIO::placeholders::bytes_transferred));
    }
    void processData(std::size_t bytes) {
        if (bytes > BufferSize - 2)
            bytes = BufferSize - 2;
        mBuffer[bytes+1] = '\0';
        std::cout << "Received: " << mBuffer << std::endl;
        std::strncat(mBuffer, " - RESPONSE", BufferSize - bytes - 1);
        std::cout << "Send: " << mBuffer << std::endl;

        mSocket.async_write_some(ASIO::buffer(mBuffer, BufferSize),
            boost::bind(&Session::handleWrite, this, ASIO::placeholders::error));
    }

    ASIO_IP::tcp::socket mSocket;
    enum { BufferSize = 1024 };
    char mBuffer[BufferSize];
};

class Server {
public:
    Server(ASIO::io_service &service, int port): mIoService(service), 
        mAcceptor(service, ASIO_IP::tcp::endpoint(ASIO_IP::tcp::v4(), port)) {
        std::cout << "Start server on port: " << port << std::endl;
        startAccept();
    }
private:
    void startAccept() {
        Session *session = new Session(mIoService);
        mAcceptor.async_accept(session->getSocket(), 
            boost::bind(&Server::handleAccept, this, session,
                boost::asio::placeholders::error));
    }
    void handleAccept(Session *session, const boost::system::error_code &err) {
        if (!err) {
            std::cout << "New connection: " << 
                session->getSocket().remote_endpoint() << std::endl;
            session->start();
        } else {
            std::cerr << "Error on accept" << std::endl;
            delete session;
        }
        startAccept();
    }
    ASIO::io_service &mIoService;
    ASIO_IP::tcp::acceptor mAcceptor;
};

int main(int argc, char *argv[]) {
    try {
        if (argc < 2) {
            std::cout << "Usage: server <port_number>" << std::endl;
            return -1;
        }
        int port = std::atoi(argv[1]);
        ASIO::io_service ioService;
        Server s(ioService, port);
        ioService.run();
    } catch (std::exception &ex) {
        std::cerr << "Exception: " << ex.what() << std::endl;        
    }
    return 0;
}
