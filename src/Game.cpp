#include "Game.h"
#include <cstdlib>
#include <iterator>

Game::Game() :
    m_window(sf::VideoMode(LANE_WIDTH * 3, WINDOW_HEIGHT), "ProtoName", sf::Style::Close | sf::Style::Titlebar),
    m_dividers(sf::Lines, 6),
    m_Player (BASE_COLOR,  sf::Vector2f{LANE_WIDTH, WINDOW_HEIGHT}),
    m_overlayBg({LANE_WIDTH * 4, WINDOW_HEIGHT}),
    m_playing(false)
{
    m_window.setVerticalSyncEnabled(true);

    m_dividers[0] = sf::Vertex({LANE_WIDTH, 0}, sf::Color(180, 180, 180));
    m_dividers[1] = sf::Vertex({LANE_WIDTH, WINDOW_HEIGHT}, sf::Color(180, 180, 180));
    m_dividers[2] = sf::Vertex({LANE_WIDTH * 3, 0}, sf::Color(180, 180, 180));
    m_dividers[3] = sf::Vertex({LANE_WIDTH * 3, WINDOW_HEIGHT}, sf::Color(180, 180, 180));
    m_dividers[4] = sf::Vertex({LANE_WIDTH * 2, 0}, sf::Color(180, 180, 180));
    m_dividers[5] = sf::Vertex({LANE_WIDTH * 2, WINDOW_HEIGHT}, sf::Color(180, 180, 180));   

    //TODO What should I do if loading this fails ?
    m_font.loadFromFile("assets/font.ttf");
    m_prompt.setFont(m_font);
    //m_prompt.setColor(sf::Color(180, 180, 180));
    m_prompt.setCharacterSize(20);
    m_prompt.setString("Toma los circulos, evade los triangulos.\n"
                       "     Controla el auto con las flechas \n"
                       "                  izquierda y derecha,\n"
                       "       Presiona espacio para empezar.");
    m_prompt.setPosition((m_window.getSize().x - m_prompt.getLocalBounds().width) / 2.f,
                         (m_window.getSize().y - m_prompt.getLocalBounds().height) / 2.f);

    m_overlayBg.setFillColor(sf::Color(0, 0, 0, 100));

    //If these fail to load, simple Circles/Rectangles will be used.
    Obstacle::m_circleTexture.loadFromFile("assets/circle.png");
    Obstacle::m_triangleTexture.loadFromFile("assets/triangle.png");
    Player::m_playerTexture.loadFromFile("assets/car.png");
    m_Player.applyTexture();
    m_Player.reset();
 
    m_bgMusic.openFromFile("assets/bgm.ogg");
    m_bgMusic.setLoop(true);
}

void Game::newGame()
{
    if (m_bgMusic.getStatus() != sf::SoundSource::Playing)
        m_bgMusic.play();
    m_obstacles.clear();
    m_score = 0;
    m_velocity = INITIAL_VELOCITY;
    m_distance = SPAWN_DIST;
    m_playing = true;
    m_Player.reset();
}

void Game::run()
{
    srand(time(nullptr));
    sf::Event event;
    while (m_window.isOpen())
    {
        while (m_window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                m_window.close();
            if (m_playing)
            {
                m_Player.handleInput(event);
            }
            else if (event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::Space)
            {
                m_playing = true;
                newGame();
            }
        }

        auto dt = m_timer.restart().asSeconds();

        if (m_playing)
        {
            m_velocity += ACCELERATION * dt;
            m_distance += m_velocity * dt;

            if (m_distance > SPAWN_DIST)
            {
                //++m_score;
                m_obstacles.emplace_front(static_cast<Obstacle::Type>(rand() % 2), BASE_COLOR, sf::Vector2f{LANE_WIDTH / 2.f + LANE_WIDTH * (rand() % 3), 0});             
                m_distance -= SPAWN_DIST;
            }
            
            for(auto it = m_obstacles.begin(); it != m_obstacles.end(); ++it)
            {
                it->getShape().move(0, m_velocity * dt);
                if (it->getShape().getGlobalBounds().top > WINDOW_HEIGHT - PLAYER_HEIGHT - OBJECT_SIZE && it->getShape().getGlobalBounds().top < WINDOW_HEIGHT - OBJECT_SIZE) // When a triangle collides the player
                {                            
                    if (it->getShape().getPosition().x == FIRST_LANE_CENTER_POSITION && m_Player.getLane() == Player::Left)
                    {
                        if (it->getType() == Obstacle::Triangle)
                        {
                            gameOver();
                            break;
                        }
                        else
                        {
                            m_score++;
                        }
                        it = std::prev(m_obstacles.erase(it));
                    }
                    else if (it->getShape().getPosition().x == SECOND_LANE_CENTER_POSITION && m_Player.getLane() == Player::Middle)
                    {
                        if (it->getType() == Obstacle::Triangle)
                        {
                            gameOver();
                            break;
                        }
                        else
                        {
                            m_score++;
                        }
                        it = std::prev(m_obstacles.erase(it));
                    }
                    else if (it->getShape().getPosition().x == THIRD_LANE_CENTER_POSITION && m_Player.getLane() == Player::Right)
                    {
                        
                        if (it->getType() == Obstacle::Triangle)
                        {
                            gameOver();
                            break;
                        }
                        else
                        {
                            m_score++;
                        }
                        it = std::prev(m_obstacles.erase(it));
                    }                 
                }
                else if (it->getShape().getGlobalBounds().top > WINDOW_HEIGHT && it->getType() == Obstacle::Circle) // When the circle crosses the base 'y' line
                {                 
                     gameOver();
                     break;
                    
                    it = std::prev(m_obstacles.erase(it));
                }
                 
                
            }
           
           

            m_Player.update(dt);
        }


        m_window.clear(BACKGROUND_COLOR);
        m_window.draw(m_dividers);
        for (auto& o : m_obstacles)
            m_window.draw(o);
        m_window.draw(m_Player);
        if (!m_playing)
        {
            m_window.draw(m_overlayBg);
            m_window.draw(m_prompt);
        }
        m_window.display();
    }
}

bool Game::isGameOver(Player::Lane playerLane, Player::Lane objLane, Obstacle::Type type)
{
    if ((playerLane == objLane && type == Obstacle::Circle)
        || (playerLane != objLane && type == Obstacle::Triangle))
            return false;
    return true;
}

void Game::gameOver()
{
    m_playing = false;
    m_prompt.setString(" Puntaje: " + std::to_string(m_score) + ".\n"
        " Presiona espacio para reiniciar.");
    m_prompt.setPosition(0,
            (m_window.getSize().y - m_prompt.getLocalBounds().height) / 2.f);
}
