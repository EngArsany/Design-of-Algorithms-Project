#include <bits/stdc++.h>
using namespace std;

class Point
{
private:
    double x, y;

public:
    Point(int x, int y){
        this->x = x;
        this->y = y;
    }

    double getX(){
        return x;
    }
    double getY(){
        return y;
    }

};

double distance(Point *a, Point *b)
{ // root( (x1-x2)^2 - (y1-y2)^2 )
    double differenceX = a->getX() - b->getX();
    double differenceY = a->getY() - b->getY();
    return sqrt(pow(differenceX,2)+  pow(differenceY,2));
}
int main()
{
      // Assume points are given in an array
    vector<Point> myVector = {Point(3,4), Point(5,6)};



}