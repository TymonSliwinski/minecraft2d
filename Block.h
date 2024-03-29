#pragma once
#include <SFML/Graphics.hpp>

class Block : public sf::Sprite{
public:
    Block();
    Block(int x, int y, int id, sf::Texture &texture);
    ~Block();

    int blockid;
    int blockX;
    int blockY;

private:
    bool operator<(const Block& other) const
    {
        return (blockX < other.blockX) || (blockY < other.blockY);
    }
};
