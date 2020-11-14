#ifndef BABEL_SYSTEM_H_
#define BABEL_SYSTEM_H_

#include "function_traits.hpp"
#include <concepts>
#include <functional>

class Game;

template <typename Fn>
concept SystemFunction =
    std::is_same<typename function_traits<Fn>::result_type, void>::value
        &&function_traits<Fn>::arity > 0;
// concept SystemFunction = boost::function_traits<Fn>::result_type;

class System
{
  public:
    System(std::function<void(Game &)> system);
    System(SystemFunction auto system);

    void call(Game &) const;

  private:
    std::function<void(Game &)> m_call_wrapper;
};

#ifndef RTYPE_SYSTEM_NO_IMPL
#include "System.tpp"
#endif

#endif // BABEL_SYSTEM_H_
