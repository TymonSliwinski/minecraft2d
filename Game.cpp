#include "Game.h"
#include <math.h>
#include <fstream>
#include <iostream>
#include <string>
#include <time.h>
#include <stdlib.h>
#include <algorithm>


Game::Game()
{
}

Game::~Game()
{
}

void Game::run()
{
    init(1280, 720);
    //gameloop();
}


void Game::init(int w, int h)
{
    window.create(sf::VideoMode(w, h), "Mincraft");
    window.setFramerateLimit(20);
    //window.setVerticalSyncEnabled(true);

    sf::Texture menu;
    menu.loadFromFile("textures/menu.jpg");
    sf::Sprite menuScreen;
    menuScreen.setTexture(menu);
    menuScreen.setPosition(0, 0);
    menuScreen.setScale(w / 1920.f, h / 1080.f );

    window.create(sf::VideoMode(w, h), "menu");

    bool ok = true;

    while (window.isOpen() && ok)
    {

         while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed || sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
                window.close();
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
                ok = false;
        }

        window.clear();
        window.draw(menuScreen);
        window.display();

    }

    view.setSize(w, h);
    view.setCenter(w/2, h/2);

    background.loadFromFile("textures/background.jpg");
    player_txt.loadFromFile("textures/playerkoy.png");
    blocks_txt.loadFromFile("textures/blocks.png");
    walls_txt.loadFromFile("textures/walls.png");
    //std::cout << "error loading resources" << "\n";

    Background.setTexture(background);
    Background.setPosition(0, 0);


    player.init(400.f, 500.f, player_txt);



    sf::Texture * p = &blocks_txt;
    gui.init(player.getPosition().x, player.getPosition().y, p, 1.5f);


    //loading current world if exists
    ///////////
    std::ifstream world ("world.txt");

    if(world.is_open() && !world.fail())
    {
        bool t;
        int x, y, id;
        while (world >> t >> x >> y >> id)
        {
            if (t)
                blocks.emplace(std::pair<int, int>(x, y), Block(x, y, id, blocks_txt));
            else
                walls.emplace(std::pair<int, int>(x, y), Block(x, y, id, walls_txt));
        }

        world.close();
    }
    else
    {
        //generate world
        generateWorld(5000, 3000);
    }
    /////////////
    gameloop();
}

