#pragma once
#include "SFML/Graphics.hpp"



class Menu
{
private:
	int selectedItemIndex;

	
	

public:
	Menu(sf::RenderWindow& window, sf::Font m_font);
	~Menu();

	void moveUp(sf::Text menuArray[]);
	void moveDown(sf::Text menuArray[]);
	int getKeyPressedItem();

};