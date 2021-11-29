#include "Credits.h"



Credits::Credits(sf::Font m_font, sf::RenderWindow m_window)
{
    phrases[0].setFont(m_font);
    phrases[0].setCharacterSize(30);
    phrases[0].setFillColor(sf::Color::White);
    phrases[0].setString("Play");
    phrases[0].setPosition((m_window.getSize().x - menuArray[0].getLocalBounds().width) / 2.f, ((m_window.getSize().y - menuArray[0].getLocalBounds().height) / 2.f) - 50);

    phrases[1].setFont(m_font);
    phrases[1].setCharacterSize(30);
    phrases[1].setFillColor(sf::Color::White);
    phrases[1].setString("Play");
    phrases[1].setPosition((m_window.getSize().x - menuArray[0].getLocalBounds().width) / 2.f, ((m_window.getSize().y - menuArray[0].getLocalBounds().height) / 2.f) - 50);

    phrases[2].setFont(m_font);
    phrases[2].setCharacterSize(30);
    phrases[2].setFillColor(sf::Color::White);
    phrases[2].setString("Play");
    phrases[2].setPosition((m_window.getSize().x - menuArray[0].getLocalBounds().width) / 2.f, ((m_window.getSize().y - menuArray[0].getLocalBounds().height) / 2.f) - 50);
}

sf::Text Credits::getPhrases()
{

}