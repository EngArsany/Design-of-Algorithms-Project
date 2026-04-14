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
using Cluster = vector<Point>;

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
        totalY += point.getY();
    }

    double meanX = totalX / points.size();
    double meanY = totalY / points.size();
    return Point(meanX, meanY);
}
vector<vector<Point>> addPointsToNearestCluster(vector<Point> &points, vector<Point> &clusterCenters)
{
    vector<vector<Point>> clusteredPoints;
    for (Point point : points)
    {
        int nearestCluster;
        double minDistance = INT_MAX;
        for (int i = 0; i < clusterCenters.size(); i++)
        {
            double currentDistance = pointDistance(&point, &clusterCenters[i]);

            if (currentDistance >= minDistance)
                continue;

            minDistance = currentDistance;
            nearestCluster = i;
        }
        clusteredPoints[nearestCluster].push_back({point});
    }
    return clusteredPoints;
}
Point computeCentroid(Cluster &cluster)
{
    return findMeanPoint(cluster);
}

double clusterDistance(Cluster &a, Cluster &b)
{
    Point centroidA = computeCentroid(a);
    Point centroidB = computeCentroid(b);
    return pointDistance(&centroidA, &centroidB);
}
vector<Cluster> mergeClusters(vector<Cluster> combinedClusters, int k)
{
    int numOfClusters = combinedClusters.size();
    while (numOfClusters > k)
    {
        int firstCluster = 0, secondCluster = 1;
        double minDistance = clusterDistance(combinedClusters[firstCluster], combinedClusters[secondCluster]);

        for (int i = 0; i < numOfClusters; i++)
        {
            for (int j = i + 1; j < numOfClusters; j++)
            {
                double distance = clusterDistance(combinedClusters[i], combinedClusters[j]);
                if (distance >= minDistance)
                    continue;

                minDistance = distance;
                firstCluster = i;
                secondCluster = j;
            }
        }

        // Merge the second cluster into the first
        for (Point &p : combinedClusters[secondCluster])
            combinedClusters[firstCluster].push_back(p);

        // Remove redundant cluster
        combinedClusters.erase(combinedClusters.begin() + secondCluster);
    }
    return combinedClusters;
}