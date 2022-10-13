#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
using namespace sf;
using namespace std;

extern  int size; // kich co cua moi o hay moi quan co (size anh)
extern  Vector2f offset;// choquan co di vao dung o(moi lan di chuyen thi con con di tuong do)

extern  Sprite f[]; //figures // toa ra 1 cai mang co the chua 32 cai anh nho o trong cai background
extern  string position;

extern  int board[][8];

     
 
      
string toChessNote(Vector2f p);
Vector2f toCoord(char a,char b);
void move(string str);
void loadPosition();
