#include "GameManager.h"
int GameManager::Alpha_Beta(int depth,bool luot,int alpha,int beta)
{
 if(depth==0){
  return CostMove();
 }
 Vector2f positiveMovetemp[32];//luu lai vi tri cac nuoc co the di
 if(luot==true){
  int bestMove=-10000;//gia cua bestMove ban dau
  for(int j=16;j<32;j++)//cac quan cua nguoi choi
  {
   if(f[j].s.getPosition()==Vector2f(-100,-100)) continue;
   PositiveMoving(j);
   int coun=positiveCount;//ta khong the dung PositiveCount vi no thay doi lien tuc khi ta de quy
   positiveCount=0;
   for (int i = 0; i < coun; i++)  positiveMovetemp[i]=positiveMove[i];  
   for(int i=0;i<coun;i++)
   {
    move(j,f[j].s.getPosition(),positiveMovetemp[i]);
    bestMove=max(bestMove,Alpha_Beta(depth-1,!luot,alpha,beta));
    //undo
    Undo();
    alpha=max(alpha,bestMove);
    if(beta<=alpha)  return bestMove;
   }
  }
  return bestMove;
 }
 else {
  int bestMove=10000;//gia cua bestMove ban dau
  for(int j=0;j<16;j++)//quan cua may
  {
   if(f[j].s.getPosition()==Vector2f(-100,-100)) continue;
   PositiveMoving(j);
   int coun=positiveCount;//ta khong the dung PositiveCount vi no thay doi lien tuc khi ta de quy
   positiveCount=0;
   for (int i = 0; i < coun; i++)  positiveMovetemp[i]=positiveMove[i];  
   for(int i=0;i<coun;i++)
   {
    move(j,f[j].s.getPosition(),positiveMovetemp[i]);
    bestMove=min(bestMove,Alpha_Beta(depth-1,!luot,alpha,beta));
    //undo
    Undo();
    beta=min(beta,bestMove);
    if(beta<=alpha)  return bestMove;
   }
  }
  return bestMove;
 }
}

void GameManager::IncreasePositive(int i,int j){
 positiveMove[positiveCount]=Vector2f(i*size,j*size)+offset;
 positiveCount++;
}

void GameManager::move(int n,Vector2f oldPos,Vector2f newPos)
{ 

 posS.push(oldPos);
 posS.push(newPos);
 nS.push(n);
 int y=int((newPos-offset).y/size);//kiem tra xem co phong hau hay khong
 //phong hau cho tot
 if(y==0 && f[n].index==6){
  nS.push(100);//de ty undo xoa phong hau di
  f[n].index=4;
  f[n].cost=90;
  f[n].s.setTextureRect(IntRect( 3*size,size,size,size));
 }
 if(y==7 && f[n].index==-6){
  nS.push(-100);
  f[n].index=-4;
  f[n].cost=-90;
  f[n].s.setTextureRect(IntRect( 3*size,0,size,size));
 }
 //di chuyen em an vao vi tri moi 
 for(int i=0;i<32;i++){
  if (f[i].s.getPosition()==newPos) {
   f[i].s.setPosition(-100,-100);//di chuyen em bi an ra khoi man hinh
   posS.push(newPos);
   posS.push(Vector2f(-100,-100));
   nS.push(i);
   break;//neu ta dat f[n].s.setPosition(newPos) len truoc ma ko co break=> bi mat not con nay
  }
 }
 f[n].s.setPosition(newPos);
}

void GameManager::Undo()
{
 int n= nS.top();
 nS.pop();
 Vector2f p=posS.top();//kiem tra xem co = (-100,-100) => day la con bi an
 posS.pop();
 Vector2f q=posS.top();
 posS.pop();
 if(n==100) {
  n=nS.top();
  nS.pop();
  f[n].index=6;
  f[n].cost=10;
  f[n].s.setTextureRect(IntRect( 5*size,size,size,size));
 }
 if(n==-100){
  n=nS.top();
  nS.pop();
  f[n].index=-6;
  f[n].cost=-10;
  f[n].s.setTextureRect(IntRect( 5*size,0,size,size));
 }
 f[n].s.setPosition(q);

 if(p==Vector2f(-100,-100))  Undo();// luc nay moi dy chuyen con an
}

