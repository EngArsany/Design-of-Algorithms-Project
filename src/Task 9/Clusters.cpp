#include <bits/stdc++.h>
using namespace std;

struct Point
{
    double x, y;
};

double distance(Point *a, Point *b)
{
    // root( (x1-x2)^2 - (y1-y2)^2 )

    double differenceX = a->x - b->x;
    double differenceY = a->y - b->y;
    return sqrt(pow(differenceX,2)+  pow(differenceY,2));
}
int main()
{
    auto a = new Point();
    auto b = new Point();
    a->x = 3;
    a->y = 5;
    b->x = 4;
    b->y = 7;

    cout << "Distance = " << distance(a, b);
}