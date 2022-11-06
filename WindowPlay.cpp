#include "WindowPlay.h"
#include "GameManager.h"

void WindowPlay(){
	RenderWindow window(VideoMode(650, 504), "The Chess!");  // tao cua so moi 
	Image img1;
	img1.loadFromFile("images/playicon.png");
	window.setIcon(50,50,img1.getPixelsPtr());
	Texture t1,t2,t3,t4,trang,den;
	t1.loadFromFile("images/figures.png"); // quan co
	t2.loadFromFile("images/board.png"); // ban co
	t3.loadFromFile("images/a1.png"); // background
	t4.loadFromFile("images/back2.png");
	trang.loadFromFile("images/trang.png");
	den.loadFromFile("images/den.png");
	Font font;
	if (!font.loadFromFile("font/rockston.ttf"))
	{
	}
	Text turn;
	turn.setFont(font);
	turn.setString("TURN");
	turn.setCharacterSize(40);
	turn.setFillColor(Color::Black);
	turn.setPosition(520,165);
	
	Text pl1;
	pl1.setFont(font);
	pl1.setString("PLAYER 2");
	pl1.setCharacterSize(30);
	pl1.setFillColor(Color::Black);
	pl1.setPosition(490,30);
	
	Text pl2;
	pl2.setFont(font);
	pl2.setString("PLAYER 1");
	pl2.setCharacterSize(30);
	pl2.setFillColor(Color::Black);
	pl2.setPosition(490,380);
				    
	SoundBuffer moveself;// Am thanh cua moi nuoc di
	moveself.loadFromFile("move-self.wav");
	Sound sfx;
	sfx.setBuffer(moveself);

	for(int i=0;i<32;i++) f[i].setTexture(t1);
	Sprite sBoard(t2);
	Sprite sBoard1(t3),back(t4),White(trang),Black(den);
	White.setPosition(545,213);
	Black.setPosition(545,213);
	back.setPosition(550,430);
	loadPosition();
	
	
	int demnuoc=0;
	
	bool isMove=false;
	float dx=0, dy=0;
	Vector2f oldPos,newPos;
	string str;
	int n=0;
	// Bat su kien ban phim va chuot
	while (window.isOpen())
 	{
		Vector2i pos = Mouse::getPosition(window) - Vector2i(offset);
		Event event;
		while (window.pollEvent(event))
		{
		
		switch(event.type){
			case Event::Closed:{
				int u=0;
				while(u!=1){
					for(int i=0;i<32;i++) f[i].move(offset);// 
					for(int i=0;i<32;i++) window.draw(f[i]); window.draw(f[n]);
					for(int i=0;i<32;i++) f[i].move(-offset);
					u=1;
				}
				window.close();	
				break;
			}
			case Event::MouseButtonPressed:{
				if (event.mouseButton.button == Mouse::Left){
						for(int i=0;i<32;i++){
							if (f[i].getGlobalBounds().contains(pos.x,pos.y))
								{
									isMove=true; n=i;
									dx=pos.x - f[i].getPosition().x;
									dy=pos.y - f[i].getPosition().y;
									oldPos  =  f[i].getPosition();
								}
						}
						   				
				}
				break;
			}
			case Event::MouseButtonReleased:{
				if (event.mouseButton.button == Mouse::Left)
				{
					isMove=false;
					Vector2f p = f[n].getPosition() + Vector2f(size/2,size/2);
				
					newPos = Vector2f( size*int(p.x/size), size*int(p.y/size) );

					str = toChessNote(oldPos)+toChessNote(newPos);
					for(int i=0;i<32;i++){
		    	
			    	if( f[4].getPosition()  == newPos && f[4].getPosition()  !=oldPos){
				     	Font font;
						if (!font.loadFromFile("font/rockston.ttf"))
						{
						}
				     	RenderWindow ketqua(VideoMode(480,259),"Final Result");
			            Image img1;
			            img1.loadFromFile("images/iconKQ.png");
			            ketqua.setIcon(52,52,img1.getPixelsPtr());
			            Texture pl2;	            
			            pl2.loadFromFile("images/winner1.png");
			            Sprite PL2(pl2);
			            
						while(ketqua.isOpen()){
							Event temp;
							while(ketqua.pollEvent(temp)){
								if (temp.type == Event::Closed)
									ketqua.close();
							}
							ketqua.clear();
							ketqua.draw(PL2);
							ketqua.display();
							sleep(2);
							ketqua.close();
							for(int i=0;i<32;i++) f[i].setTexture(t1);
							loadPosition();
							window.close();	
							
						}
						break;
					}
					else if( f[28].getPosition() == newPos && f[28].getPosition()  !=oldPos){
						RenderWindow ketqua(VideoMode(480,259),"Final Result");
			            Image img1;
			            img1.loadFromFile("images/iconKQ.png");
			            ketqua.setIcon(52,52,img1.getPixelsPtr());
						Texture pl1;	            
			            pl1.loadFromFile("images/winner2.png");
			            Sprite PL1(pl1);
			
						while(ketqua.isOpen()){
							Event temp;
							while(ketqua.pollEvent(temp)){
								if (temp.type == Event::Closed)
									ketqua.close();
							}
							ketqua.clear();
							ketqua.draw(PL1);
							ketqua.display();
							sleep(2);
							ketqua.close();
							for(int i=0;i<32;i++) f[i].setTexture(t1);
							loadPosition();
							window.close();	
							
						}
						break;
					}
					}
					move(str); 

					if (oldPos!=newPos) position+=str+" ";
					else demnuoc--;
					f[n].setPosition(newPos);         
					sfx.play();  
					//turn
					Vector2i poS = Mouse::getPosition(window);
					if(poS.x<448 && poS.x>28 &&poS.y<448 && poS.y>28){
						demnuoc++; 
					}
					//turn
					  
				}                      
				break;
			}
		}
		//back
		if (event.type == Event::MouseButtonPressed){
			if (event.mouseButton.button == Mouse::Left){
					
				Vector2i posPlay = Mouse::getPosition(window);
				if(posPlay.x>550 && posPlay.x <620 && posPlay.y >430 && posPlay.y <500){
					int u=0;
					while(u!=1){
						for(int i=0;i<32;i++) f[i].move(offset);// 
						for(int i=0;i<32;i++) window.draw(f[i]); window.draw(f[n]);
						for(int i=0;i<32;i++) f[i].move(-offset);
						u=1;
					}
					window.close();
								
				}		
			}
		}
		

		if (isMove && pos.x-dx< 420){
			f[n].setPosition(pos.x-dx,pos.y-dy);
			
		}
		
	   ////// draw  ///////
		window.clear(); // xoa mnan hinh
		window.draw(sBoard1);
		window.draw(sBoard); /// ve ban co 
		window.draw(turn);
		window.draw(pl1);
		window.draw(pl2);
		window.draw(back);
		if(demnuoc %2 == 0){
			window.draw(White);
		}else{
			window.draw(Black);
		}
		
		for(int i=0;i<32;i++) f[i].move(offset);// 
		for(int i=0;i<32;i++) window.draw(f[i]); window.draw(f[n]);
		for(int i=0;i<32;i++) f[i].move(-offset);
		
		window.display();
	}
	}
	
}


