#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <deque>
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
        void runMenu();
        void runGame();
    private:
        void newGame();
        void gameLoop();
        void gameOver();
        static bool isGameOver(Player::Lane carLane, Player::Lane objLane, Obstacle::Type type);

        sf::RenderWindow m_window;

        sf::VertexArray m_dividers;
        std::deque<Obstacle> m_obstacles;
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

        sf::Clock m_timer;
        int m_score;
        bool m_playing;
        bool start;
        bool showCredits;
        float m_distance,
              m_velocity;

        
};

#endif
