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
 QuanCo f[33];
 Vector2f positiveMove[32];
 int positiveCount;
 stack<Vector2f> posS;
 stack<int> nS;

 void move(int n,Vector2f oldPos,Vector2f newPos);
 void Undo();
 void Create();
 void Play();

 void PositiveXe(int n,int x,int y,int grid[9][9]);
 void PositiveTuong(int n,int x,int y,int grid[9][9]);
 void PositiveMa(int n,int x,int y,int grid[9][9]);
 void PositiveVua(int n,int x,int y,int grid[9][9]);
 void PositiveTot(int n,int x,int y,int grid[9][9]);

 void IncreasePositive(int i,int j);
 void PositiveMoving(int n);

 int CostMove();
 int Alpha_Beta(int depth,bool luot,int alpha,int beta);
 Vector2f getNextMove(bool luot);
};
