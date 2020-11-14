#include "SystemStorage.hpp"

SystemStorage::SystemStorage() : m_systems()
{
}

void SystemStorage::addSystem(System system)
{
    m_systems.push_back(system);
}

void SystemStorage::runTick(Game &game) const
{
    for (auto &system : m_systems) {
        system.call(game);
    }
}
