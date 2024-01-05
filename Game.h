#pragma once
#include <SFML/Graphics.hpp>
#include <Player.h>
#include <Block.h>
#include <map>
#include <utility>
#include <Gui.h>

class Game {
public:
    Game();
    ~Game();

    void run();
    int getGridPos(float n) { return (int)(n/30)*30;}
private:
    void init(int w, int h);
    void gameloop();

    sf::RenderWindow window;
    sf::View view;
    sf::Event event;

    sf::Texture background, player_txt, blocks_txt, walls_txt;
    Player player;
    sf::Sprite Background;

    Gui gui;

    int selectedBlock = 0;

    std::map<std::pair<int, int>, Block> blocks;
    std::map<std::pair<int, int>, Block> walls;
    void generateWorld(int w, int h);


    std::map<std::pair<int, int>, Block> getChunk(const std::map<std::pair<int, int>, Block> &container , std::pair<int, int> from, std::pair<int, int> to);
};
