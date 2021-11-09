#include "Player.h"

Player::Player()
{
}

Player::~Player()
{
}

Player::Player(int x, int y, sf::Texture &texture)
{
    setPosition(sf::Vector2f(x, y));
    setTexture(texture);
}

//void Player::initPhysics()
//{
//    this->velocityMax = 10.f;
//}

int Player::checkCollision(sf::Sprite other)
{
    int px = this->getPosition().x, py = this->getPosition().y, ox = other.getPosition().x, oy = other.getPosition().y;

    // gracz koliduje z blokiem w x po prawej
    if ((px + 30 >= ox) && (px < ox) && (py <= oy) && (py + 57 > oy))
    {
        this->velocity.x = 0;
        return 2;
    }
    // gracz koliduje z blokiem w x po lewej
    else if ((px - 30 <= ox) && (px > ox) && ((py <= oy) && (py + 57 > oy)))
    {
        this->velocity.x = 0;
        return 3;
    }
    // gracz na bloku
    else if(((px + 25 >= ox) && (px - 25 <= ox)) && ((py - 2 <= oy) && py + 60 >= oy))
        return 1;
    // gracz pod blokiem
    else if(((px + 25 >= ox) && (px - 25 <= ox)) && (py -2 >= oy+30))
    {
        this->velocity.y = 0;
        return -1;
    }
    else
        return 0;

}

void Player::jump()
{
    for (int i = 0; i<=50; i++)
        velocity.y -= 1;
}

void Player::update(bool canJump, int kolx)
{
      velocity.x = 0;
//    velocity.y = 0.5;

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) && (kolx != 1)) velocity.x = -5.f;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) && (kolx != -1)) velocity.x = 5.f;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) && canJump) jump();
    move(velocity);
}
