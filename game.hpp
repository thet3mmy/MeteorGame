#include <SFML/Graphics.hpp>
#include <iostream>
#pragma once

namespace game {
    class Character {
        public:
            float pos;
    
            void move(float a) {
                this->pos += a;
                return;
            }
    };
}

bool toggle(bool s) {
    return !s;
}