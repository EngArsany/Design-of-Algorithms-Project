#include <bits/stdc++.h>
using namespace std;

class Point
{
private:
    double x, y;

public:
    Point(double x, double y)
    {
        this->x = x;
        this->y = y;
    }
    bool operator==(const Point &other) const
    {
        return x == other.x && y == other.y;
    }
    double getX()
    {
        return x;
    }
    double getY()
    {
        return y;
    }

    void print()
    {
        cout << "(" << x << ", " << y << "), ";
    }
};

double distance(Point *a, Point *b)
{ // root( (x1-x2)^2 - (y1-y2)^2 )
    double differenceX = a->getX() - b->getX();
    double differenceY = a->getY() - b->getY();
    return sqrt(pow(differenceX, 2) + pow(differenceY, 2));
}
int calculateMaxDistance(const vector<Point> &points)
{
    double maxDistance = -1;
    for (int i = 0; i < points.size(); i++)
    {
        for (int j = i; j < points.size(); j++)
        {
            double currentDistance = distance(&points[i], &points[j]);
            maxDistance = max(maxDistance, currentDistance);
        }
    }
}

bool isExist(const vector<Point> &points, Point a)
{
    for (size_t i = 0; i < points.size(); i++)
    {
        if (points[i] == a)
            return true;
    }
    return false;
}