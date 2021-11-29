#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <list>
#include <memory>
#include <algorithm>

#include "Menu.h"
#include "Obstacle.h"
#include "Constants.h"
#include "Player.h"


class Game
{
    public:
        Game();      
        void runGame();
    private:       
        void gameLoop(sf::Event event);

        sf::RenderWindow m_window;

        sf::VertexArray m_dividers;
        std::list<Obstacle> m_obstacles;
        Player m_Player;       

        sf::Font m_font;
        sf::Text m_textStart;
        sf::Text m_textScore;
        sf::Text m_textVersion;
        sf::RectangleShape m_overlayBg;

        sf::Texture m_backGround;


        sf::Music m_bgMusic;

        sf::Text menuArray[MENU_ARRAY_AMOUNT];
        sf::Text creditsArray[MENU_ARRAY_AMOUNT];

        int aux;

        sf::Clock m_timer;
        int m_score;
        bool m_playing;
        bool start;
        bool pause;
        bool showCredits;
        float m_distance,
              m_velocity;

        
};

#endif
