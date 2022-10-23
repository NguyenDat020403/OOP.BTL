#include "AboutWindow.h"


void AboutWindow(){
	//about
	
	RenderWindow about(VideoMode(650,504),"Thong tin");
	Image img1;
	img1.loadFromFile("images/abouticon.png");
	about.setIcon(50,50,img1.getPixelsPtr());
	Texture tt,tt2,back;
	tt.loadFromFile("images/a5.png");
	tt2.loadFromFile("images/a6.png");
	back.loadFromFile("images/back2.png");
	Sprite TT(tt),TT2(tt2),Back(back);
	Back.setPosition(550,430);
	int dem=0;
	while(about.isOpen()){
		Event event1;
		while(about.pollEvent(event1)){
			if (event1.type == Event::Closed)
				about.close();
			if (event1.type == Event::MouseButtonReleased)
			{
				if (event1.mouseButton.button == Mouse::Left){
					Vector2i posPlay = Mouse::getPosition(about);
					if(posPlay.x>550 && posPlay.x <620 && posPlay.y >430 && posPlay.y <500){
						about.close();
					}
					if(posPlay.x>60 && posPlay.x <150 && posPlay.y >465 && posPlay.y <490){
						dem++;
					}
				}
			}	
		}
		
		about.clear();
		if(dem%2==0){
			about.draw(TT);	
		}else{
			about.draw(TT2);	
		}
			
		about.draw(Back);	
		about.display();
	}	
}

