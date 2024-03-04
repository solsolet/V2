#pragma once
#include <component.hpp>

struct PhysicsComponent : Component {
   struct Data {
      float x{}, y{};
      float vx{}, vy{};
      float max_vx{5.0f}, max_vy{5.0f};
   };
   Data data{};

   void setVelocity(float const svx, float const svy, float const mrelx = 1.0f, float const mrely = 1.0f) noexcept;
   void setVelocityX(float const svx, float const max_relative = 1.0f) noexcept;
   void setVelocityY(float const svy, float const max_relative = 1.0f) noexcept;   

   static Component::Type getType() noexcept { 
      static auto id { ++numComponentes };
      return id; 
   }
   
   explicit PhysicsComponent(Data d) : data{d} {}
   explicit PhysicsComponent() = default;
   void update(EntityManager&, Entity&) final;

private:
   void manage_input(Entity&);
};