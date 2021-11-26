#include "Player.h"
#include "Constants.h"

sf::Texture Player::m_carTexture;

Player::Player(const sf::Color& color, const sf::Vector2f& pos) : m_transition(0), m_lane(Left), m_shape({OBJECT_SIZE, CAR_HEIGHT}), m_center(pos)
{
    m_shape.setFillColor(color);
    m_shape.setOrigin(m_shape.getLocalBounds().width / 2, m_shape.getLocalBounds().height);
    m_shape.setPosition(m_center + sf::Vector2f{LANE_WIDTH / 2.f * m_lane, 0});
}

void Player::applyTexture()
{
    m_shape.setTexture(&m_carTexture);
}
void Player::setKeyLeft(sf::Keyboard::Key key)
{
    m_keyLeft = key;
}
void Player::setKeyRight(sf::Keyboard::Key key)
{
    m_keyRight = key;
}
void Player::handleInput(const sf::Event& event)
{
    if (event.type == sf::Event::KeyPressed && event.key.code == m_keyLeft)
    {
        setLane(static_cast<Lane>(m_lane - 1));           
    }
    else if (event.type == sf::Event::KeyPressed && event.key.code == m_keyRight)
    {
        setLane(static_cast<Lane>(m_lane + 1));
    }
}

Player::Lane Player::getLane()
{
    if (m_transition != 0)
        return (static_cast<int>(m_shape.getPosition().x / LANE_WIDTH) % 2) ? Player::Left : Player::Right;
    return m_lane;
}

void Player::reset(Lane lane)
{
    m_transition = 0;
    m_lane = lane;
    m_shape.setPosition(m_center + sf::Vector2f{LANE_WIDTH / 2.f * m_lane, 0});
}

void Player::update(float dt)
{
    if (m_transition > 0)
    {
        m_shape.move(CAR_TRANSITION_SPEED * dt, 0);
        if (m_shape.getPosition().x >= m_targetX)
        {
            m_transition = 0;
            m_shape.setPosition(m_targetX, m_shape.getPosition().y);
        }
    }
    else if (m_transition < 0)
    {
        m_shape.move(-CAR_TRANSITION_SPEED * dt, 0);
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
    m_targetX = m_center.x + LANE_WIDTH / 2.f * lane;
    m_transition = lane - m_lane;
    m_lane = lane;
}
