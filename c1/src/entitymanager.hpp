#pragma once
#include <span>
#include <cstdint>
#include <array>
#include <entity.hpp>

// Dará acceso al array devolviendolo por referencia constante
struct EntityManager {
   static constexpr std::size_t MAX_ENTITIES { 100 };

   Entity& newEntity() noexcept;

   Entity*        getFirstEntityByTags(Entity::Tag const ts)       noexcept;
   Entity const*  getFirstEntityByTags(Entity::Tag const ts) const noexcept;

   std::size_t freeEntities() const noexcept { return MAX_ENTITIES - alive_; }
   std::span<Entity const> getEntities() const  { return std::span{ entities_.begin(), alive_ }; }
   std::span<Entity>       getEntities()        { return std::span{ entities_.begin(), alive_ }; }
private:
   std::size_t alive_{};
   std::array<Entity, MAX_ENTITIES> entities_{};
};