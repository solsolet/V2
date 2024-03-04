#pragma once
#include <cstdint>
#include <raylib.h>
#include <component.hpp>

struct RenderComponent : Component {
   struct Data {
      uint16_t x{}, y{};
      uint16_t w{1}, h{1};
      Color c{WHITE};
   };
   Data data{};

   static Component::Type getType() noexcept { 
      static auto id { ++numComponentes };
      return id; 
   }

   explicit RenderComponent(Data d) : data{d} {}
   void update(EntityManager&, Entity&) final;
};