#pragma once
#include "entt/entt.hpp"

namespace Hasbu::Core {

class EntityManager {

public:
    static EntityManager& getInstance();
    static void clear(unsigned int e);
    static void drawEntities();

    entt::registry registry;

private:
    EntityManager() = default;
    EntityManager(const EntityManager&) = delete;
    EntityManager& operator=(const EntityManager&) = delete;
};

}
