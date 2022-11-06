#include "WindowOption.h"
#include "WindowPlay.h"
#include "ComputerPlay.h"
void WindowOption(){
	RenderWindow window1(VideoMode(650,504),"OPTIONS"); //tao cua so option
	Image img1;											//Tao icon tr�n thanh c�ng cu.
	img1.loadFromFile("images/optionicon.png");			// icon tu file nay`
	window1.setIcon(50,50,img1.getPixelsPtr());			// setup icon l�n m�n h�nh
	Texture m2,b1,people1,people2,computer1,computer2;	// Khai bao nhung~ h�nh anh? m2: back ground , b1: nut' quay tro? ve MENU , 
	m2.loadFromFile("images/backgroundOption.png");		// people1: h�nh bigPeople , people2: h�nh smallpeople, tuong tu voi computer
	b1.loadFromFile("images/back2.png");
	people1.loadFromFile("images/bigPeople.png");
	people2.loadFromFile("images/smallPeople.png");
	computer1.loadFromFile("images/bigRobot.png");
	computer2.loadFromFile("images/smallRobot.png");
	// Thi�t' l�p. sprite - thong qua vi�c d� khai b�o nhung~ Texture o? tr�n 
	Sprite M2(m2),B1(b1),People1(people1),People2(people2),C1(computer1),C2(computer2);  
	B1.setPosition(550,430);							//B1.setPosition(550,430): set vi. tri' cho B1 o? tr�n m�n h�nh - o? d�y la` x= 550, y = 430
	People1.setPosition(60,200);						//People1.setPosition(60,200): set vi. tr� cho h�nh people l�n m�n h�nh - x=60, y=200
	People2.setPosition(70,250);						// tuong tu
	C1.setPosition(430,200);							// tuong tu
	C2.setPosition(440,250);							// tuong tu
	//L� do su? dung 2 h�nh anh? people va computer de: khi di chuyen chuot. vao` hinh` anh people hay computer thi` hinh` anh? do' se~ duoc. phong' to ra
	
	int checkPeople=0,checkComputer=0;
	
	while(window1.isOpen()){   							//Khi cua so OPTION dang duoc mo ( isOpen() )
		Event event1;										//Khai b�o 1 bi�n' theo kieu? Event-> bat' su kien tu ban phim hoac chuot.	
		while(window1.pollEvent(event1)){				//pollEvent(event1): nhan. su kien vua duoc thuc hien (co the la chuot hoac ban phim) de? dua vao ham switch
			Vector2i posOption = Mouse::getPosition(window1);	//Vector2i posOption: khai b�o bi�n' posOption chua 2 gia tri (x,y) duoc nhan tu vi tri con tro chuot tren cua so Option
			switch(event1.type){//Kiem tra su kien: event1 (co the la chuot hoac ban phim)
				case Event::Closed:{ 		//Neu l� dong' cua? so Option thi` 				
					window1.close();		// => Dong' cua so ( .close() )
					break;
				}
	  	        case Event::MouseButtonReleased:{				// Neu la su kien: nhan' chuot 
	  	        	if (event1.mouseButton.button == Mouse::Left){		//nhan' chuot trai' (left mouse)
	  	        		if(posOption.x>70 && posOption.x <220 && posOption.y >250 && posOption.y <400){ //kiem tra vi tri con tro chuot o? hinh` People th� mo cua
	  	        			window1.close();															// so? choi 1vs1 (people vs people)
							WindowPlay();
						  }
	  	        		if(posOption.x>440 && posOption.x <590 && posOption.y >250 && posOption.y <400){//kiem tra vi tri con tro chuot o? hinh` Computer th� mo cua
	  	        			window1.close();															// so? choi voi may'
	  	        			ComputerPlay();
						  }
					}
					break;
				}
			}	
			if (event1.type == Event::MouseButtonReleased){
				if (event1.mouseButton.button == Mouse::Left){
					if(posOption.x>550 && posOption.x <620 && posOption.y >430 && posOption.y <500){//kiem tra vi tri con tro chuot o? hinh` back (quay tro ve MENU) th� dong'
							window1.close();														// cua so OPTION
					}
				}
			}
			// Ham` dung` de?: khi con tro chuot di chuyen vao hinh` PEOPLE (hay COMPUTER) thi' hinh` se~ duoc phong' to ra va` nguoc lai se duoc thu nho? lai.
			if(posOption.x>70 && posOption.x <220 && posOption.y >250 && posOption.y <400){
				checkPeople=1; // neu con tro chuot o hinh people tra ve gia tri 1
			}else{
				checkPeople=0;// neu con tro chuot khong o hinh people tra ve gia tri 0
			}
			if(posOption.x>440 && posOption.x <590 && posOption.y >250 && posOption.y <400){
				checkComputer=1;// neu con tro chuot o hinh computer tra ve gia tri 1
			}else{
				checkComputer=0;// neu con tro chuot khong o hinh computer tra ve gia tri 0
			}
			//
	}
		//C�c h�m ve~ len cua so?
		window1.clear();
		window1.draw(M2);//ve back ground
		window1.draw(B1);//ve hinh` back (d�u' quay tro lai. MENU)
		// h�m ve~ h�nh to hoac h�nh nho? t�y v�o con tro? chuot dang o? dau
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
		// .display() : Thuc hien tat ca cac len o tren (xuat len man hinh`);
		window1.display();
	}	
	
}


