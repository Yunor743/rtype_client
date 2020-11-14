#ifndef BABEL_SYSTEM_IMPL_
#define BABEL_SYSTEM_IMPL_

#include <functional>
#include <tuple>

#include "Game.hpp"
#include "Modules.hpp"
#include "System.hpp"
#include "function_traits.hpp"

template <typename T>
using cleaned_component =
    typename std::remove_cv<typename std::remove_reference<T>::type>::type;

template <typename T, typename M>
struct split_modules_components;

template <typename... Modules, typename First, typename... Rest>
requires std::is_base_of<IModule, cleaned_component<First>>::
    value struct split_modules_components<std::tuple<Modules...>,
                                          std::tuple<First, Rest...>>
    : public split_modules_components<std::tuple<Modules..., First>,
                                      std::tuple<Rest...>> {
};

template <typename... Modules, typename... Components>
struct split_modules_components<std::tuple<Modules...>,
                                std::tuple<Components...>> {
    using modules = std::tuple<Modules...>;
    using components = std::tuple<Components...>;
    using type = std::pair<modules, components>;
};

template <typename T>
T &getModule(Game &);

template <typename T>
struct wrapper
    : public wrapper<typename split_modules_components<
          std::tuple<>, typename function_traits<T>::args_type>::type> {
};

template <typename... Modules, typename... Components>
struct wrapper<std::pair<std::tuple<Modules...>, std::tuple<Components...>>> {
    static constexpr auto wrap_system(auto system)
    {
        return [system](Game &game) {
            auto modules = std::tuple<Modules...>(
                getModule<typename std::remove_reference<Modules>::type>(
                    game)...);
            auto components_map = game.componentStorage.join_components(
                game.componentStorage
                    .getComponents<cleaned_component<Components>>()...);

            for (auto &[_, components] : components_map)
                std::apply(system, std::tuple_cat(modules, components));
        };
    }
};

System::System(SystemFunction auto system)
    : m_call_wrapper(wrapper<decltype(system)>::wrap_system(system))
{
}

#endif // BABEL_SYSTEM_IMPL_
