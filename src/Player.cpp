#include "Player.h"
#include "Constants.h"

sf::Texture Player::m_playerTexture;

Player::Player(const sf::Color& color, const sf::Vector2f& pos) : m_shape({OBJECT_SIZE, PLAYER_HEIGHT}), m_center(pos)
{
    m_shape.setFillColor(color);
    m_shape.setOrigin(m_shape.getLocalBounds().width / 2, m_shape.getLocalBounds().height);
    m_center.x = LANE_WIDTH * 3 / 2;
    m_shape.setPosition(m_center);

    m_transition = 0;
    m_lane = Middle;

    m_keyLeft = sf::Keyboard::Left;
    m_keyRight = sf::Keyboard::Right;
}

void Player::applyTexture()
{
    m_shape.setTexture(&m_playerTexture);
}

void Player::handleInput(const sf::Event& event)
{
    if (event.type == sf::Event::KeyPressed && event.key.code == m_keyLeft)
    {
        if (m_lane != Left)
        {
            setLane(static_cast<Lane>(m_lane - 1));
        }
        
    }
    else if (event.type == sf::Event::KeyPressed && event.key.code == m_keyRight)
    {
        if (m_lane != Right)
        {
            setLane(static_cast<Lane>(m_lane + 1));
        }
    }
}

Player::Lane Player::getLane()
{
    if (m_transition != 0)
        return (static_cast<int>(m_shape.getPosition().x / LANE_WIDTH) % 2) ? Player::Left : Player::Right;
    return m_lane;
}

void Player::reset()
{
    m_transition = 0;
    m_shape.setPosition(m_center);
}

void Player::update(float dt)
{
    if (m_transition > 0)
    {
        m_shape.move(PLAYER_TRANSITION_SPEED * dt, 0);
        if (m_shape.getPosition().x >= m_targetX)
        {
            m_transition = 0;
            m_shape.setPosition(m_targetX, m_shape.getPosition().y);
        }
    }
    else if (m_transition < 0)
    {
        m_shape.move(-PLAYER_TRANSITION_SPEED * dt, 0);
        if (m_shape.getPosition().x <= m_targetX)
        {
            m_transition = 0;
            m_shape.setPosition(m_targetX, m_shape.getPosition().y);
        }
    }
}

void Player::draw(sf::RenderTarget& target, const sf::RenderStates states) const
{
    target.draw(m_shape, states);
}

void Player::setLane(Player::Lane lane)
{
    if (lane == Left)
    {
        m_targetX = 120 - m_shape.getSize().x;
    }
    else if (lane == Middle)
    {
        m_targetX = m_center.x;
    }
    else
    {
        m_targetX = 240 + m_shape.getSize().x;
    }
   
    m_transition = lane - m_lane;
    m_lane = lane;
}