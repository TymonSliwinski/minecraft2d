#pragma once
#include <SFML/Graphics.hpp>

class Gui : public sf::RectangleShape {
public:
    Gui();
    ~Gui();

    void init(int x, int y, sf::Texture *blocks_texture, float scale);
    void update(float x, float y, int &selectedBlock);
private:
    virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const;
    sf::RectangleShape background;
    sf::RectangleShape toolbar;
    sf::RectangleShape selector;
};
