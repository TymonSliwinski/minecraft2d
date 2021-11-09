#include "Block.h"
#include <math.h>


Block::Block()
{
}

Block::Block(int x, int y, int id, sf::Texture &texture)
{
    setPosition(sf::Vector2f(floor(x/30)*30, floor(y/30)*30));
    setTexture(texture);


    blockid = id;
    blockX = floor(x/30)*30;
    blockY = floor(y/30)*30;
}

Block::~Block()
{
}
