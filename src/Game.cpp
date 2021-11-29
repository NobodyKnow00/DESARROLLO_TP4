#include "Game.h"
#include <cstdlib>
#include <iterator>

Game::Game() :
    m_window(sf::VideoMode(LANE_WIDTH * 3, WINDOW_HEIGHT), "ProtoName", sf::Style::Close | sf::Style::Titlebar),
    m_dividers(sf::Lines, 6),
    m_Player (BASE_COLOR,  sf::Vector2f{LANE_WIDTH, WINDOW_HEIGHT}),
    m_overlayBg({LANE_WIDTH * 4, WINDOW_HEIGHT}),
    m_playing(false),
    start(false)
{
    m_window.setVerticalSyncEnabled(true);

    m_dividers[0] = sf::Vertex({LANE_WIDTH, 0}, sf::Color(180, 180, 180));
    m_dividers[1] = sf::Vertex({LANE_WIDTH, WINDOW_HEIGHT}, sf::Color(180, 180, 180));
    m_dividers[2] = sf::Vertex({LANE_WIDTH * 3, 0}, sf::Color(180, 180, 180));
    m_dividers[3] = sf::Vertex({LANE_WIDTH * 3, WINDOW_HEIGHT}, sf::Color(180, 180, 180));
    m_dividers[4] = sf::Vertex({LANE_WIDTH * 2, 0}, sf::Color(180, 180, 180));
    m_dividers[5] = sf::Vertex({LANE_WIDTH * 2, WINDOW_HEIGHT}, sf::Color(180, 180, 180));   

    m_score = 0;
    m_distance = 0.f;
    m_velocity = 0.f;

    m_font.loadFromFile("assets/font.ttf");
    m_textStart.setFont(m_font);  
    m_textStart.setCharacterSize(20);
    m_textStart.setString("Toma los circulos, evade los triangulos.\n"
                       "     Controla el auto con las flechas \n"
                       "                  izquierda y derecha,\n"
                       "       Presiona espacio para empezar.");
    m_textStart.setPosition((m_window.getSize().x - m_textStart.getLocalBounds().width) / 2.f,
                         (m_window.getSize().y - m_textStart.getLocalBounds().height) / 2.f);


    m_textVersion.setFont(m_font);
    m_textVersion.setCharacterSize(22);
    m_textVersion.setString("V 1.0");
    m_textVersion.setPosition(10, WINDOW_HEIGHT - 30);


    m_textScore.setFont(m_font);
    m_textScore.setCharacterSize(20);
    m_textScore.setPosition(m_window.getSize().x - 230, 10);

    m_overlayBg.setFillColor(sf::Color(0, 0, 0, 100));

    menuArray[0].setFont(m_font);
    menuArray[0].setCharacterSize(30);
    menuArray[0].setFillColor(sf::Color::White);
    menuArray[0].setString("Play");
    menuArray[0].setPosition((m_window.getSize().x - menuArray[0].getLocalBounds().width) / 2.f, ((m_window.getSize().y - menuArray[0].getLocalBounds().height) / 2.f) - 50);

    menuArray[1].setFont(m_font);
    menuArray[1].setCharacterSize(30);
    menuArray[1].setFillColor(sf::Color::White);
    menuArray[1].setString("Credits");
    menuArray[1].setPosition((m_window.getSize().x - menuArray[1].getLocalBounds().width) / 2.f, (m_window.getSize().y - menuArray[1].getLocalBounds().height) / 2.f);

    menuArray[2].setFont(m_font);
    menuArray[2].setCharacterSize(30);
    menuArray[2].setFillColor(sf::Color::White);
    menuArray[2].setString("Exit");
    menuArray[2].setPosition((m_window.getSize().x - menuArray[2].getLocalBounds().width) / 2.f, ((m_window.getSize().y - menuArray[2].getLocalBounds().height) / 2.f) + 50);


    //If these fail to load, simple Circles/Rectangles will be used.
    Obstacle::m_circleTexture.loadFromFile("assets/circle.png");
    Obstacle::m_triangleTexture.loadFromFile("assets/triangle.png");
    Player::m_playerTexture.loadFromFile("assets/car.png");
    m_Player.applyTexture();
    m_Player.reset();
 
    m_bgMusic.openFromFile("assets/bgm.ogg");
    m_bgMusic.setLoop(true);

    
}

void Game::runMenu()
{
    
}

void Game::newGame()
{
   // if (m_bgMusic.getStatus() != sf::SoundSource::Playing)
        //m_bgMusic.play();
    m_obstacles.clear();
    m_score = 0;
    m_velocity = INITIAL_VELOCITY;
    m_distance = SPAWN_DIST;
    m_playing = true;
    start = false;
    m_Player.reset();
}

void Game::gameLoop()
{
    sf::Event event;
    m_window.pollEvent(event);

    if (start == true)
    {
        auto dt = m_timer.restart().asSeconds();

        if (m_playing)
        {
            m_velocity += ACCELERATION * dt;
            m_distance += m_velocity * dt;

            if (m_distance > SPAWN_DIST)
            {
                m_obstacles.emplace_front(static_cast<Obstacle::Type>(rand() % 2), BASE_COLOR, sf::Vector2f{ LANE_WIDTH / 2.f + LANE_WIDTH * (rand() % 3), 0 });
                m_distance -= SPAWN_DIST;
            }

            for (auto it = m_obstacles.begin(); it != m_obstacles.end(); ++it)
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

            m_Player.handleInput(event);
            event.key.code = sf::Keyboard::Space; // Renew event key code
            m_Player.update(dt);
            m_textScore.setString(" Puntaje: " + std::to_string(m_score));
        }

    }
    else
    {
        if (event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::Space)
        {
            start = true;
        }
    }
      
    m_window.clear(BACKGROUND_COLOR);
   
    if (start == false)
    {
        m_window.draw(m_dividers);
        
        m_window.draw(m_overlayBg);
        m_window.draw(m_textStart);
           
    }
    else
    {
        m_window.draw(m_dividers);
        for (auto& o : m_obstacles)
            m_window.draw(o);
        m_window.draw(m_Player);  

        m_window.draw(m_textScore);
          
    }
    
    m_window.display();
}

void Game::runGame()
{
    srand(time(nullptr));
    sf::Event event;
    
    Menu menu(m_window, m_font);
   
    while (m_window.isOpen())
    {
        sf::Event event;

        while (m_window.pollEvent(event))
        {
            switch (event.type)
            {
            case sf::Event::KeyReleased:
                switch (event.key.code)
                {
                case sf::Keyboard::Up:
                    menu.moveUp(menuArray);
                    break;

                case sf::Keyboard::Down:
                    menu.moveDown(menuArray);
                    break;

                case sf::Keyboard::Return:
                    switch (menu.getKeyPressedItem())
                    {
                    case 0:
                        if (m_playing == false)
                        {
                            newGame();
                            
                            do
                            {
                                gameLoop();
                               
                            } while (m_playing == true);
                        }
                       
                        break;
                    case 1:
                        std::cout << "Option button has been pressed" << std::endl;
                        break;
                    case 2:
                        m_window.close();
                        break;
                    }

                    break;
                }

                break;
            case sf::Event::Closed:
                m_window.close();
                break;
            }
        }

        m_window.clear();

        for (int i = 0; i < ARRAY_AMOUNT; i++)
        {
            m_window.draw(menuArray[i]);
        }

        m_window.draw(m_textVersion);
       
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
   
}
