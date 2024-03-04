#pragma once
#include <cstdint>

struct Entity;
struct EntityManager;

struct Component {
   using Type = uint8_t;

   virtual void update(EntityManager&, Entity&) = 0;
   virtual ~Component() = default;

protected:
   inline static Component::Type numComponentes { 0 };
}; 