#include <iostream>
#include <boost/asio.hpp>
#include <boost/asio/ts/buffer.hpp>
#include <boost/asio/ts/internet.hpp>

#ifndef _TCPCLIENT_HPP_
#define _TCPCLIENT_HPP_

#include "MsgQueue.hpp"
#include "Message.hpp"
#include "interface/IClient.hpp"

namespace ecs {
namespace tcp {

template<typename T>
class Client: public IClient<T> {
    public:
        Client(boost::asio::io_context &io_context,
               boost::asio::ip::tcp::socket _socket,
               MsgQueue<Message<T>> &_q_in) :
               socket(std::move(_socket)), context(io_context), q_in(_q_in)
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
            boost::asio::async_read(socket,
                boost::asio::buffer(&tmp.head, sizeof(MessageHeader<T>)),
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
            boost::asio::async_read(socket,
                boost::asio::buffer(tmp.body.data(), tmp.head.size),
                [this](std::error_code ec, std::size_t len) {
                    (void)len;
                    if (!ec) {
                        addToMsgQueue();
                    } else {
                        std::cerr << "[" << this->getId() << "] Read body failed: " << ec.message() << std::endl;
                        socket.close();
                    }
            });
        }
        virtual void writeHeader()final {
            boost::asio::async_write(socket,
                boost::asio::buffer(&q_out.front().head, sizeof(MessageHeader<T>)),
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
                        std::cerr << "[" << this->getId() << "] Write header failed: " << ec.message() << std::endl;
                        socket.close();
                    }
            });
        }
        virtual void writeBody()final {
            boost::asio::async_write(socket,
                boost::asio::buffer(q_out.front().body.data(), q_out.front().body.size()),
                [this](std::error_code ec, std::size_t len) {
                    (void)len;
                    if (!ec) {
                        q_out.pop_front();
                        if (!q_out.empty())
                            writeHeader();
                    } else {
                        std::cerr << "[" << this->getId() << "] Write header failed: " << ec.message() << std::endl;
                        socket.close();
                    }
            });
        }
        virtual void addToMsgQueue()final {
            tmp.remote = this->shared_from_this();
            q_in.push_back(tmp);
            tmp.empty();
            readHeader();
        }

    private:
        boost::asio::ip::tcp::socket socket;
        boost::asio::io_context &context;

        MsgQueue<Message<T>> &q_in;
        MsgQueue<Message<T>> q_out;

        Message<T> tmp;
};

}
}

#endif //_TCPCLIENT_HPP_
