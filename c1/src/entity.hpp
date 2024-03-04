#pragma once

#include <unordered_map>
#include <memory>
#include <allcomponents.hpp>

struct Entity {
   using tag_type = uint8_t;
   enum Tag {
      Player = 0x01,
      Enemy  = 0x02
   };

   void addTags   (Tag const ts) noexcept;
   bool hasTags   (Tag const ts) const noexcept;
   void removeTags(Tag const ts) noexcept;

   void addComponent(std::unique_ptr<RenderComponent> cmp);
   void addComponent(std::unique_ptr<PhysicsComponent> cmp);
   void addComponent(std::unique_ptr<InputComponent> cmp);
   void addComponent(std::unique_ptr<AIComponent> cmp);

   RenderComponent*        getComponent(RenderComponent)       noexcept;
   RenderComponent const*  getComponent(RenderComponent) const noexcept;
   PhysicsComponent*       getComponent(PhysicsComponent)      noexcept;
   PhysicsComponent const* getComponent(PhysicsComponent) const noexcept;
   InputComponent*         getComponent(InputComponent)        noexcept;
   InputComponent const*   getComponent(InputComponent)  const noexcept;
   AIComponent*            getComponent(AIComponent)           noexcept;
   AIComponent const*      getComponent(AIComponent)     const noexcept;

   void update(EntityManager&);

private:
   tag_type tags_{};
   std::unique_ptr<RenderComponent> ren{};
   std::unordered_map<Component::Type, std::unique_ptr<Component>> components{};
};