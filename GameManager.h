#include "play.h"
#include <unistd.h>
//sleep(...);
typedef struct
{
 Sprite s;
 int index ,cost;
}QuanCo;
class GameManager
{
public:
 QuanCo f[33]; //mang luu cac quan co
 Vector2f positiveMove[32];//vi tri cac nuoc co the di chuyen
 int positiveCount;// so nuoc co the di chuyen
 stack<Vector2f> posS;//luu tru vi tri cac nuoc di
 stack<int> nS;//luu tru index cua quan di

 void move(int n,Vector2f oldPos,Vector2f newPos);//ham di chuyen
 void Undo();//ham quay lai
 void Create();
 void Play();// choi: moi thao tac o day

 void PositiveXe(int n,int x,int y,int grid[9][9]);//tim cac nuoc co the di cua Quan Xe
 void PositiveTuong(int n,int x,int y,int grid[9][9]);
 void PositiveMa(int n,int x,int y,int grid[9][9]);
 void PositiveVua(int n,int x,int y,int grid[9][9]);
 void PositiveTot(int n,int x,int y,int grid[9][9]);

 void IncreasePositive(int i,int j);//tang so nuoc co the di
 void PositiveMoving(int n);//tim cac nuoc co the di ung voi index n
 //AI
 int CostMove();//gia tri diem cua toan bo ban co ung voi gia tri moi quan
 //int Minimax(int depth,bool luot);// Chien luoc Minimax
 int Alpha_Beta(int depth,bool luot,int alpha,int beta);//cat tia alpha beta
 Vector2f getNextMove(bool luot);// tra ve nuoc di tot nhat theo chien luoc phia tren
};
