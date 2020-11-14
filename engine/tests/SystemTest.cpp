#include "System.hpp"
#include "Game.hpp"
#include "SystemStorage.hpp"

struct Position {
    int x;
};

struct Velocity {
    int vx;
};

int main(void)
{
    Game game("game");

    game.componentStorage.registerComponent<Position>();
    game.componentStorage.registerComponent<Velocity>();

    game.componentStorage.buildEntity()
        .withComponent(Position{10})
        .withComponent(Velocity{2})
        .build();
    game.componentStorage.buildEntity().withComponent(Position{4}).build();

    SystemStorage systems;

    systems.addSystem([](Position &position, const Velocity &velocity) {
        position.x += velocity.vx;
    });
    systems.addSystem([](const Position &p) {
        std::cout << "Position " << p.x << std::endl;
    });

    systems.runTick(game);
    return 0;
}
