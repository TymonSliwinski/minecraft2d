#pragma once
#include <SFML/Graphics.hpp>


class Player : public sf::Sprite {
public:
    Player();
    ~Player();

    sf::Vector2f velocity;

    void init(int x, int y, sf::Texture &texture);
    void move(const float dir_x, const float dir_y);
    void update();
    void checkCollision(sf::Sprite other);
private:
    void resetVelocityY();
    void jump();
    bool collides = false;
    bool canJump = false;
    float velocityMax;
    float velocityMin;
    float acceleration;
    float drag;
    float velocityMaxY;
    float gravity;
    void initPhysics();
    void updatePhysics();


};


