#include "WindowOption.h"
#include "WindowPlay.h"
#include "ComputerPlay.h"
void WindowOption(){
	RenderWindow window1(VideoMode(650,504),"OPTIONS");
	Image img1;
	img1.loadFromFile("images/optionicon.png");
	window1.setIcon(50,50,img1.getPixelsPtr());
	Texture m2,b1,people1,people2,computer1,computer2;
	m2.loadFromFile("images/backgroundOption.png");
	b1.loadFromFile("images/back2.png");
	people1.loadFromFile("images/bigPeople.png");
	people2.loadFromFile("images/smallPeople.png");
	computer1.loadFromFile("images/bigRobot.png");
	computer2.loadFromFile("images/smallRobot.png");
	Sprite M2(m2),B1(b1),People1(people1),People2(people2),C1(computer1),C2(computer2);
	B1.setPosition(550,430);
	People1.setPosition(60,200);
	People2.setPosition(70,250);
	C1.setPosition(430,200);
	C2.setPosition(440,250);
	
	
	int checkPeople=0,checkComputer=0;
	
	while(window1.isOpen()){
	Event event1;
		while(window1.pollEvent(event1)){
			Vector2i posOption = Mouse::getPosition(window1);
			switch(event1.type){
				case Event::Closed:{
					window1.close();
					break;
				}
	  	        case Event::MouseButtonReleased:{
	  	        	if (event1.mouseButton.button == Mouse::Left){
	  	        		if(posOption.x>70 && posOption.x <220 && posOption.y >250 && posOption.y <400){
	  	        			window1.close();
							WindowPlay();
						  }
	  	        		if(posOption.x>440 && posOption.x <590 && posOption.y >250 && posOption.y <400){
	  	        			window1.close();
	  	        			ComputerPlay();
						  }
					}
					break;
				}
			}	
			if (event1.type == Event::MouseButtonPressed){
				if (event1.mouseButton.button == Mouse::Left){
					if(posOption.x>550 && posOption.x <620 && posOption.y >430 && posOption.y <500){
							window1.close();
					}
				}
			}
			
			if(posOption.x>70 && posOption.x <220 && posOption.y >250 && posOption.y <400){
				checkPeople=1;
			}else{
				checkPeople=0;
			}
			if(posOption.x>440 && posOption.x <590 && posOption.y >250 && posOption.y <400){
				checkComputer=1;
			}else{
				checkComputer=0;
			}
		
	}
		
		window1.clear();
		window1.draw(M2);
		window1.draw(B1);
		if(checkPeople==1){	
			window1.draw(People1);
		}else{
			window1.draw(People2);
		}
		if(checkComputer==1){	
			window1.draw(C1);
		}else{
			window1.draw(C2);
		}
		
		window1.display();
	}	
	
}