void Game::gameloop()
{



    sf::Clock clock;

    while(window.isOpen())
    {
        float framerate = 1.0f / clock.getElapsedTime().asSeconds();
        clock.restart();
        std::cout << blocks.size() << "\n";
        std::cout << framerate << "\n";

        std::cout << "player(" <<  player.getPosition().x << "," << player.getPosition().y << ")\n";



        // view & gui
        view.setCenter(player.getPosition());

        window.setView(view);
        gui.update(view.getCenter().x * 1.f, view.getCenter().y - 0.48f * view.getSize().y , selectedBlock);

        std::pair<int, int> topLeft(getGridPos(view.getCenter().x - view.getSize().x/2), getGridPos(view.getCenter().y - view.getSize().y/2));
        std::pair<int, int> botRight(getGridPos(topLeft.first + view.getSize().x + 30), getGridPos(topLeft.second + view.getSize().y + 30));
        /////////



        // input
        //////////
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed || sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
                window.close();

            if (event.type == sf::Event::KeyPressed)
            {
                switch (event.key.code)
                {
                    //saving world
                    case ( sf::Keyboard::F1):
                    {
                        std::ofstream world("world.txt");
                        for (const auto& [pos, block] : blocks)
                        {
                            world << 1;
                            world << " " << block.blockX;
                            world << " " << block.blockY;
                            world << " " << block.blockid << "\n";
                        }
                        for (const auto& [pos, wall] : walls)
                        {
                            world << 0;
                            world << " " << wall.blockX;
                            world << " " << wall.blockY;
                            world << " " << wall.blockid << "\n";
                        }
                        world.close();
                        break;
                    }

                    //selecting blocks
                    case ( sf::Keyboard::Num1):
                    {
                        this->selectedBlock = 0;
                        break;
                    }
                    case ( sf::Keyboard::Num2):
                    {
                        this->selectedBlock = 1;
                        break;
                    }
                    case ( sf::Keyboard::Num3):
                    {
                        this->selectedBlock = 2;
                        break;
                    }
                    case ( sf::Keyboard::Num4):
                    {
                        this->selectedBlock = 3;
                        break;
                    }
                    case ( sf::Keyboard::Num5):
                    {
                        this->selectedBlock = 4;
                        break;
                    }
                    case ( sf::Keyboard::Num6):
                    {
                        this->selectedBlock = 5;
                        break;
                    }
                    case ( sf::Keyboard::Num7):
                    {
                        this->selectedBlock = 6;
                        break;
                    }
                    case ( sf::Keyboard::Num8):
                    {
                        this->selectedBlock = 7;
                        break;
                    }
                }
            }
        }
        //////////////





            // stawianie bloku
            if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Right))
            {

                sf::Vector2f pos = window.mapPixelToCoords(sf::Mouse::getPosition(window));
                std::cout << "click" << blocks.size() << "(" << getGridPos(pos.x) << ", " << getGridPos(pos.y) << ")" << "\n";
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::LControl))
                    walls.emplace(std::pair<int, int>(getGridPos(pos.x), getGridPos(pos.y)), Block(pos.x, pos.y, selectedBlock,walls_txt));
                else
                    blocks.emplace(std::pair<int, int>(getGridPos(pos.x), getGridPos(pos.y)), Block(pos.x, pos.y, selectedBlock,blocks_txt));
            }

            //usuwanie bloku
            if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
            {
                sf::Vector2f pos = window.mapPixelToCoords(sf::Mouse::getPosition(window));
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::LControl))
                {
                    walls.erase(std::pair<int, int>(getGridPos(pos.x), getGridPos(pos.y)));
                    std::cout << walls.size() << "\n";
                }
                else
                {
                    blocks.erase(std::pair<int, int>(getGridPos(pos.x), getGridPos(pos.y)));
                    std::cout << walls.size() << "\n";
                }
            }
            sf::Vector2f pos = window.mapPixelToCoords(sf::Mouse::getPosition(window));
            std::cout << "Mouse (" << getGridPos(pos.x) << ", " << getGridPos(pos.y) << ")\n";



            for (const auto& [pos, block]: getChunk(blocks, topLeft, botRight))
            {
                player.checkCollision(block);
            }
            player.update();

            window.clear();
            window.draw(Background);

            for(const auto& [pos, wall] : getChunk(walls, topLeft, botRight))
                window.draw(wall);
            window.draw(player);
            for(const auto& [pos, block]: getChunk(blocks, topLeft, botRight))
                window.draw(block);
            window.draw(gui);
            window.display();
    }

}


void Game::generateWorld(int w, int h)
{
    srand(time(NULL));

    int prevStoneHeigth = getGridPos(rand() % 4*30 + h * 0.6);
    int prevDirtHeigth = prevStoneHeigth - 90;
    for (int x = 0; x <= w; x+= 30)
    {

        int stoneHeigth = getGridPos(rand() % (4*30) + (prevStoneHeigth - 45));



        int dirtHeigth;

        if (stoneHeigth - prevDirtHeigth > 5*30 || stoneHeigth - prevDirtHeigth < 2*30)
            dirtHeigth = stoneHeigth - 3 * 30;
        else if (prevStoneHeigth > stoneHeigth)
            dirtHeigth = prevDirtHeigth - 30;
        else if (prevStoneHeigth == stoneHeigth)
            dirtHeigth = prevDirtHeigth;
        else
            dirtHeigth = prevDirtHeigth + 30;



        for (int y = getGridPos(h); y >= dirtHeigth; y -= 30)
        {
            blocks.emplace(std::pair<int, int>(x, y), Block(x, y, (y >= stoneHeigth ? 2 : 1),blocks_txt));
            walls.emplace(std::pair<int, int>(x, y), Block(x, y, (y >= stoneHeigth ? 2 : 1),walls_txt));
        }


        // grass layer
        blocks.emplace(std::pair<int, int>(x, dirtHeigth - 30), Block(x, dirtHeigth - 30, 0,blocks_txt));
        walls.emplace(std::pair<int, int>(x, dirtHeigth - 30), Block(x, dirtHeigth - 30, 0,walls_txt));







        prevStoneHeigth = stoneHeigth;
        prevDirtHeigth = dirtHeigth;
    }

}


std::map<std::pair<int, int>, Block> Game::getChunk(const std::map<std::pair<int, int>, Block> &container,
                                                     std::pair<int, int> from,
                                                     std::pair<int, int> to)
{
    std::map<std::pair<int, int>, Block> chunk;
    auto it_from = container.lower_bound(from);
    auto it_to = container.lower_bound(to);

    while (it_from != it_to)
    {
        chunk.emplace(it_from->first, it_from->second);
        it_from++;
    }
    return chunk;
}
