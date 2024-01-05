#include "Player.h"

Player::Player()
{
}

Player::~Player()
{
}

void Player::init(int x, int y, sf::Texture &texture)
{
    this->setPosition(sf::Vector2f(x, y));
    this->setTexture(texture);
    this->initPhysics();
}


void Player::initPhysics()
{
    this->velocityMax = 6.f;
    this->velocityMin = 1.5f;
    this->acceleration = 2.5f;
    this->drag = 0.7f;
    this->gravity = 4.f;
    this->velocityMaxY = 18.f;
}

void Player::updatePhysics()
{
    this->velocity.y += this->gravity;

    if (std::abs(this->velocity.y) > this->velocityMaxY)
    {
        this->velocity.y = this->velocityMaxY * (this->velocity.y < 0.f ? -1.f : 1.f);
    }


    this->velocity *= this->drag;

    if (std::abs(this->velocity.x) < this->velocityMin)
        this->velocity.x = 0.f;
    if (std::abs(this->velocity.y) < this->velocityMin)
        this->velocity.y = 0.f;

   sf::Sprite::move(velocity);

}

void Player::move(const float dir_x, const float dir_y)
{
    this->velocity.x += dir_x * this->acceleration;

    this->velocity.y += dir_x * this->acceleration;

    if (std::abs(this->velocity.x) > this->velocityMax)
    {
        this->velocity.x = this->velocityMax * (this->velocity.x < 0.f ? -1.f : 1.f);
    }
}

void Player::resetVelocityY()
{
    this->velocity.y = 0.f;
}

void Player::jump()
{
    this->velocity.y -= 32.f;
    this->canJump = false;
}

void Player::update()
{
    this->updatePhysics();
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) this->velocity.x -= 2.7;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) this->velocity.x += 2.7;;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) && this->canJump) jump();
    sf::Sprite::move(velocity);
}


void Player::checkCollision(sf::Sprite other)
{
    sf::FloatRect pb = this->getGlobalBounds();
    sf::FloatRect ob = other.getGlobalBounds();
    sf::FloatRect nextPos = pb;

    if (!pb.intersects(ob))
        return;

    // gracz na bloku
    nextPos = pb;
    nextPos.top = (pb.top + pb.height + this->velocity.y);
    if(ob.intersects(nextPos))
    {
        this->resetVelocityY();
        this->setPosition(pb.left, ob.top - pb.height - 5.5f);
        this->canJump = true;
        return;
    }
    // gracz koliduje z blokiem w x po prawej
    nextPos = pb;
    nextPos.left = pb.left + pb.width + this->velocity.x;
    nextPos.top = pb.top + pb.height / 6.f;
    if (ob.intersects(nextPos))
    {
        this->setPosition(ob.left - pb.width -5.f, pb.top);
        return;
    }
    // gracz koliduje z blokiem w x po lewej
    nextPos = pb;
    nextPos.left = pb.left - pb.width + this->velocity.x;
    nextPos.top = pb.top + pb.height / 6.f;
    if (ob.intersects(nextPos))
    {
        this->setPosition(ob.left + ob.width + 2.f, pb.top);
        return;
    }
    // gracz pod blokiem
    nextPos = pb;
    nextPos.top = pb.top + pb.height / 1.5f + this->velocity.y;
    if (ob.intersects(nextPos))
    {
        this->resetVelocityY();
        this->setPosition(pb.left, ob.top + ob.height + 5.f);
        this->canJump = false;
        return;
    }

}
