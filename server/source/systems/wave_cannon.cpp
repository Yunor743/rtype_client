#include "components/WaveCannon.hpp"
#include "components/PlayerShipController.hpp"
#include "components/Transform.hpp"
#include "components/Sprite.hpp"
#include "components/Velocity.hpp"
#include "components/CollisionBox.hpp"
#include "components/Destructible.hpp"
#include "Game.hpp"

// Wave Cannon Projectile config
constexpr char WCP_SPRITESHEET[] = "effects";
constexpr unsigned WCP_BASIC_ID = 22;
constexpr float WCP_OFFSET_X = 30;
constexpr float WCP_OFFSET_Y = 8;
constexpr float WCP_SPEED = 10;
constexpr unsigned WCP_ROUGHNESS = 1;

void wave_cannon_input_getter(WaveCannon &cannon, const PlayerShipController &controller)
{
    if (cannon.status == WaveCannon::Status::Inactive && controller.firing)
        cannon.status = WaveCannon::Status::Charging;
    else if (cannon.status == WaveCannon::Status::Charging && !controller.firing)
        cannon.status = WaveCannon::Status::Firing;
}

void wave_cannon_projectile_summoner(Game &instance)
{
    auto cannon_params = instance.componentStorage.join_components(
        instance.componentStorage.getComponents<WaveCannon>(),
        instance.componentStorage.getComponents<Transform>()
    );

    for (auto &[id, param] : cannon_params) {
        auto &[cannon, transform] = param;
        if (cannon.status == WaveCannon::Status::Firing) {
            instance.componentStorage.buildEntity()
                .withComponent(Sprite(WCP_SPRITESHEET, WCP_BASIC_ID))
                .withComponent(Transform(
                    Dimensional(
                        transform.location.x + WCP_OFFSET_X * transform.scale.x,
                        transform.location.y + WCP_OFFSET_Y * transform.scale.y
                    ),
                    Dimensional(0, 0),
                    transform.scale
                ))
                .withComponent(CollisionBox(16, 4, 0, 0 ))
                .withComponent(Destructible(1))
                .withComponent(Velocity(WCP_SPEED, 0))
                .withComponent(GameObject::Projectile)
                .build();
            cannon.status = WaveCannon::Status::Inactive;
        }
    }
}
