#pragma once

#include <string>
#include <entitymanager.hpp>

struct GameManager {
    explicit GameManager(uint16_t const width, uint16_t const height, std::string title);
    ~GameManager();

    void run();

    // Systems
    void update_entities();
    void render_system();
    void input_system();
private:
    void generateLevel1();

    EntityManager EM_{};
};