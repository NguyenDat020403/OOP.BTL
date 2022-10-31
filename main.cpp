#include "play.h"
#include "Menu.h"
#include "WindowPlay.h"
#include "WindowOption.h"
#include "AboutWindow.h"
#include "GameManager.h"
//
int main()
{
	GameManager gm;
 	
	//Tao khung window hien thi menu
	RenderWindow window(VideoMode(650, 504), "MENU");
	
	//Background menu
	Texture m1,about;
	Image img1;
	img1.loadFromFile("images/chess-icon.png");
	window.setIcon(40,40,img1.getPixelsPtr());
	m1.loadFromFile("images/m1.png");
	about.loadFromFile("images/about.png");
	Sprite M1(m1),About(about);
	About.setPosition(610,10);
	Menu menu(650,504);
	Music music;
	music.openFromFile("music/MenuMusic.wav");
	//Bat su kien tu ban phim or chuot
	music.play();
	music.setVolume(20.f);
	while (window.isOpen())
	{
		
		Event event;
		while (window.pollEvent(event))
		{
			switch (event.type)
			{
			case Event::MouseButtonReleased:{
				if(event.mouseButton.button== Mouse::Left){
						Vector2i posMenu = Mouse::getPosition(window);
						if(posMenu.x >225 &&  posMenu.x < 470 && posMenu.y >126 && posMenu.y < 166 ){
							WindowPlay();
						}
						if(posMenu.x >245 &&  posMenu.x < 430 && posMenu.y >252 && posMenu.y < 312 ){
							menu.MoveDown();
							WindowOption();
						}
						if(posMenu.x >275 &&  posMenu.x < 370 && posMenu.y >378 && posMenu.y < 438 ){
							window.close();
						}	
						
						if(posMenu.x >610 &&  posMenu.x < 650 && posMenu.y >10 && posMenu.y < 40){
							AboutWindow();
						}
					}
				
				break;
			}	
			case Event::KeyReleased:
				switch (event.key.code)
				{
				case Keyboard::Up:
					menu.MoveUp();
					break;
				case Keyboard::Down:
					menu.MoveDown();
					break;
				case Keyboard::Escape:{
					window.close();
					break;
				}
				case Keyboard::Return:
					switch (menu.GetPressedItem())
					{
					case 0:{	
						
						WindowPlay();
						break;
					} 
					case 1:{
						
						WindowOption();			
						break;
					}
					case 2:
						window.close();
						break;
					}
				}
				break;
			case Event::Closed:
				window.close();
				break;
			}
		}
		window.clear();
		window.draw(M1);
		window.draw(About);
		menu.draw(window);
		window.display();
	}
}

