#include <unordered_map>

#ifndef _UDPSERVER_HPP_
#define _UDPSERVER_HPP_

#include "interface/IServer.hpp"
#include "UdpClient.hpp"
#include "Protocol.hpp"
#include "Snitch.hpp"

namespace ecs {
namespace udp {

template<typename T>
class Server: public IServer<T> {
    public:
        Server(const unsigned port) :
            asio_acceptor(asio_context,
                          boost::asio::ip::udp::endpoint(boost::asio::ip::udp::v4(), port))
        {};
        virtual ~Server() { this->stop(); };

        virtual bool start()final {
            try {
                waitForClientConnection();
                context_thread = std::thread([this]() { asio_context.run(); });
            } catch (const std::exception &e) {
                Snitch::warn("UDP_SERVER") << "Exception: " << e.what() << Snitch::endl;
                return false;
            }
            Snitch::msg("UDP_SERVER") << "Server Started" << Snitch::endl;
            return true;
        }
        virtual void stop()final {
            asio_context.stop();
            if (context_thread.joinable()) { context_thread.join(); }
            Snitch::msg("UDP_SERVER") << "Stopped..." << Snitch::endl;
        }
        virtual void update(const size_t maxMessage = -1, const bool wait = false) {
            if (wait) msg_in.wait();
            for (size_t i = 0; i < maxMessage && !msg_in.empty(); i++) {
                auto msg = msg_in.pop_front();
                this->onMessage(msg);
            }
        }
        MsgQueue<Message<T>> &getMsgIn() { return msg_in; };

    protected:
        virtual void waitForClientConnection()final { readHeader(); }
        virtual void msgClient(const Message<T> &msg, std::shared_ptr<IClient<T>> cli)final { (void)msg; (void)cli; };
        void msgClient(const Message<T> &msg, std::shared_ptr<Client<T>> cli) {
            if (*cli) {
                cli->send(msg);
            } else {
                Snitch::warn("UDP_SERVER") << "Sending to invalid client" << Snitch::endl;
                this->onClientDisconnect(cli);
                client_list.erase(cli->remote_endpoint);
            }
        }
        virtual void msgAll(const Message<T> &msg, std::shared_ptr<IClient<T>> skip = nullptr)final {
            for (auto &[_, i] : client_list) {
                if (i == skip) continue;
                this->msgClient(msg, i);
            }
        }
        virtual void onMessage(Message<T> msg) = 0;

    private:
       void readHeader() {
            Snitch::msg("UDP_SERVER") << "Start to receive header" << std::endl;
            asio_acceptor.async_receive_from(boost::asio::buffer(&tmp.head, sizeof(MessageHeader<T>)),
               *tmp_end,
               [this](std::error_code ec, std::size_t len) {
                    (void)len;
                    Snitch::msg("UDP_SERVER") << "Readhead" << Snitch::endl;
                    Snitch::msg("UDP_SERVER_DEBUG") << tmp.head << Snitch::endl;
                    if (!ec) {
                        if (tmp.head.size > 0) {
                            tmp.body.resize(tmp.head.size);
                            readBody();
                        } else {
                            addToMsgQueue();
                        }
                    } else {
                        Snitch::warn("UDP_SERVER") << "ReadHeader failed: " << ec.message() << Snitch::endl;
                    }
            });
        }
        void readBody() {
            Snitch::msg("UDP_SERVER") << "ReadBody" << std::endl;
            asio_acceptor.async_receive_from(boost::asio::buffer(tmp.body.data(), tmp.body.size()),
               *tmp_end,
               [this](std::error_code ec, std::size_t len) {
                   (void)len;
                    if (!ec) {
                        addToMsgQueue();
                    } else {
                        Snitch::warn("UDP_SERVER") << "ReadBody failed: " << ec.message() << Snitch::endl;
                    }
            });
        }
        void addToMsgQueue() {
            if (!client_list.contains(tmp_end)) {
                client_list.insert({tmp_end, std::make_shared<Client<T>>(asio_context, tmp_end, asio_acceptor)});
                this->onClientConnect(client_list.at(tmp_end));
            }
            tmp.remote = client_list.at(tmp_end);
            msg_in.push_back(tmp);
            tmp_end = std::make_shared<boost::asio::ip::udp::endpoint>();
            waitForClientConnection();
        }

    private:
        MsgQueue<Message<T>> msg_in;
        std::unordered_map<std::shared_ptr<boost::asio::ip::udp::endpoint>, std::shared_ptr<Client<T>>> client_list;

        boost::asio::io_context asio_context;
        std::thread context_thread;

        Message<T> tmp;
        std::shared_ptr<boost::asio::ip::udp::endpoint> tmp_end;

        boost::asio::ip::udp::socket asio_acceptor;
        uint32_t base_id = 10000;
};

}
}

#endif //_UDPSERVER_HPP_
