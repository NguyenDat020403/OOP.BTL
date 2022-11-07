#include "Menu.h"
Menu::Menu(float width, float height)
{
	if (!font.loadFromFile("font/rockston.ttf"))
	{
		// handle error
	}
	//Play
	menu[0].setFont(font);
	menu[0].setFillColor(sf::Color::Red);
	menu[0].setString("Play 1 vs 1");
	menu[0].setCharacterSize(40);
	menu[0].setPosition(sf::Vector2f((width / 2)-110, height / (MAX_NUMBER_OF_ITEMS + 1) * 1));
	//Option
	menu[1].setFont(font);
	menu[1].setFillColor(sf::Color::White);
	menu[1].setString("Options");
	menu[1].setCharacterSize(40);
	menu[1].setPosition(sf::Vector2f((width / 2)-85, height / (MAX_NUMBER_OF_ITEMS + 1) * 2));
	//Exit
	menu[2].setFont(font);
	menu[2].setFillColor(sf::Color::White);
	menu[2].setString("Exit");
	menu[2].setCharacterSize(40);
	menu[2].setPosition(sf::Vector2f((width / 2)-45, height / (MAX_NUMBER_OF_ITEMS + 1) * 3));
	selectedItemIndex = 0;
}
Menu::~Menu()
{
}
void Menu::draw(RenderWindow &window)
{
	for (int i = 0; i < MAX_NUMBER_OF_ITEMS; i++)
	{
		window.draw(menu[i]);
	}
}
void Menu::MoveUp()
{
	if (selectedItemIndex - 1 >= 0)
	{
		menu[selectedItemIndex].setFillColor(sf::Color::White);
		selectedItemIndex--;
		menu[selectedItemIndex].setFillColor(sf::Color::Red);
	}
}
void Menu::MoveDown()
{
	if (selectedItemIndex + 1 < 2)
	{
		menu[selectedItemIndex].setFillColor(sf::Color::White);
		selectedItemIndex++;
		menu[selectedItemIndex].setFillColor(sf::Color::Red);
	}
}


