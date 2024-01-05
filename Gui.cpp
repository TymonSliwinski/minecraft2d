#include "Gui.h"
#include <iostream>

Gui::Gui()
{
}

Gui::~Gui()
{
}


void Gui::init(int x, int y, sf::Texture *blocks_texture, float scale)
{
    sf::Vector2f size = sf::Vector2f(blocks_texture->getSize().x, blocks_texture->getSize().y);
    // setting background
    background.setSize(size);
    background.setScale(scale - 0.05f, scale + 0.1f);
    background.setPosition(x - (background.getScale().x * size.x/2), y);
    background.setFillColor(sf::Color(200, 200, 200));

    // setting toolbar
    toolbar.setSize(size);
    toolbar.setTexture(blocks_texture);
    toolbar.setScale(scale - 0.1f, scale - 0.1f);
    toolbar.setPosition(background.getPosition().x + ((background.getScale().x * background.getSize().x - toolbar.getScale().x * toolbar.getSize().x) / 2.f),
                        background.getPosition().y + ((background.getScale().y * background.getSize().y - toolbar.getScale().y * toolbar.getSize().y) / 2.f));

    // setting selector
    selector.setSize(sf::Vector2f(30, 30));
    selector.setScale(scale - 0.1f, scale - 0.1f);
    selector.setPosition(toolbar.getPosition().x, toolbar.getPosition().y);
    selector.setFillColor(sf::Color::Transparent);
    selector.setOutlineColor(sf::Color(102, 255, 102));
    selector.setOutlineThickness(2.f);

}

void Gui::update(float x, float y, int &selectedBlock)
{
    background.setPosition(x - (background.getScale().x * background.getSize().x/2), y);
    toolbar.setPosition(background.getPosition().x + ((background.getScale().x * background.getSize().x - toolbar.getScale().x * toolbar.getSize().x) / 2.f), background.getPosition().y + ((background.getScale().y * background.getSize().y - toolbar.getScale().y * toolbar.getSize().y) / 2.f));
    selector.setPosition(toolbar.getPosition().x + selectedBlock * 30 * toolbar.getScale().x, toolbar.getPosition().y);
}

void Gui::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    target.draw(background);
    target.draw(toolbar);
    target.draw(selector);
}
