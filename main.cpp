
#include "play.h"
#include "Menu.h"
#include "WindowPlay.h"
#include "WindowOption.h"
int main()
{
	//Tao khung window hien thi menu
	RenderWindow window(VideoMode(650, 504), "MENU");
	//Background menu
	Texture m1;
	m1.loadFromFile("C:\\Users\\DatNgu\\Desktop\\OOP\\images\\m1.png");
	Sprite M1(m1);
	Menu menu(650,504);
	Music music;
	music.openFromFile("C:\\Users\\DatNgu\\Desktop\\OOP\\music\\MenuMusic.wav");
	//Bat su kien tu ban phim or chuot
	while (window.isOpen())
	{
		music.play();
		Event event;
		while (window.pollEvent(event))
		{
			switch (event.type)
			{
			case Event::MouseButtonReleased:{
				if(event.mouseButton.button== Mouse::Left){
						Vector2i posMenu = Mouse::getPosition(window);
						if(posMenu.x >325 &&  posMenu.x < 420 && posMenu.y >126 && posMenu.y < 166 ){
							music.pause();
							WindowPlay();
						}
						if(posMenu.x >325 &&  posMenu.x < 500 && posMenu.y >252 && posMenu.y < 312 ){
							music.pause();
							WindowOption();
						}
						if(posMenu.x >325 &&  posMenu.x < 420 && posMenu.y >378 && posMenu.y < 438 ){
							window.close();
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
						music.pause();	
						WindowPlay();
						break;
					} 
					case 1:{
						music.pause();
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
		menu.draw(window);
		window.display();
	}
}
