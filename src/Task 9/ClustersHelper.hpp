#include <bits/stdc++.h>
using namespace std;

class Point
{
private:
    double x, y;
    double EPSILON = 1;

public:
    Point(double x, double y)
    {
        this->x = x;
        this->y = y;
    }
    bool operator==(const Point &other) const
    {
        bool equalX = abs(x - other.x) < EPSILON;
        bool equalY = abs(y - other.y) < EPSILON;

        return equalX && equalY;
    }
    bool operator!=(const Point &other) const
    {
        bool equalX = abs(x - other.x) >= EPSILON;
        bool equalY = abs(y - other.y) >= EPSILON;

        return equalX && equalY;
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

double pointDistance(Point *a, Point *b)
{ // root( (x1-x2)^2 - (y1-y2)^2 )
    double differenceX = a->getX() - b->getX();
    double differenceY = a->getY() - b->getY();
    return sqrt(pow(differenceX, 2) + pow(differenceY, 2));
}
static int calculateMaxDistance(vector<Point> &points)
{
    double maxDistance = -1;
    for (int i = 0; i < points.size(); i++)
    {
        for (int j = i; j < points.size(); j++)
        {
            Point *point_1 = &points[i];
            Point *point_2 = &points[j];

            double currentDistance = pointDistance(point_1, point_2);
            maxDistance = max(maxDistance, currentDistance);
        }
    }
    return maxDistance;
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

Point findMeanPoint(vector<Point> &points)
{
    double totalX = 0;
    double totalY = 0;

    for (Point point : points)
    {
        totalX += point.getX();
        totalY = point.getY();
    }

    double meanX = totalX / points.size();
    double meanY = totalY / points.size();
    return Point(meanX, meanY);
}