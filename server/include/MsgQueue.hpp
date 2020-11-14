#include <mutex>
#include <deque>
#include <condition_variable>

#ifndef _MSGQUEUE_HPP_
#define _MSGQUEUE_HPP_

template<typename T>
class MsgQueue {
    public:
        MsgQueue() = default;
        MsgQueue(const MsgQueue<T>&) = delete;
        virtual ~MsgQueue() { this->clear(); }

        const T& front() {
            std::scoped_lock lock(q_mut);
            return q.front();
        }
        const T& back() {
            std::scoped_lock lock(q_mut);
            return q.back();
        }
        bool empty() {
            std::scoped_lock lock(q_mut);
            return q.empty();
        }
        size_t size() {
            std::scoped_lock lock(q_mut);
            return q.size();
        }
        void clear() {
            std::scoped_lock lock(q_mut);
            q.clear();
        }
        T pop_front() {
            std::scoped_lock lock(q_mut);
            T t = std::move(q.front());
            q.pop_front();
            return t;
        }
        T pop_back() {
            std::scoped_lock lock(q_mut);
            T t = std::move(q.front());
            q.pop_back();
            return t;
        }
        void push_back(const T& i) {
            std::scoped_lock lock(q_mut);
            q.emplace_back(std::move(i));

            std::unique_lock<std::mutex> ul(mutBlocking);
            vBlocking.notify_one();
        }
        void push_front(const T& i) {
            std::scoped_lock lock(q_mut);
            q.emplace_front(std::move(i));

            std::unique_lock<std::mutex> ul(mutBlocking);
            vBlocking.notify_one();
        }

        void wait() {
            while(this->empty()) {
                std::unique_lock<std::mutex> ul(mutBlocking);
                vBlocking.wait(ul);
            }
        }


    protected:
        std::mutex q_mut;
        std::deque<T> q;

        std::mutex mutBlocking;
        std::condition_variable vBlocking;
};
#endif //_MSGQUEUE_HPP_
