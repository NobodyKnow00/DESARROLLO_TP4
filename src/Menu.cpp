#include "Menu.h"
#include "SFML/Graphics.hpp"
#include <iostream>

Menu::Menu(float width, float height)
{
	menu[0].setFillColor(sf::Color::Red);
	menu[0].setString("Play");
	menu[0].setPosition(sf::Vector2f(width / 2, height / (ARRAY_AMOUNT + 1) * 1));

	menu[1].setFillColor(sf::Color::White);
	menu[1].setString("Credits");
	menu[1].setPosition(sf::Vector2f(width / 2, height / (ARRAY_AMOUNT + 1) * 2));

	menu[2].setFillColor(sf::Color::White);
	menu[2].setString("Exit");
	menu[2].setPosition(sf::Vector2f(width / 2, height / (ARRAY_AMOUNT + 1) * 3));

	selectedItemIndex = 0;
}
Menu::~Menu()
{

}
void Menu::draw(sf::RenderWindow &window)
{
	for (int i = 0; i < ARRAY_AMOUNT; i++)
	{
		window.draw(menu[i]);
	}
}

void Menu::moveUp()
{
	if (selectedItemIndex - 1 >= 0)
	{
		menu[selectedItemIndex].setFillColor(sf::Color::White);
		selectedItemIndex--;
		menu[selectedItemIndex].setFillColor(sf::Color::Red);
	}
}

void Menu::moveDown()
{
	if (selectedItemIndex + 1 < ARRAY_AMOUNT)
	{
		menu[selectedItemIndex].setFillColor(sf::Color::White);
		selectedItemIndex++;
		menu[selectedItemIndex].setFillColor(sf::Color::Red);
	}
}