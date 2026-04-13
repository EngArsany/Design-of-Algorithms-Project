#include "ClustersHelper.hpp"
using namespace std;

vector<vector<Point>> bruteForceClusters(vector<Point> &points, int clusters)
{
    if (clusters == points.size() || clusters == 1) // Edge Cases
        return {points};

    double maxDistance = calculateMaxDistance(points);
    maxDistance /= clusters;
    vector<bool> pointTaken;

    vector<vector<Point>> clusteredPoints;
    clusteredPoints[0].push_back(points[0]); // add first point to a cluster

    while (clusters--)
    {
        for (int i = 0; i < points.size(); i++)
        {
            for (int j = i + 1; j < points.size(); j++)
            {
                Point startPoint = points[i];
                Point endPoint = points[j];

                if (pointTaken[i])
                    continue;

                double currentDistance = distance(&startPoint, &endPoint);

                if (currentDistance <= maxDistance)
                {
                    clusteredPoints[clusters].push_back(endPoint);
                    pointTaken[j] = true;
                }
            }
        }
    }
    return clusteredPoints;
}

void iterativeImprovementClusters(vector<Point> &points, int clusters)
{
}

void divideAndConquerClusters(vector<Point> &points, int clusters)
{
}

int main()
{
    // Assume points are given in an array
    vector<Point> points = {
        Point(1, 2),
        Point(3, 4),
        Point(5, 6),
        Point(7, 8),
        Point(9, 10),
        Point(11, 12),
        Point(13, 14),
        Point(15, 16),
        Point(17, 18),
        Point(19, 20),
        Point(21, 22),
        Point(23, 24)};

    vector<vector<Point>> clusteredPoints = bruteForceClusters(points, 3);

    for (int i = 0; i < clusteredPoints.size(); i++)
    {
        cout << "Cluster number " << i + 1 << ":\n";
        for (auto point : clusteredPoints[i])
            point.print();
    }
}