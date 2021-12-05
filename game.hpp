#include <SFML/Graphics.hpp>
#include <iostream>
#pragma once

namespace game {
    class Character {
        public:
            float pos;
            bool isAlive;
    
            void move(float a) {
                this->pos += a;
                return;
            }
    };
}