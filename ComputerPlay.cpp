#include "ComputerPlay.h"
#include "Connector.hpp"

void ComputerPlay(){
	
	
	RenderWindow window(VideoMode(650, 504), "The Chess!");
	ConnectToEngine("stockfish.exe");
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
	turn.setPosition(520,50);			    
	SoundBuffer moveself;// Am thanh cua moi nuoc di
	moveself.loadFromFile("move-self.wav");
	Sound sfx;
	sfx.setBuffer(moveself);

	for(int i=0;i<32;i++) f[i].setTexture(t1);
	Sprite sBoard(t2);
	Sprite sBoard1(t3),back(t4),White(trang),Black(den);
	White.setPosition(545,100);
	Black.setPosition(545,100);
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

					move(str); 

					if (oldPos!=newPos) position+=str+" ";

					f[n].setPosition(newPos);         
					sfx.play();  
					  demnuoc++; 
				}                      
				break;
			}
		}
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
		}
		if (Keyboard::isKeyPressed(Keyboard::Space))
       {
         str =  getNextMove(position);
                   
         oldPos = toCoord(str[0],str[1]);
         newPos = toCoord(str[2],str[3]);
         
         for(int i=0;i<32;i++) if (f[i].getPosition()==oldPos) n=i;
         
         /////animation///////
         for(int k=0;k<50;k++)
          {
            Vector2f p = newPos - oldPos;
            f[n].move(p.x/50, p.y/50); 
            window.draw(sBoard);
            for(int i=0;i<32;i++) f[i].move(offset);
            for(int i=0;i<32;i++) window.draw(f[i]); window.draw(f[n]);
            for(int i=0;i<32;i++) f[i].move(-offset);
            window.display();
          }

        move(str);  position+=str+" ";
        f[n].setPosition(newPos); 
        }

		if (isMove && pos.x-dx< 392){
			f[n].setPosition(pos.x-dx,pos.y-dy);
			
		}
		
	   ////// draw  ///////
		window.clear(); // xoa mnan hinh
		window.draw(sBoard1);
		window.draw(sBoard); /// ve ban co 
		window.draw(turn);
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
	CloseConnection();

    
	
}

