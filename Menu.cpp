#include "Menu.h"
Menu::Menu(float width, float height)
{
	if (!font.loadFromFile("C:\\Users\\DatNgu\\Desktop\\chess\\font\\rockston.ttf"))
	{
		// handle error
	}
	
	menu[0].setFont(font);
	menu[0].setFillColor(sf::Color::Red);
	menu[0].setString("Play");
	menu[0].setCharacterSize(40);
	menu[0].setPosition(sf::Vector2f((width / 2), height / (MAX_NUMBER_OF_ITEMS + 1) * 1));

	menu[1].setFont(font);
	menu[1].setFillColor(sf::Color::White);
	menu[1].setString("Options");
	menu[1].setCharacterSize(40);
	menu[1].setPosition(sf::Vector2f((width / 2), height / (MAX_NUMBER_OF_ITEMS + 1) * 2));

	menu[2].setFont(font);
	menu[2].setFillColor(sf::Color::White);
	menu[2].setString("Exit");
	menu[2].setCharacterSize(40);
	menu[2].setPosition(sf::Vector2f((width / 2), height / (MAX_NUMBER_OF_ITEMS + 1) * 3));

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
	if (selectedItemIndex + 1 < MAX_NUMBER_OF_ITEMS)
	{
		menu[selectedItemIndex].setFillColor(sf::Color::White);
		selectedItemIndex++;
		menu[selectedItemIndex].setFillColor(sf::Color::Red);
	}
}
//void case1(){
//						Font font;
//						if (!font.loadFromFile("C:\\Users\\DatNgu\\Desktop\\chess\\font\\rockston.ttf"))
//						{
//							// handle error
//						}
//						Text c,c1;
//						c.setFont(font);c1.setFont(font);
//						c.setString("Dang phat trien");c1.setString("<-Back");
//						c.setFillColor(Color::White);c1.setFillColor(Color::Red);
//						c.setPosition(290,150);c1.setPosition(700,400);
//						while(window.isOpen()){
//							Event event;
//							while(window.pollEvent(event)){
//								if (event.type == Event::Closed)
//						                window.close();
//								if(event.type == Event::KeyPressed){
//									if (event.key.code == Keyboard::Return)
//									{
//										window.clear();
//										window.draw(H1);
//										window.draw(c);		
//										window.draw(c1);						
//										window.display();
//										
//									}
//								}
//							}
//						}
//}
