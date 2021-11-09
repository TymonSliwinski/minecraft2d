#pragma once
#include <SFML/Graphics.hpp>


class Player : public sf::Sprite {
public:
    Player();
    Player(int x, int y, sf::Texture &texture);
    ~Player();

    sf::Vector2f velocity;
    void update(bool canJump, int kolx);
    void jump();
    int checkCollision(sf::Sprite other);
private:
//    float velocityMax;
//    float acceletarion;
//    float drag;
//    void initPhysics();

};


