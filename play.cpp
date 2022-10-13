#include "play.h"

int size = 56; // kich co cua moi o hay moi quan co (size anh)
Vector2f offset(28,28);// choquan co di vao dung o(moi lan di chuyen thi con con di tuong do)

Sprite f[32]; //figures // toa ra 1 cai mang co the chua 32 cai anh nho o trong cai background
string position="";

int board[8][8] = 
    {-1,-2,-3,-4,-5,-3,-2,-1,
     -6,-6,-6,-6,-6,-6,-6,-6,
      0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0,
      6, 6, 6, 6, 6, 6, 6, 6,
      1, 2, 3, 4, 5, 3, 2, 1};

string toChessNote(Vector2f p)
{
	string s = "";
	s += char(p.x/size+97);
	s += char(7-p.y/size+49);
	return s;
}

Vector2f toCoord(char a,char b)
{
   int x = int(a) - 97;
   int y = 7-int(b)+49;
   return Vector2f(x*size,y*size);
}

void move(string str)
{
    Vector2f oldPos = toCoord(str[0],str[1]);
    Vector2f newPos = toCoord(str[2],str[3]);

    for(int i=0;i<32;i++)
     if (f[i].getPosition()==newPos) f[i].setPosition(-100,-100);
        
    for(int i=0;i<32;i++)
     if (f[i].getPosition()==oldPos) f[i].setPosition(newPos);

    //castling       //if the king didn't move
    if (str=="e1g1") if (position.find("e1")==-1) move("h1f1"); 
    if (str=="e8g8") if (position.find("e8")==-1) move("h8f8");
    if (str=="e1c1") if (position.find("e1")==-1) move("a1d1");
    if (str=="e8c8") if (position.find("e8")==-1) move("a8d8");
}

void loadPosition()
{
    int k=0;
    for(int i=0;i<8;i++)
    for(int j=0;j<8;j++)
     {
       int n = board[i][j];
       if (!n) continue;
       int x = abs(n)-1;
       int y = n>0?1:0;
       f[k].setTextureRect( IntRect(size*x,size*y,size,size) );
       f[k].setPosition(size*j,size*i);
       k++;
     }

    for(int i=0;i<position.length();i+=5)
      move(position.substr(i,4));
}
