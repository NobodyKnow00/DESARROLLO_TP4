#include "Game.h"
#include <cstdlib>
#include <iterator>

Game::Game() :
    m_window(sf::VideoMode(LANE_WIDTH * 3, WINDOW_HEIGHT), "ProtoName", sf::Style::Close | sf::Style::Titlebar),
    m_dividers(sf::Lines, 6),
    m_Player ( sf::Vector2f{LANE_WIDTH, WINDOW_HEIGHT}),
    m_overlayBg({LANE_WIDTH * 4, WINDOW_HEIGHT}),
    m_playing(false),
    start(false),
    showCredits(false),
    aux(0),
    pause(false)
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
                       "       Presiona espacio para empezar,\n"
                       "               'P' para pausar el juego.");
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
    menuArray[2].setPosition((m_window.getSize().x - menuArray[2].getLocalBounds().width) / 2.f, ((m_window.getSize().y - creditsArray[2].getLocalBounds().height) / 2.f) + 50);

    creditsArray[0].setFont(m_font);
    creditsArray[0].setCharacterSize(20);
    creditsArray[0].setFillColor(sf::Color::White);
    creditsArray[0].setString("Made by:");
    creditsArray[0].setPosition((m_window.getSize().x - creditsArray[0].getLocalBounds().width) / 2.f, WINDOW_HEIGHT - 200);

    creditsArray[1].setFont(m_font);
    creditsArray[1].setCharacterSize(20);
    creditsArray[1].setFillColor(sf::Color::White);
    creditsArray[1].setString("Ignacio Sanduay & Matias Pierpaoli");
    creditsArray[1].setPosition((m_window.getSize().x - creditsArray[1].getLocalBounds().width) / 2.f, WINDOW_HEIGHT - 170);

    creditsArray[2].setFont(m_font);
    creditsArray[2].setCharacterSize(20);
    creditsArray[2].setFillColor(sf::Color::White);
    creditsArray[2].setString("Using SFML-2.5.1");
    creditsArray[2].setPosition((m_window.getSize().x - creditsArray[2].getLocalBounds().width) / 2.f, WINDOW_HEIGHT - 140);

    //If these fail to load, simple Circles/Rectangles will be used.
    Obstacle::m_circleTexture.loadFromFile("assets/circle.png");
    Obstacle::m_triangleTexture.loadFromFile("assets/triangle.png");
    Player::m_playerTexture.loadFromFile("assets/SpaceShip.png");
    m_backGround.loadFromFile("assets/space.png");
    m_Player.applyTexture();
    m_Player.reset();

    m_bgMusic.openFromFile("assets/bgm.ogg");
    m_bgMusic.setLoop(true);

    
}

void Game::gameLoop(sf::Event event)
{

    sf::Sprite s(m_backGround);

    m_window.pollEvent(event);

    if (start == true)
    {
        if (event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::P)
        {
            pause = !pause; 
            if (pause == false)
            {
                aux++;
            }
        }

        if (pause == false)
        {          
            float dt = m_timer.restart().asSeconds();

            if (m_playing)
            {
                m_velocity += ACCELERATION * dt;
                m_distance += m_velocity * dt;

                if (m_distance > SPAWN_DIST)
                {                  
                    m_obstacles.emplace_front(static_cast<Obstacle::Type>(rand() % 2), BASE_COLOR, sf::Vector2f{ LANE_WIDTH / 2.f + LANE_WIDTH * (rand() % 3), 0 });
                    m_distance -= SPAWN_DIST;
                }

                for (std::list<Obstacle>::iterator it = m_obstacles.begin(); it != m_obstacles.end(); ++it)
                {
                    it->getShape().move(0, m_velocity * dt);
                    if (it->getShape().getGlobalBounds().top > WINDOW_HEIGHT - PLAYER_HEIGHT - OBJECT_SIZE && it->getShape().getGlobalBounds().top < WINDOW_HEIGHT - OBJECT_SIZE) // When an obstacle is at 'y' player area
                    {
                        if (it->getShape().getPosition().x == m_Player.getX())
                        {
                            if (it->getType() == Obstacle::Triangle)
                            {
                                m_playing = false;
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
                        if (it->getType() == Obstacle::Circle)
                        {
                            m_playing = false;
                            break;
                        }
                        

                        it = std::prev(m_obstacles.erase(it));
                    }
                }

                m_Player.handleInput(event);
                m_Player.update(dt);
                m_textScore.setString(" Puntaje: " + std::to_string(m_score));
            }
        }          
    }
    else
    {
        if (event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::Space)
        {
            start = true;
        }
    }
      
    
    

    m_window.clear(sf::Color::White);
    m_window.draw(s);
    
    if (pause == false)
    {
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
                            /*if (m_bgMusic.getStatus() != sf::SoundSource::Playing) m_bgMusic.play();*/
                            m_obstacles.clear();
                            m_score = 0;
                            m_velocity = INITIAL_VELOCITY;
                            m_distance = SPAWN_DIST;
                            m_playing = true;
                            start = false;
                            pause = false;
                            m_Player.reset();
                            
                            do
                            {
                                gameLoop(event);
                               
                            } while (m_playing == true);
                        }
                       
                        break;
                    case 1:
                       
                        if (menu.getKeyPressedItem() == 1)
                        {
                            showCredits = true;
                        }

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

        for (int i = 0; i < MENU_ARRAY_AMOUNT; i++)
        {
            m_window.draw(menuArray[i]);
        }

        if (showCredits == true)
        {
            for (int i = 0; i < CREDITS_ARRAY_AMOUNT; i++)
            {
                m_window.draw(creditsArray[i]);
            }

            if (menu.getKeyPressedItem() != 1)
            {
                showCredits = false;
            }
            
        }

        m_window.draw(m_textVersion);
       
        m_window.display();
    }
}



