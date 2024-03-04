#include "rendercomponent.hpp"
#include <raylib.h>
#include <entity.hpp>
#include <physicscomponent.hpp>

uint16_t RenderComponent_type { 0 };

void 
RenderComponent::update(EntityManager&, Entity& e) {
   auto& d = data;
   auto* phyc = e.getComponent(PhysicsComponent{});
   if ( phyc != nullptr ) {
      auto& p = phyc->data;
      d.x = static_cast<uint16_t>(p.x);
      d.y = static_cast<uint16_t>(p.y);
   }
   DrawRectangle(d.x, d.y, d.w, d.h, d.c);
}