#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <math.h>
#include <vector>
#include <iostream>
#include "Player.h"
#include "Block.h"
#include <map>

int main()
{
    sf::RenderWindow window(sf::VideoMode(1200, 530), "Game");
    window.setFramerateLimit(30);

    sf::Texture player_txt;
    player_txt.loadFromFile("textures/player.png");

    sf::Texture dirt_txt;
    dirt_txt.loadFromFile("textures/1.png");

    sf::Texture background;
    background.loadFromFile("textures/background.png");

    sf::Sprite Background;
    Background.setTexture(background);
    Background.setPosition(0, 0);

    std::vector<Block> blocks;

    for(int i = 0; i<=20; i++)
    {
        blocks.push_back(Block(i*30, 500, 1, dirt_txt));
    }

    Player player(300, 300, player_txt);

    while (window.isOpen())
    {
        system("cls");
        std::cout << blocks.size() << "\n";

        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        std::cout << "player(" <<  player.getPosition().x << "," << player.getPosition().y << ")\n";
        //kolizja
        int kolx = 0;
        bool koly = 0;
        for (Block block : blocks)
        {
            std::cout << block.blockX << "," << block.blockY << "\n";
            //if (player.getPosition().x >= block.blockX && player.getPosition().x <= block.blockX+30 && player.getPosition().y <= block.blockY-1)
            if(player.checkCollision(block) == 0)
            {
                koly = 0;
                continue;
            }

            if (player.checkCollision(block) == 2)
            {
                        player.velocity.x = 0;
                        player.velocity.y = 0;
                        koly = 1;
                        kolx = 1;
                        std::cout << "kolx" << kolx << "\n";
                        std::cout <<player.getPosition().x << "," << player.getPosition().y << "\n";
                        std::cout << "blok" << block.blockX << "," << block.blockY << "\n";
            }
            else if (player.checkCollision(block) == 3)
            {
                        player.velocity.x = 0;
                        player.velocity.y = 0;
                        koly = 1;
                        kolx = -1;
                        std::cout << "kolx" << kolx << "\n";
                        std::cout <<player.getPosition().x << "," << player.getPosition().y << "\n";
                        std::cout << "blok" << block.blockX << "," << block.blockY << "\n";
            }
            else if (player.checkCollision(block) == 1)
            {
                        player.velocity.y = 0;
                        koly = 1;
            }
//            switch (player.checkCollision(block))
//            {
//                case 2:
//                    {
//                        player.velocity.x *= -2;
//                        player.velocity.y = 0;
//                        kol = 1;
//                        break;
//                    }
//                case 1:
//                    {
//                        player.velocity.y = 0;
//                        kol = 1;
//                        break;
//                    }
//                case -1:
//                    {
//                        player.velocity.y = 0;
//                        kol = 0;
//                        break;
//                    }
////                case 0:
////                    {
////                    kol = 0;
////                    break;
////                    }
//            }
            break;

        }
        if (koly > 0) player.velocity.y = 0.f;
        else player.velocity.y = 5.f;
        player.update(koly, kolx);


        // stawianie bloku
        if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Right))
        {

            sf::Vector2i pos = sf::Mouse::getPosition(window);
            std::cout << "click" << blocks.size() << "(" << (int)(pos.x/30)*30 << ", " << (int)(pos.y/30)*30 << ")" << "\n";
            blocks.push_back(Block(pos.x, pos.y, 1,dirt_txt));
            sf::sleep(sf::seconds(0.08));
        }

        //usuwanie bloku
        if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
        {
            sf::Vector2i pos = sf::Mouse::getPosition(window);
            int i = -1;
            for(Block block : blocks){
                i++;
                if (block.blockX == floor(pos.x/30)*30 && block.blockY == floor(pos.y/30)*30)
                    blocks.erase(std::next(blocks.begin(), i));
            }
            sf::sleep(sf::seconds(0.08));
        }

        window.clear();
        window.draw(Background);
        window.draw(player);
        for(auto block : blocks)
            window.draw(block);
        window.display();
    }

    return 0;
}
