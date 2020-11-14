#include "Game.hpp"
#include "LevelState.hpp"
#include "components/Sprite.hpp"
#include "components/PlayerShipController.hpp"
#include "components/Velocity.hpp"
#include "components/CollisionBox.hpp"
#include "components/GameObject.hpp"
#include "components/Enemy.hpp"
#include "components/AnimationLoop.hpp"
#include "components/Destructible.hpp"
#include "components/AnimMontage.hpp"
#include "components/WaveCannon.hpp"
#include "components/Trajectory.hpp"
#include <iostream>
#include <chrono>
#include <cstdlib>
#include <cmath>

// Counted in milleseconds
constexpr int STAR_SPAWN_DELAY = 250;

constexpr unsigned STAR_BUFFER_SIZE = 200;

void LevelState::onStart(Game &instance)
{
    // Creating Back ground
    instance.componentStorage.buildEntity()
        .withComponent(Sprite("level1", 0))
        .withComponent(Transform(Dimensional(10, 10), Dimensional(0, 0),
                                 Dimensional(4, 4)))
        .withComponent(Velocity(-0.5, 0))
        .build();

    // Creating Player Ship
    instance.componentStorage.buildEntity()
        .withComponent(Sprite("player_ships", 2))
        .withComponent(Transform(Dimensional(10, 10), Dimensional(0, 0),
                                 Dimensional(3, 3)))
        .withComponent(PlayerShipController(0, 2.5))
        .withComponent(Velocity(0, 0))
        .withComponent(GameObject::PlayerShip)
        .withComponent(CollisionBox(30, 10, 0, 3, 10))
        .withComponent(Destructible(1, true))
        .withComponent(DeathMontage(AnimMontage("effects", {80, 81, 82, 83, 84}, 7)))
        .withComponent(WaveCannon())
        .build();

    // Floor CollisionBox
    instance.componentStorage.buildEntity()
        .withComponent(Transform(Dimensional(0, 920), Dimensional(1, 1),
                                 Dimensional(1, 1)))
        .withComponent(GameObject::Wall)
        .withComponent(CollisionBox(2000, 60, 0, 0, 1000))
        .build();

    // Bugs Enemies
    instance.componentStorage.buildEntity()
        .withComponent(Sprite{"bug", 4})
        .withComponent(Transform({2000, 400}, {0, 0}, {3, 3}))
        .withComponent(Trajectory([]
        (Transform &t) {
            t.location.x -= 1;
            t.location.y = std::cos(t.location.x * 0.01) * 200 + 300;
        }))
        .withComponent(Destructible(1, true))
        .withComponent(CollisionBox(21, 20, 4, 2, 1))
        .withComponent(DeathMontage(AnimMontage("explosions", {0, 1, 2, 3, 4, 5}, 7)))
        .withComponent(GameObject::Enemy)
        .build();


    // Example Enemy
    instance.componentStorage.buildEntity()
        .withComponent(Sprite{"player_ships", 1})
        .withComponent(Transform({1000, 200}, {0, 0}, {1, 1}))
        .withComponent(Velocity{0, 0})
        .withComponent(Enemy{{Pattern{{-1, 1}, 60}, Pattern{{-1, -1}, 60}}, 10})
        .withComponent(AnimationLoop{{{"enemy_flap", 0},
                                      {"enemy_flap", 1},
                                      {"enemy_flap", 2},
                                      {"enemy_flap", 3},
                                      {"enemy_flap", 4},
                                      {"enemy_flap", 5},
                                      {"enemy_flap", 6},
                                      {"enemy_flap", 7}},
                                     15})
        .build();
}

void LevelState::onPause(Game &instance)
{}

void LevelState::onResume(Game &instance)
{}

void LevelState::onTick(Game &instance)
{
    static std::chrono::time_point last_update = std::chrono::system_clock::now();
    std::chrono::milliseconds tick_delay(STAR_SPAWN_DELAY);

    if (std::chrono::system_clock::now() - last_update < tick_delay)
        return;
    last_update = std::chrono::system_clock::now();

    float scale = rand() % 4 + 3;
    float height = rand() % 800;
    float speed = rand() % 5 + 1;

    m_stars_ids.push(
        instance.componentStorage.buildEntity()
            .withComponent(Sprite("player_ships", 50))
            .withComponent(Transform(Dimensional(2000, height), Dimensional(0, 0), Dimensional(scale, scale)))
            .withComponent(Velocity(-1 * speed, 0))
            .build()
    );
    while (m_stars_ids.size() > STAR_BUFFER_SIZE) {
        instance.componentStorage.destroyEntity(m_stars_ids.front());
        m_stars_ids.pop();
    }
}

void LevelState::onStop(Game &instance)
{}
