#include <SFML/Graphics.hpp>
#include "game.hpp"
#include <iostream>
#include <string>
#include <random>
#include <sstream>
#include <math.h>

#define FPS_MAX 30
#define CHARACTER_SIZE 35
#define MOVE_AMOUNT 7
#define FONT_NAME "Arial.ttf"

game::Character character;
game::Character meteor;
std::random_device rd;
std::uniform_int_distribution<int> dist(0, 640 - (CHARACTER_SIZE / 2));
std::string title("Score: 0");

sf::CircleShape character_shape(CHARACTER_SIZE);
sf::CircleShape meteor_shape(CHARACTER_SIZE / 2);
sf::RenderWindow window(sf::VideoMode(640, 640), title.c_str());
sf::Font font;

bool collision_fix = false; // idk why it works but it does
bool paused = false;
bool lose = false;

int METEOR_SPEED = 7;
float meteor_x = -1;
unsigned int game_score = 0;

void keyboard() {
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
        character.move(-MOVE_AMOUNT);
    } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
        character.move(MOVE_AMOUNT);
    } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
        paused = toggle(paused);
    }
}

void meteor_logic() {
    meteor.pos += METEOR_SPEED;
        
    if(meteor.pos > 640) {
        meteor.pos = 0;
        meteor_x = -1;
        game_score++;
    }
    
    if(meteor_x == -1) {
        meteor_x = dist(rd);
    }
}

void update_pos() {
    character_shape.setPosition(character.pos, window.getSize().y - (CHARACTER_SIZE * 2));
    meteor_shape.setPosition(meteor_x, meteor.pos);
}

void update_title() {
    std::stringstream sstr;
    sstr << "Score: " << game_score;
    title = sstr.str();

    window.setTitle(title);
}

void render_text() {
    sf::Text text;
    text.setFont(font);
    text.setString(title);
    text.setCharacterSize(24);
    text.setFillColor(sf::Color::Yellow);
    text.setStyle(sf::Text::Bold | sf::Text::Underlined);

    window.draw(text);
}

void show_lose_text() {
    sf::Text stext;
    stext.setFont(font);
    stext.setString("You lose");
    stext.setCharacterSize(48);
    stext.setFillColor(sf::Color::Magenta);
    stext.setStyle(sf::Text::Bold | sf::Text::Underlined);
    stext.setPosition(window.getSize().x / 3, window.getSize().y / 2);

    window.draw(stext);
    lose = true;
}

void collisions() {
    if(character_shape.getGlobalBounds().intersects(meteor_shape.getGlobalBounds())) {
        if(collision_fix == false) {
            collision_fix = true;
        } else if (collision_fix == true) {
            show_lose_text();
        }
    }
}

int main()
{
    // everything we need is global for other functions to use
    // nothing needed at the beginning!!!

    character_shape.setFillColor(sf::Color::Green);
    meteor_shape.setFillColor(sf::Color::Red);

    window.setFramerateLimit(FPS_MAX);
    font.loadFromFile(FONT_NAME);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
            if (event.type == sf::Event::KeyPressed)
                keyboard();
        }

        if(!paused && !lose) {
            window.clear();

            meteor_logic();
            update_title();
            collisions();
            update_pos();
            render_text();

            window.draw(character_shape);
            window.draw(meteor_shape);
            window.display();
        }
    }

    return 0;
}