void GameManager::Create()//gan gia tri can thiet vao danh sach Quan co
{
 positiveCount=0;//so nuoc co the di ban dau duong nhien =0(chua chon gi ca)
 int k=0;
 for(int i=0;i<8;i++){
  for(int j=0;j<8;j++)
  {
   int n = board[i][j];   
   if (!n) continue;
   int x = abs(n)-1;
   int y = n>0?1:0;
   f[k].index=n;
   f[k].s.setTextureRect( IntRect(size*x,size*y,size,size) );
   f[k].s.setPosition(size*j+offset.x,size*i+offset.y);
   //cost
   int v=0,g; 
   g=abs(f[k].index);
   if(g==1)  v=50;
   else if(g==2|| g==3)  v=30;
   else if(g==4)  v=90;
   else if(g==5)  v=900;
   else if(g==6)  v=10;
   f[k].cost=f[k].index/g*v;
   k++;
  }
 }
}

Vector2f GameManager::getNextMove(bool luot)
{
 Vector2f oldPos,newPos,oldPostemp,newPostemp;// ta can tim vi tri co minimax nho nhat de ung voi may( quan den)
 int minimaxtemp=10000,minimax=10000;
 int count1,n;
 Vector2f positiveMovetemp[32];

 for(int i=0;i<16;i++)
 {
  if(f[i].s.getPosition()==Vector2f(-100,-100)) continue;
  //////
  PositiveMoving(i);
  count1=positiveCount;//khong the dung PositiveCount vi no thay doi lien tuc khi ta de quy
  positiveCount=0;
  ///set///
  for (int k = 0; k < count1; k++) positiveMovetemp[k]=positiveMove[k];
  //set oldPos va newPos  tam thoi
  oldPostemp=f[i].s.getPosition();
  //newPostemp=positiveMove[0];
  for(int j=0;j<count1;j++)
  {
   move(i,oldPostemp,positiveMovetemp[j]);
   int alpha=-9999,beta=9999;
   int temp=Alpha_Beta(3,!luot,alpha,beta);
   if(minimaxtemp>temp){
    newPostemp=positiveMovetemp[j];
    minimaxtemp=temp;
   }
   Undo();
  }
  if(minimax>minimaxtemp){
   minimax=minimaxtemp;
   oldPos=oldPostemp;
   newPos=newPostemp;
   n=i;
  }
 }
 //lay cac thong tin nuoc di
 posS.push(oldPos);//luu tam o trong stack ty ra ngoai xoa di
 nS.push(n);
 return newPos;
}

int GameManager::CostMove()// don gian con nao bi chet thi khong tinh diem cua con day
{
 int s=0;
 for(int i=0;i<32;i++)
 {  
  if(f[i].s.getPosition()==Vector2f(-100,-100)) continue;//neu no da bi out-> ko tinh diem
  s+=f[i].cost;
 }
 return s;
}

void GameManager::PositiveTot(int n,int x,int y,int grid[9][9])
{
 int k=grid[x][y]/abs(grid[x][y]);// 1 hoac -1
 if((y==1 || y==6) &&grid[x][y-k]==0 && grid[x][y-2*k]==0 && y-2*k>=0 && y-2*k<8) IncreasePositive(x,y-2*k);
 if(grid[x][y-k]==0 && y-k>=0 && y-k<8)            IncreasePositive(x,y-k);
 if(grid[x+1][y-k]*grid[x][y]<0 && y-k>=0 && y-k<8 && x+1<8)       IncreasePositive(x+1,y-k);
 if(grid[x-1][y-k]*grid[x][y]<0 && y-k>=0 && y-k<8 && x-1>=0)      IncreasePositive(x-1,y-k);
}

