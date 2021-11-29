#pragma once
#include "SFML/Graphics.hpp"

#define MAX_PHRASES_CREDITS 3

class Credits
{
private:
	sf::Text phrases[MAX_PHRASES_CREDITS];

public:
	Credits(sf::Font m_font, sf::RenderWindow m_window);

	sf::Text getPhrases();



};
