#include "Game.hpp"
#include "SfmlAudioModule.hpp"
#include "SfmlModule.hpp"
#include "components/Sprite.hpp"
#include "components/PlayerControlled.hpp"
#include "components/Velocity.hpp"
#include "components/GameObject.hpp"
#include "components/CollisionBox.hpp"
#include "components/Destructible.hpp"
#include "components/AnimMontage.hpp"
#include "components/Trajectory.hpp"
#include "LevelState.hpp"
#include <iostream>
#include "systems/InputHandler.hpp"
#include "systems/rtype_systems.h"
#include <boost/dll/runtime_symbol_info.hpp>
#include <cstdlib>
#include <time.h>

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

    // Modules Initialisation and assignation
    std::unique_ptr<IModule> sfml_module(new SfmlModule(
        "R-Type SOLO v0.1",
        assets_location));
    auto audio_module = std::make_unique<SfmlAudioModule>();

    game.addModule("sfml", std::move(sfml_module));
    game.setDisplayModule("sfml");
    game.setInputModule("sfml");
    game.addModule("audio-sfml", std::move(audio_module));
    game.setAudioModule("audio-sfml");

    srand(time(NULL));

    // Components registering
    game.componentStorage.registerComponent<Transform>();
    game.componentStorage.registerComponent<Sprite>();
    game.componentStorage.registerComponent<PlayerControlled>();
    game.componentStorage.registerComponent<Velocity>();
    game.componentStorage.registerComponent<CollisionBox>();
    game.componentStorage.registerComponent<GameObject>();
    game.componentStorage.registerComponent<PlayerShipController>();
    game.componentStorage.registerComponent<Enemy>();
    game.componentStorage.registerComponent<AnimationLoop>();
    game.componentStorage.registerComponent<Destructible>();
    game.componentStorage.registerComponent<AnimMontage>();
    game.componentStorage.registerComponent<DeathMontage>();
    game.componentStorage.registerComponent<WaveCannon>();
    game.componentStorage.registerComponent<Trajectory>();

    // Systems Initialisation
    // System that displays entities with a transform and a sprite on screen
    game.systemStorage.addSystem([](IDisplayModule &display,
                                    const Transform &transform,
                                    const Sprite &sprite) {
        if (!sprite.hidden)
            display.drawSprite(sprite.name, transform, sprite.tile_id);
    });

    game.systemStorage.addSystem(playership_ct_input_getter);
    game.systemStorage.addSystem([]
    (Velocity &velocity, const PlayerShipController &controller) {
        velocity.x = controller.moovingRight * controller.getSpeed() \
        + controller.moovingLeft * -1 * controller.getSpeed();
        velocity.y = controller.moovingDown * controller.getSpeed() \
        + controller.moovingUp * -1 * controller.getSpeed();
    });

    // DEBUG Collision Displayer

    game.systemStorage.addSystem([]
    (IDisplayModule &display, const Transform &transform, const CollisionBox &box) {
        sf::RectangleShape rect;
        rect.setPosition(transform.location.x + box.offset_x * transform.scale.x, transform.location.y + box.offset_y * transform.scale.y);
        rect.setSize(sf::Vector2f(box.width * transform.scale.x, box.height * transform.scale.y))    ;
        dynamic_cast<SfmlModule &>(display).drawDebugBox(rect);
    });

    std::function<void(Game &)> collision_system = collisions_update;
    game.systemStorage.addSystem(collision_system);
    std::function<void(Game &)> destructible_reaper_system = destructible_reaper;
    game.systemStorage.addSystem(destructible_reaper_system);
    std::function<void(Game &)> wave_cannon_projectile_system = wave_cannon_projectile_summoner;
    game.systemStorage.addSystem(wave_cannon_projectile_system);

    // movement
    game.systemStorage.addSystem(velocity_applicator);
    game.systemStorage.addSystem(trajectory_applicator);

    game.systemStorage.addSystem(playership_animations);
    game.systemStorage.addSystem(move_enemies);
    game.systemStorage.addSystem(run_animation_loops);
    game.systemStorage.addSystem(collision_damages);
    game.systemStorage.addSystem(play_deathmontages);
    game.systemStorage.addSystem(draw_animmontages);
    game.systemStorage.addSystem(draw_deathmontages);
    game.systemStorage.addSystem(wave_cannon_input_getter);
    game.systemStorage.addSystem(corpse_hider);

    // States Initialisation
    std::unique_ptr<AState> level_state(new LevelState);
    game.stateMachine.setState(std::move(level_state));

    game.run();
}
