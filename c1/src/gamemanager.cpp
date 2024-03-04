#include "gamemanager.hpp"
#include <raylib.h>
#include <entity.hpp>
#include <allcomponents.hpp>

///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////
GameManager::GameManager(uint16_t const width, uint16_t const height, std::string title) {       
    InitWindow(width, height, title.c_str());
}

///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////
GameManager::~GameManager() {
    CloseWindow();
}

///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////
void
GameManager::run() {
   generateLevel1();

   SetTargetFPS(60);
   while ( ! WindowShouldClose() ) {
      input_system();
      update_entities();
      render_system();
   }
}

// Levels 

///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////
void
GameManager::generateLevel1() {
   /////////////////////// PLAYER
   {
      auto& e = EM_.newEntity();

      e.addTags(Entity::Player);

      e.addComponent(std::make_unique<InputComponent>());
      e.addComponent(std::make_unique<RenderComponent>(
         RenderComponent::Data{ .w=40, .h=25 }
      ));
      e.addComponent(std::make_unique<PhysicsComponent>(
         PhysicsComponent::Data{ .x=400.f, .y=100.f }
      ));
   }
   /////////////////////// ENEMY 1
   {
      auto& e = EM_.newEntity();

      e.addTags(Entity::Enemy);

      e.addComponent(std::make_unique<RenderComponent>(
         RenderComponent::Data{ .w=40, .h=25, .c=RED }
      ));
      e.addComponent(std::make_unique<PhysicsComponent>(
         PhysicsComponent::Data{ .x=200.f, .y=200.f }
      ));
      e.addComponent(std::make_unique<AIComponent>(
         AIComponent::Data{ 
            .beh = AIComponent::Behaviour::FollowPlayer,
            .max_vel_relative = 0.75f,
            .limite = 0.3f
         }
      ));
   }
   /////////////////////// ENEMY 2
   {
      auto& e = EM_.newEntity();

      e.addTags(Entity::Enemy);

      e.addComponent(std::make_unique<RenderComponent>(
         RenderComponent::Data{ .w=40, .h=25, .c=ORANGE }
      ));
      e.addComponent(std::make_unique<PhysicsComponent>(
         PhysicsComponent::Data{ .x=700.f, .y=300.f }
      ));
      e.addComponent(std::make_unique<AIComponent>(
         AIComponent::Data{ 
            .beh = AIComponent::Behaviour::FollowPlayer,
            .limite = 0.4f
         }
      ));
   }

   /////////////////////// ENEMY 3
   {
      auto& e = EM_.newEntity();

      e.addTags(Entity::Enemy);

      e.addComponent(std::make_unique<RenderComponent>(
         RenderComponent::Data{ .w=40, .h=25, .c=BLUE }
      ));
      e.addComponent(std::make_unique<PhysicsComponent>(
         PhysicsComponent::Data{ .x=500.f, .y=400.f }
      ));
      e.addComponent(std::make_unique<AIComponent>(
         AIComponent::Data{ 
            .beh = AIComponent::Behaviour::FollowPlayer,
            .limite = 0.6f
         }
      ));
   }
}

// Systems

///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////
void
GameManager::update_entities() {
    for( auto& e : EM_.getEntities() ) {
        e.update(EM_);
    }
}

///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////
void
GameManager::render_system() {
   BeginDrawing();
   ClearBackground(BLACK);

   for( auto& e : EM_.getEntities() ) {
      auto* renc = e.getComponent(RenderComponent({}));
      if ( renc ) { renc->update(EM_, e); }
   }

   EndDrawing();
}

///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////
void
GameManager::input_system() {
   // Test Keyboard
   InputComponent::Data actions{
      .left  = IsKeyDown(KEY_LEFT),
      .right = IsKeyDown(KEY_RIGHT), 
      .up    = IsKeyDown(KEY_UP),
      .down  = IsKeyDown(KEY_DOWN)
   };

   for ( auto& e : EM_.getEntities() ) {
      if( auto* inp = e.getComponent( InputComponent({}) ) ) {
         inp->data = actions;
      }
   }
}