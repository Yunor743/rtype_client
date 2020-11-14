#include <memory>

#include "Message.hpp"
#include "interface/IClient.hpp"

#ifndef _ISERVER_HPP_
#define _ISERVER_HPP_

namespace ecs {

template<typename T>
class IServer {
    public:
        virtual ~IServer() {};
        virtual bool start() = 0;
        virtual void stop() = 0;
        virtual void update(const size_t maxMessage = -1, const bool wait = false) = 0;

    protected:
        virtual void onClientDisconnect(std::shared_ptr<IClient<T>> cli) {
            (void)cli;
        }
        virtual bool onClientConnect(std::shared_ptr<IClient<T>> cli) {
            (void)cli;
            return true;
        }
        virtual void waitForClientConnection() = 0; // ASYNC
        virtual void msgClient(const Message<T> &msg, std::shared_ptr<IClient<T>> cli) = 0;
        virtual void msgAll(const Message<T> &msg, std::shared_ptr<IClient<T>> skip = nullptr) = 0;
        virtual void onMessage(Message<T> msg) = 0;
};

}
#endif //_ISERVER_HPP_
