#ifndef RTYPE_SYSTEM_STORAGE_
#define RTYPE_SYSTEM_STORAGE_

#define RTYPE_SYSTEM_NO_IMPL
#include "System.hpp"

class SystemStorage
{
  public:
    SystemStorage();

    void addSystem(System system);

    void runTick(Game &) const;

  private:
    std::vector<System> m_systems;
};

#ifndef RTYPE_SYSTEM_STORAGE_NO_IMPL
#include "System.tpp"
#endif

#endif // RTYPE_SYSTEM_STORAGE_
