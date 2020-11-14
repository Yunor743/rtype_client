#ifndef RTYPE_SYSTEM_INPUT_HANDLER_IMPL_
#define RTYPE_SYSTEM_INPUT_HANDLER_IMPL_

#include "InputHandler.hpp"
#include "components/PlayerControlled.hpp"

namespace InputHandlerDetails
{
    template <std::size_t... Ns, typename... Ts>
    auto tail_impl(std::index_sequence<Ns...>, std::tuple<Ts...> t)
    {
        return std::tie(std::get<Ns + 1u>(t)...);
    }

    template <typename First, typename... Ts>
    std::tuple<Ts...> tail(std::tuple<First, Ts...> t)
    {
        return tail_impl(std::make_index_sequence<sizeof...(Ts)>(), t);
    }

    template <typename T>
    struct wrapper
        : public wrapper<typename split_modules_components<
              std::tuple<>, typename function_traits<T>::args_type>::type> {
    };

    template <typename... Modules, typename... Components>
    struct wrapper<
        std::pair<std::tuple<Modules...>, std::tuple<Components...>>> {
        static std::function<void(Game &)> wrap_system(auto system, Input key)
        {
            return [system, key](Game &game) {
                auto modules = std::tuple<Modules...>(
                    getModule<typename std::remove_reference<Modules>::type>(
                        game)...);
                auto components_map = game.componentStorage.join_components(
                    game.componentStorage.getComponents<PlayerControlled>(),
                    game.componentStorage
                        .getComponents<cleaned_component<Components>>()...);
                auto &input = game.inputModule.value().get();

                for (auto &[_, components] : components_map) {
                    auto controller = std::get<0>(components);
                    if (input.isKeyPressed(controller.player_id, key))
                        std::apply(system, tail(components));
                                   // std::tuple_cat(modules, components));
                }
            };
        }
    };
} // namespace InputHandlerDetails

template <typename Fn>
System createInputHandler(Input key, Fn f)
{
    return System(InputHandlerDetails::wrapper<Fn>::wrap_system(f, key));
}

#endif // RTYPE_SYSTEM_INPUT_HANDLER_IMPL_
