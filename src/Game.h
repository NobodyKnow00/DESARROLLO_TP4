#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <deque>
#include <memory>
#include <algorithm>

#include "Obstacle.h"
#include "Constants.h"
#include "Player.h"

class Game
{
    public:
        Game();
        void run();
    private:
        void newGame();
        void gameOver();
        static bool isGameOver(Player::Lane carLane, Player::Lane objLane, Obstacle::Type type);

        sf::RenderWindow m_window;

        sf::VertexArray m_dividers;
        std::deque<Obstacle> m_obstacles;
        Player m_Player;

        sf::Font m_font;
        sf::Text m_prompt;
        sf::RectangleShape m_overlayBg;

        sf::Music m_bgMusic;

        sf::Clock m_timer;
        int m_score;
        bool m_playing;
        float m_distance,
              m_velocity;
};

#endif // GAME_H
