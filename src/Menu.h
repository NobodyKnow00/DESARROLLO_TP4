#pragma once
#include "SFML/Graphics.hpp"

#define ARRAY_AMOUNT 3


class Menu
{
private:
	int selectedItemIndex;
	sf::Font font;
	sf::Text menu[ARRAY_AMOUNT];

public:
	Menu(float width, float height);
	~Menu();

	void draw(sf::RenderWindow &window);
	void moveUp();
	void moveDown();
	int getKeyPressedItem() { return selectedItemIndex; }

};