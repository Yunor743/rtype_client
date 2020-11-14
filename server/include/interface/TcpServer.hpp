#include "MsgQueue.hpp"
#include "TcpClient.hpp"
#include "interface/IServer.hpp"
#include "Snitch.hpp"

#ifndef _TCPSERVER_HPP_
#define _TCPSERVER_HPP_

namespace ecs {
namespace tcp {

template<typename T>
class Server: public IServer<T> {
    public:
        Server(const unsigned port) :
            asio_acceptor(asio_context,
                          boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(), port))
        {}
        virtual ~Server() { this->stop(); };

        virtual bool start()final {
            try {
                waitForClientConnection();
                context_thread = std::thread([this]() { asio_context.run(); } );
            } catch (const std::exception &e) {
                Snitch::warn("TCP_SERVER") << "Exception: " << e.what() << Snitch::endl;
                return false;
            }
            Snitch::msg("TCP_SERVER") << "Server Started" << Snitch::endl;
            return true;
        }
        virtual void stop()final {
            asio_context.stop();
            if (context_thread.joinable()) { context_thread.join(); }
            Snitch::msg("TCP_SERVER") << "Stopped..." << Snitch::endl;
        }
        virtual void update(const size_t maxMessage = -1, const bool wait = false) {
            if (wait) q_in.wait();
            for (size_t i = 0; i < maxMessage && !q_in.empty(); i++) {
                auto msg = q_in.pop_front();
                this->onMessage(msg);
            }
        }
    protected:
        virtual void waitForClientConnection()final {
            asio_acceptor.async_accept(
                [this](std::error_code ec, boost::asio::ip::tcp::socket socket) {
                    if (!ec) {
                        Snitch::msg("TCP_SERVER") << " New Connection: " << socket.remote_endpoint() << Snitch::endl;
                        auto new_client = std::make_shared<Client<T>>(asio_context, std::move(socket), q_in);
                        if (this->onClientConnect(new_client)) {
                            clients.push_back(std::move(new_client));
                            clients.back()->giveId(base_id++);
                            Snitch::msg(std::to_string(clients.back()->getId())) << "Connection Approved" << Snitch::endl;
                        }
                    } else {
                        Snitch::warn("TCP_SERVER") << "Connection Error: " << ec.message() << Snitch::endl;
                    }
            });
        }
        virtual void msgClient(const Message<T> &msg, std::shared_ptr<IClient<T>> cli)final {
            if (cli && *cli) {
                cli->send(msg);
            } else {
                this->onClientDisconnect(cli);
                cli.reset();
                clients.erase(std::remove(clients.begin(), clients.end(), nullptr), clients.end());
            }
        }
        virtual void msgAll(const Message<T> &msg, std::shared_ptr<IClient<T>> skip = nullptr)final {
            bool isInvalidClients = false;

            for (auto &i : clients) {
                if (i && *i) {
                    if (i == skip)
                        i->send(msg);
                } else {
                    this->onClientDisconnect(i);
                    i.reset();
                    isInvalidClients = true;
                }
            }
            if (isInvalidClients)
                clients.erase(std::remove(clients.begin(), clients.end(), nullptr), clients.end());
        }
        virtual void onMessage(Message<T> msg) = 0;

    private:
        MsgQueue<Message<T>> q_in;
        std::deque<std::shared_ptr<Client<T>>> clients;

        boost::asio::io_context asio_context;
        std::thread context_thread;

        boost::asio::ip::tcp::acceptor asio_acceptor;
        uint32_t base_id = 0;
};

}
}
#endif //_TCPSERVER_HPP_
