#include "Block.h"
#include <math.h>


Block::Block()
{
}

Block::Block(int x, int y, int id, sf::Texture &texture)
{
    this->setPosition(sf::Vector2f(floor(x/30)*30, floor(y/30)*30));
    this->setTexture(texture);
    this->setTextureRect(sf::IntRect(id % 30 * 30, 0, 30, 30));


    this->blockid = id;
    this->blockX = floor(x/30)*30;
    this->blockY = floor(y/30)*30;
}

Block::~Block()
{
}
