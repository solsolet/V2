#pragma once
#include <component.hpp>

struct AIComponent : Component {
   enum class Behaviour {
      FollowPlayer,
      Wander,
      Idle
   };

   struct Data {
      Behaviour   beh{Behaviour::Wander};
      float       tx{}, ty{};
      float       epsilon{0.05f};
      float       max_vel_relative{0.8f};
      float       tiempo{};
      float       limite{};
   };
   Data data{};

   static Component::Type getType() noexcept { 
      static auto id { ++numComponentes };
      return id; 
   }
   
   explicit AIComponent(Data d) : data{d} {}
   explicit AIComponent() = default;
   void update(EntityManager&, Entity&) final;

private:
   float distance_epsilon(float const target, float const origin) const noexcept;
   void sense_environment(EntityManager& e);
};