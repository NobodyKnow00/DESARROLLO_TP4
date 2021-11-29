#include "Menu.h"
#include "SFML/Graphics.hpp"
#include <iostream>

Menu::Menu(sf::RenderWindow& m_window, sf::Font m_font)
{
	

	selectedItemIndex = 0;
}
Menu::~Menu()
{

}
void Menu::draw(sf::RenderWindow &window)
{
	
}

void Menu::moveUp(sf::Text menuArray[])
{
	if (selectedItemIndex - 1 >= 0)
	{		
		menuArray[selectedItemIndex].setFillColor(sf::Color::White);
		selectedItemIndex--;		
		menuArray[selectedItemIndex].setFillColor(sf::Color::Red);
	}
}

void Menu::moveDown(sf::Text menuArray[])
{
	if (selectedItemIndex + 1 < ARRAY_AMOUNT)
	{		
		menuArray[selectedItemIndex].setFillColor(sf::Color::White);
		selectedItemIndex++;	
		menuArray[selectedItemIndex].setFillColor(sf::Color::Red);
	}
}