#include "aicomponent.hpp"
#include "physicscomponent.hpp"
#include <entitymanager.hpp>
#include <entity.hpp>
#include <cmath>
#include <algorithm>

///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////
float
AIComponent::distance_epsilon(float const target, float const origin) const noexcept {
   auto const dist = target - origin;
   if ( std::abs(dist) < data.epsilon ) {
      return 0.0f;
   }
   return dist;
}

///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////
void
AIComponent::update(EntityManager& EM, Entity& e) {
   // Must have physics
   if ( auto* phy = e.getComponent( PhysicsComponent({}) ) ) {
      auto& P  = phy->data;
      auto& AI = data;

      // Preceive environment
      if(AI.tiempo > AI.limite){
         sense_environment(EM);
         AI.tiempo = 0.0f;
      }
      AI.tiempo += 0.05f;

      // Adjust velocity to distance
      auto const dist  = distance_epsilon(AI.tx, P.x);
      phy->setVelocityX(dist, AI.max_vel_relative); //static_cast<const float> (std::rand())/100
   }
};

///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////
void
AIComponent::sense_environment(EntityManager& EM) {
   auto* player = EM.getFirstEntityByTags(Entity::Player); if (!player) return;
   auto* p_phy  = player->getComponent( PhysicsComponent({}) ); if (!p_phy) return;

   data.tx = p_phy->data.x;
   data.ty = p_phy->data.y;
}
