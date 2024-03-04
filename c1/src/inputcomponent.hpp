#pragma once
#include <component.hpp>

struct InputComponent : Component {
   struct Data {
      bool left{}, right{};
      bool up{}, down{};
   };
   Data data{};

   static Component::Type getType() noexcept { 
      static auto id { ++numComponentes };
      return id; 
   }
   
   explicit InputComponent(Data d) : data{d} {}
   explicit InputComponent() = default;
   void update(EntityManager&, Entity&) final;
};