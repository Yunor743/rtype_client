#include "Game.hpp"
#include "ComponentStorage.hpp"
#include <iostream>

static bool test_component_join()
{
    Game random("random");
    ComponentStorage storage(random.stateMachine);

    std::cout << "component_join tests...";
    std::map<unsigned, char> chars;
    std::map<unsigned, short> shorts;
    std::map<unsigned, std::string> strings;

    chars.emplace(0, 'z'); chars.emplace(1, 'a'); chars.emplace(3, 'b');
    chars.emplace(4, 'z'); chars.emplace(5, 'c'); chars.emplace(6, 'z');
    shorts.emplace(1, 1); shorts.emplace(2, -1); shorts.emplace(3, 2);
    shorts.emplace(5, 3); shorts.emplace(6, -1); shorts.emplace(7, -1);
    strings.emplace(0, "__");strings.emplace(1, "first");strings.emplace(2, "__");
    strings.emplace(3, "second");strings.emplace(5, "third");strings.emplace(7, "__");

    std::map<unsigned, std::tuple<char&, short&, std::string&>> result = storage.join_components(chars, shorts, strings);
    std::map<unsigned, std::tuple<char, short, std::string>> model;

    model.emplace(1, std::tuple<char, short, std::string>{'a', 1, "first"});
    model.emplace(3, std::tuple<char, short, std::string>{'b', 2, "second"});
    model.emplace(5, std::tuple<char, short,std::string>{'c', 3, "third"});

    if (result.size() != 3) {
        std::cerr << "Wrong result size, expected 4, got " << result.size() << std::endl;
        return false;
    }

    for (const auto& [key, value] : result) {
        const auto& [ra, rb, rc] = value;
        const auto& [ma, mb, mc] = model[key];

        if (ra != ma || rb != mb || rc != mc) {
            std::cerr << "Wrong content, at" << key;
            std::cerr << " expected {" << ma << ", " << mb;
            std::cerr << "} got {" << ra << ", " << rb << std::endl;
            return 1;
        }
    }

    std::cout << "Done !" << std::endl;
    return true;
}

class FiveHandler {
    public:
    int giveMeFive(void)
    {
        return 5;
    }
};

int main(void)
{
    std::cout << "ComponentStorage tests...";

    Game random("random");
    ComponentStorage storage(random.stateMachine);
    FiveHandler handler;
    FiveHandler handler2;

    storage.registerComponent<FiveHandler>();
    storage.registerComponent<int>();

    int id = storage.buildEntity()
    .withComponent(handler)
    .build();
    if (id != 0) {
        std::cerr << "Invalid entity id, expected 0, found " << id << std::endl;
        return 1;
    }

    id = storage.buildEntity()
    .withComponent(5)
    .build();
    if (id != 1) {
        std::cerr << "Invalid entity id, expected 1, found " << id << std::endl;
        return 1;
    }

    id = storage.buildEntity()
    .withComponent(handler2)
    .withComponent(10)
    .build();
    if (id != 2) {
        std::cerr << "Invalid entity id, expected 2, found " << id << std::endl;
        return 1;
    }

    int parasite_id = storage.buildEntity()
    .withComponent(666)
    .build();

    storage.destroyEntity(parasite_id);

    std::map<unsigned, int> ints = storage.getComponents<int>();

    if (ints.size() != 2) {
        std::cerr << "Invalid int components number, expected 2, found " << ints.size() << std::endl;
        return 1;
    }
    if (ints[1] != 5 || ints[2] != 10) {
        std::cerr << "Ints components aren't correctly stored" << std::endl;
        return 1;
    }

    std::cout << "Done !" << std::endl;

    if (!test_component_join())
        return 1;
}
