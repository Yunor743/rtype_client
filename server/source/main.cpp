#include "Game.hpp"
#include "SfmlAudioModule.hpp"
#include "SfmlModule.hpp"
#include "components/Sprite.hpp"
#include "components/PlayerControlled.hpp"
#include "components/Velocity.hpp"
#include "components/GameObject.hpp"
#include "components/CollisionBox.hpp"
#include "LevelState.hpp"
#include <iostream>
#include "systems/InputHandler.hpp"
#include <boost/dll/runtime_symbol_info.hpp>
#include "GameServer.hpp"
#include "Protocol.hpp"

int main(void)
{
    Game game("R-Type SOLO");
    std::filesystem::path assets_location =
        std::filesystem::path(boost::dll::program_location().string())
            .parent_path()
            .parent_path()
            .parent_path()
            .append("draft")
            .append("assets");

    std::unique_ptr<IModule> game_server(new GameServer(25555, assets_location));
    // Modules Initialisation and assignation
    //std::unique_ptr<IModule> sfml_module(new SfmlModule(
    //    "R-Type SOLO v0.1",
    //    assets_location));
    //auto audio_module = std::make_unique<SfmlAudioModule>();
    game.addModule("server", std::move(game_server));
    //game.addModule("sfml", std::move(sfml_module));
    game.setDisplayModule("server");
    game.setInputModule("server");
    //game.addModule("audio-sfml", std::move(audio_module));
    game.setAudioModule("server");

    // Components registering
    game.componentStorage.registerComponent<Transform>();
    game.componentStorage.registerComponent<Sprite>();
    game.componentStorage.registerComponent<PlayerControlled>();
    game.componentStorage.registerComponent<Velocity>();
    game.componentStorage.registerComponent<CollisionBox>();
    game.componentStorage.registerComponent<GameObject>();

    // Systems Initialisation
    // System that displays entities with a transform and a sprite on screen
    game.systemStorage.addSystem([](IDisplayModule &display,
                                    const Transform &transform,
                                    const Sprite &sprite) {
                display.drawSprite(sprite.name, transform, sprite.tile_id);
    });

    // Velocity System

    game.systemStorage.addSystem([]
    (Transform &transform, const Velocity &velocity) {
        transform.location.x += velocity.x;
        transform.location.y += velocity.y;
    });

    // DEBUG Collision Displayer

    //game.systemStorage.addSystem([]
    //(IDisplayModule &display, const Transform &transform, const CollisionBox &box) {
    //    sf::RectangleShape rect;
    //    rect.setPosition(transform.location.x + box.offset_x, transform.location.y + box.offset_y);
    //    rect.setSize(sf::Vector2f(box.width * transform.scale.x, box.height * transform.scale.y))    ;
    //    dynamic_cast<SfmlModule &>(display).drawDebugBox(rect);
    //});

    game.systemStorage.addSystem(createInputHandler(
        Input::Up, [](Transform &transform) { transform.location.y--; }));
    game.systemStorage.addSystem(createInputHandler(
        Input::Down, [](Transform &transform) { transform.location.y++; }));
    game.systemStorage.addSystem(createInputHandler(
        Input::Left, [](Transform &transform) { transform.location.x--; }));
    game.systemStorage.addSystem(createInputHandler(
        Input::Right, [](Transform &transform) { transform.location.x++; }));

    // States Initialisation
    std::unique_ptr<AState> level_state(new LevelState);
    game.stateMachine.setState(std::move(level_state));

    game.run();
}