void GameManager::PositiveVua(int n,int x,int y,int grid[9][9])//xet 8 vi tri co the di cua vua
{
 if((grid[x+1][y]==0||grid[x][y]*grid[x+1][y]<0) && x+1<8)     IncreasePositive(x+1,y);
 if((grid[x-1][y]==0||grid[x][y]*grid[x-1][y]<0) && x-1>=0)     IncreasePositive(x-1,y);
 if((grid[x+1][y+1]==0||grid[x][y]*grid[x+1][y+1]<0) && x+1<8 && y+1<8)  IncreasePositive(x+1,y+1);
 if((grid[x-1][y+1]==0||grid[x][y]*grid[x-1][y+1]<0) && x-1>=0 && y+1<8)  IncreasePositive(x-1,y+1);
 if((grid[x][y+1]==0||grid[x][y]*grid[x][y+1]<0) && y+1<8)     IncreasePositive(x,y+1);
 if((grid[x-1][y-1]==0||grid[x][y]*grid[x-1][y-1]<0) && x-1>=0 && y-1>=0) IncreasePositive(x-1,y-1);
 if((grid[x+1][y-1]==0||grid[x][y]*grid[x+1][y-1]<0) && y-1>=0 && x+1<8)  IncreasePositive(x+1,y-1);
 if((grid[x][y-1]==0||grid[x][y]*grid[x][y-1]<0) && y-1>=0)     IncreasePositive(x,y-1);
}

void GameManager::PositiveMa(int n,int x,int y,int grid[9][9])//xet 8 vi tri co the di cua ma
{
 if((grid[x+2][y+1]==0||grid[x][y]*grid[x+2][y+1]<0) && x+2<8 && y+1<8)  IncreasePositive(x+2,y+1);
 if((grid[x+2][y-1]==0||grid[x][y]*grid[x+2][y-1]<0) && y-1>=0 && x+2<8)  IncreasePositive(x+2,y-1);
 if((grid[x-2][y+1]==0||grid[x][y]*grid[x-2][y+1]<0) && x-2>=0 && y+1<8)  IncreasePositive(x-2,y+1);
 if((grid[x-2][y-1]==0||grid[x][y]*grid[x-2][y-1]<0) && x-2>=0 && y-1>=0) IncreasePositive(x-2,y-1);
 if((grid[x+1][y+2]==0||grid[x][y]*grid[x+1][y+2]<0) && x+1<8 && y+2<8)  IncreasePositive(x+1,y+2);
 if((grid[x-1][y+2]==0||grid[x][y]*grid[x-1][y+2]<0) && x-1>=0 && y+2<8)  IncreasePositive(x-1,y+2);
 if((grid[x+1][y-2]==0||grid[x][y]*grid[x+1][y-2]<0) && y-2>=0&& x+1<8)  IncreasePositive(x+1,y-2);
 if((grid[x-1][y-2]==0||grid[x][y]*grid[x-1][y-2]<0) && x-1>=0 && y-2>=0) IncreasePositive(x-1,y-2);
}

void GameManager::PositiveTuong(int n,int x,int y,int grid[9][9])//tu vi tri (x,y) xet ra 4 huong cheo
{
 for(int i=x+1,j=y+1;(i<8&&j<8);i++,j++)
 {
  if(grid[i][j]!=0) {
   if(grid[i][j]*grid[x][y]<0)  IncreasePositive(i,j);
   break;
  }
  IncreasePositive(i,j);
 }
 for(int i=x+1,j=y-1;(i<8&&j>=0);i++,j--)
 {
  if(grid[i][j]!=0) {
   if(grid[i][j]*grid[x][y]<0)  IncreasePositive(i,j);
   break;
  }
  IncreasePositive(i,j);
 }
 for(int i=x-1,j=y+1;(i>=0&&j<8);i--,j++)
 {
  if(grid[i][j]!=0) {
   if(grid[i][j]*grid[x][y]<0)  IncreasePositive(i,j);
   break;
  }
  IncreasePositive(i,j);
 }
 for(int i=x-1,j=y-1;(i>=0 && j>=0);i--,j--)
 {
  if(grid[i][j]!=0) {
   if(grid[i][j]*grid[x][y]<0)  IncreasePositive(i,j);
   break;
  }
  IncreasePositive(i,j);
 }
}

