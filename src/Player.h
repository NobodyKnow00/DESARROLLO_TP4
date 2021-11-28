#ifndef Player_H
#define Player_H
#include <SFML/Graphics.hpp>

class Player : public sf::Drawable
{
    public:
        enum Lane { Left = -1, Middle = 0, Right = 1};
        Player(const sf::Color& color, const sf::Vector2f& pos);
        void handleInput(const sf::Event& event);
        Lane getLane();
        void applyTexture();
        static sf::Texture m_playerTexture;
        void update(float dt);
        void reset();
    protected:
        void draw(sf::RenderTarget& target, const sf::RenderStates states) const;
    private:
        void setLane(Lane lane);

        int m_transition;
        int m_targetX;
        Lane m_lane;
        sf::RectangleShape m_shape;
        sf::Keyboard::Key m_keyLeft;
        sf::Keyboard::Key m_keyRight;
        sf::Vector2f m_center;
};

#endif // Player_H
