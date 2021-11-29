#pragma once
#include "SFML/Graphics.hpp"

#define ARRAY_AMOUNT 3

class Menu
{
private:
	int selectedItemIndex;

	
	

public:
	Menu(sf::RenderWindow& window, sf::Font m_font);
	~Menu();

	void draw(sf::RenderWindow &window);
	void moveUp(sf::Text menuArray[]);
	void moveDown(sf::Text menuArray[]);
	int getKeyPressedItem() { return selectedItemIndex; }

};