void GameManager::PositiveXe(int n,int x,int y,int grid[9][9])//tu vi tri (x,y) xet ra 4 huong ngang
{
 for(int i=x+1;i<8;i++)
 {
  if(grid[i][y]!=0) {
   if(grid[i][y]*grid[x][y]<0)  IncreasePositive(i,y); 
   break;
  }
  IncreasePositive(i,y); 
 }
 for(int i=x-1;i>=0;i--)
 {
  if(grid[i][y]!=0) {
   if(grid[i][y]*grid[x][y]<0)  IncreasePositive(i,y); 
   break;
  }
  IncreasePositive(i,y); 
 }
 for(int j=y+1;j<8;j++)
 {
  if(grid[x][j]!=0) {
   if(grid[x][j]*grid[x][y]<0)  IncreasePositive(x,j);
   break;
  }
  IncreasePositive(x,j);
 }
 for(int j=y-1;j>=0;j--)
 {
  if(grid[x][j]!=0) {
   if(grid[x][j]*grid[x][y]<0)  IncreasePositive(x,j);
   break;
  }
  IncreasePositive(x,j);
 }
}

void GameManager::PositiveMoving(int n)
{
 Vector2f pos=f[n].s.getPosition()-offset;
 int x=pos.x/size;
 int y=pos.y/size;

 int grid[9][9];//mang luoi(8x8) luu lai cac vi tri ban co:
 Vector2i vtri;
 for(int i=0;i<8;i++)
  for(int j=0;j<8;j++)
   grid[i][j]=0;// neu khong co quan co nao o O nay thi =0
 for(int j=0;j<32;j++)
 {
  vtri=Vector2i( f[j].s.getPosition()-offset);
  grid[vtri.x/size][vtri.y/size]=f[j].index;// neu co = index cua quan co
 }

 if(abs(f[n].index)==1)  PositiveXe(n,x,y,grid);//xe
 else if(abs(f[n].index)==2)  PositiveMa(n,x,y,grid);//ma
 else if(abs(f[n].index)==3)  PositiveTuong(n,x,y,grid);//tuong 
 else if(abs(f[n].index)==4)//hau: hop lai cac nuoc cua ca xe va tuong
 {
  PositiveXe(n,x,y,grid);
  PositiveTuong(n,x,y,grid);
 }
 else if(abs(f[n].index)==5)  PositiveVua(n,x,y,grid);//vua
 else   PositiveTot(n,x,y,grid); //tot
}
void GameManager::Play()
{
	RenderWindow window(VideoMode(650, 504), "The Chess!");
	Image img1;
	img1.loadFromFile("images/computericon.png");
	window.setIcon(50,50,img1.getPixelsPtr());
	Texture t1,t2,t3,t4,no,iyou,ibot;
	t1.loadFromFile("images/figures.png"); // quan co
	t2.loadFromFile("images/board.png"); // ban co
	t3.loadFromFile("images/a1.png"); // background
	t4.loadFromFile("images/back2.png");
	no.loadFromFile("images/no.png");
	iyou.loadFromFile("images/iconPeople.png");
	ibot.loadFromFile("images/iconRobot.png");
	Font font;
	if (!font.loadFromFile("font/rockston.ttf")){}
	
	Text turn;
	turn.setFont(font);
	turn.setString("TURN");
	turn.setCharacterSize(40);
	turn.setFillColor(Color::Black);
	turn.setPosition(520,165);
	
	Text bot;
	bot.setFont(font);
	bot.setString("BOT");
	bot.setCharacterSize(30);
	bot.setFillColor(Color::Black);
	bot.setPosition(540,30);
	
	Text you;
	you.setFont(font);
	you.setString("YOU");
	you.setCharacterSize(30);
	you.setFillColor(Color::Black);
	you.setPosition(540,380);
			    
	SoundBuffer moveself;// Am thanh cua moi nuoc di
	moveself.loadFromFile("move-self.wav");
	Sound sfx;
	sfx.setBuffer(moveself);


 	for(int i=0;i<32;i++) f[i].s.setTexture(t1);
 	Sprite sBoard1(t2),sBoard(t3);
 	Sprite sPositive(no),back(t4),IYOU(iyou),IBOT(ibot);
	IYOU.setPosition(533,213);
	IBOT.setPosition(533,213);
	back.setPosition(550,430);
 	Create();//khoi tao

	
	int demnuoc=0;
	bool LuotChoi=true;//luot choi : = true=> nguoi ... =false => may
	Vector2f oldPos,newPos;// luu vi tri click lan1 va lan2
	int n=0,click=0,count=0;
	Vector2i pos;//vitri chuot khi click
	while (window.isOpen())
	{
		Event e;
		while (window.pollEvent(e))
		{
		   	if (e.type == Event::Closed)
		    	window.close();
		   	////move back//////
		   	if (e.type == Event::KeyPressed)
			    if (e.key.code== Keyboard::BackSpace)
			    { 
					Undo();
				}
		  	 /////click///////
		  	if (e.type == Event::MouseButtonPressed)
			    if (e.mouseButton.button == Mouse::Left)
			    {
			     	pos = Mouse::getPosition(window) - Vector2i(offset);
			     	click++;
			    }     
		}
		if(LuotChoi==true)
		{
		   	if(click==1){
			    bool isMove=false;
			    for(int i=16;i<32;i++)
			    {
				    if(f[i].s.getGlobalBounds().contains(pos.x+offset.x,pos.y+offset.y))
				    {
					    isMove=true;
					    n=i;
					    f[n].s.setColor(Color::Green);
					    oldPos=f[n].s.getPosition();
				    }
			    }
			    if(!isMove)  click=0;
			    else{
					PositiveMoving(n);
					count=positiveCount;
					positiveCount=0;
				}
	  		 }
		   if(click==2)
		   {
			    f[n].s.setColor(Color::White);
			    int x=pos.x/size;   int y=pos.y/size;
			    newPos=Vector2f(x*size,y*size)+offset;
			    // new== 28 an vua -> youlose va ngc lai
			    if (f[28].s.getPosition()==Vector2f(-100,-100) ) {
						RenderWindow ketqua(VideoMode(480,400),"Final Result");
			            Image img1;
			            img1.loadFromFile("images/iconKQ.png");
			            ketqua.setIcon(52,52,img1.getPixelsPtr());
						Texture pl1;	            
			            pl1.loadFromFile("images/youlose.png");
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
							sleep(1);
							ketqua.close();
							window.close();
						}
			
				
							
			 			}
  		  //chi di chuyen trong vung positiveMove
			    for(int i=0;i<count;i++)
			    {
			    	if (positiveMove[i]==newPos){
				    	
				      	move(n,oldPos,newPos);
				      	LuotChoi=!LuotChoi; 
				      	demnuoc++;
			  		}
			    }
				    //reset
				    count=0;
				    click=0;
			} 
		}
		else  //computer moving
		{
		  	sleep(1.5);
			newPos= getNextMove(LuotChoi);
			
			int c=nS.top();   
			nS.pop();//lay dk thong tin roi xoa di
			oldPos=posS.top();
			if (f[4].s.getPosition() == Vector2f(-100,-100) ) {
					RenderWindow ketqua(VideoMode(480,259),"Final Result");
		            Image img1;
		            img1.loadFromFile("images/iconKQ.png");
		            ketqua.setIcon(52,52,img1.getPixelsPtr());
					Texture pl1;	            
		            pl1.loadFromFile("images/win1.png");
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
						sleep(1);
						ketqua.close();
						window.close();
					}
								
		 	}
			posS.pop();//vi ham move tu nhet trong stack roi
			move(c,oldPos,newPos);
			LuotChoi=!LuotChoi;
			demnuoc++;
			//reset 
			click=0;
		}
  	
  ////// draw  ///////
		window.clear();
		window.draw(sBoard);
		window.draw(sBoard1); /// ve ban co 
		window.draw(turn);
		window.draw(you);
		window.draw(bot);
		if(demnuoc %2 == 0){
			window.draw(IYOU);
		}else{
			window.draw(IBOT);
		}
		window.draw(back);
		for(int i=0;i<count;i++){
		   	sPositive.setPosition(positiveMove[i]);
		   	window.draw(sPositive);
		}
		for(int i=0;i<32;i++) {
		   	window.draw(f[i].s);
		}
		  	window.display();
	}
}

