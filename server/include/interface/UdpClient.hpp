#ifndef _UDPCLIENT_HPP_
#define _UDPCLIENT_HPP_

#include "MsgQueue.hpp"
#include "Protocol.hpp"
#include "interface/IClient.hpp"

#include <iostream>
#include <boost/asio.hpp>
#include <boost/asio/ts/buffer.hpp>
#include <boost/asio/ts/internet.hpp>

namespace ecs {
namespace udp {

template<typename T>
class Client: public IClient<T> {
    public:
        Client(boost::asio::io_context &io_context,
               std::shared_ptr<boost::asio::ip::udp::endpoint> remote_endpoint_,
               boost::asio::ip::udp::socket &_socket) :
            remote_endpoint(remote_endpoint_),
            socket(_socket),
            context(io_context)
        {};
        virtual ~Client() { this->disconnect(); };
        virtual void disconnect()final {
            if (this->isConnected())
                boost::asio::post(context, [this]() { socket.close(); });
        }
        virtual void send(const Message<T> &msg)final {
            boost::asio::post(context,
                [this, msg]() {
                    q_out.push_back(msg);
                    if (!q_out.empty()) {
                        writeHeader();
                    }
                });
        }

        virtual bool isConnected()const final { return socket.is_open(); }
        virtual std::string getRemoteIp()const final {
            if (this->isConnected())
                return socket.remote_endpoint().address().to_string();
            return std::string("Not Connected");
        }

    protected:
        virtual void readHeader()final {
            socket.async_receive_from(boost::asio::buffer(&tmp.head, sizeof(MessageHeader<T>)),
               *remote_endpoint,
               [this](std::error_code ec, std::size_t len) {
                   (void)len;
                    if (!ec) {
                        if (tmp.head.size > 0) {
                            tmp.body.resize(tmp.head.size);
                            readBody();
                        } else {
                            addToMsgQueue();
                        }
                    } else {
                        std::cerr << "[" << this->getId() << "] Read Header failed: " << ec.message() << std::endl;
                        socket.close();
                    }
            });
        }
        virtual void readBody()final {
            socket.async_receive_from(boost::asio::buffer(tmp.body.data(), tmp.body.size()),
               *remote_endpoint,
               [this](std::error_code ec, std::size_t len) {
                   (void)len;
                    if (!ec) {
                        addToMsgQueue();
                    } else {
                        std::cerr << "[" << this->getId() << "] Read Body failed: " << ec.message() << std::endl;
                        socket.close();
                    }
            });
        }

        virtual void writeHeader()final {
            socket.async_send_to(
                boost::asio::buffer(&q_out.front().head, sizeof(MessageHeader<T>)),
                *remote_endpoint,
                [this](std::error_code ec, std::size_t len) {
                   (void)len;
                    if (!ec) {
                        if (q_out.front().body.size() > 0) {
                            writeBody();
                        } else {
                            q_out.pop_front();
                            if (!q_out.empty())
                                writeHeader();
                        }
                    } else {
                        std::cerr << "[" << this->getId() << "] Write Header failed: " << ec.message() << std::endl;
                        socket.close();
                    }
            });
        }
        virtual void writeBody()final {
            socket.async_send_to(
                boost::asio::buffer(q_out.front().body.data(), q_out.front().body.size()),
                *remote_endpoint,
                [this](std::error_code ec, std::size_t len) {
                   (void)len;
                    if (!ec) {
                        q_out.pop_front();
                        if (!q_out.empty())
                            writeHeader();
                    } else {
                        std::cerr << "[" << this->getId() << "] Write Body failed: " << ec.message() << std::endl;
                        socket.close();
                    }
            });
        }
        virtual void addToMsgQueue()final {}

    public:
        std::shared_ptr<boost::asio::ip::udp::endpoint> remote_endpoint;

    private:
        boost::asio::ip::udp::socket &socket;
        boost::asio::io_context &context;

        MsgQueue<Message<T>> q_out;
        Message<T> tmp;
};

}
}
#endif //_UDPCLIENT_HPP_
