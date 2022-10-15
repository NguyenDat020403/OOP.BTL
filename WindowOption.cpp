#include "WindowOption.h"


void WindowOption(){
	RenderWindow window1(VideoMode(650,504),"OPTIONS");
	Texture m2,b1;
	m2.loadFromFile("images/m1.png");
	b1.loadFromFile("images/back2.png");
	Font font;
	if (!font.loadFromFile("font/rockston.ttf"))
	{
	}
	Text c;
	c.setFont(font);
	c.setString("Dang phat trien !");
	c.setCharacterSize(40);
	c.setFillColor(Color::Red);
	c.setPosition(200,200);
	Sprite M2(m2),B1(b1);
	B1.setPosition(550,430);
	while(window1.isOpen()){
	Event event1;
		while(window1.pollEvent(event1)){
			if (event1.type == Event::Closed)
	  	          window1.close();
			if (event1.type == Event::MouseButtonReleased)
			{
				if (event1.mouseButton.button == Mouse::Left){
					Vector2i posPlay = Mouse::getPosition(window1);
					if(posPlay.x>550 && posPlay.x <620 && posPlay.y >430 && posPlay.y <500){
						window1.close();
					}
				}
			}
		}
		window1.clear();
		window1.draw(M2);
		window1.draw(B1);
		window1.draw(c);
		window1.display();
	}	
}
