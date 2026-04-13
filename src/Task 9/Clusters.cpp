#include "ClustersHelper.hpp"
// #include <bits/stdc++.h>
using namespace std;

vector<vector<Point>> bruteForceClusters(vector<Point> &points, int clusters)
{
    if (clusters == points.size() || clusters == 1) // Edge Cases
        return {points};

    double maxDistance = 33;
    maxDistance = maxDistance / clusters;
    vector<bool> pointTaken(points.size());

    vector<vector<Point>> clusteredPoints(clusters);

    for (int i = 0; i < points.size(); i++)
    {
        if (clusters <= 0)
            break;
        if (pointTaken[i])
            continue;

        clusteredPoints[--clusters].push_back({points[i]}); // add point to a cluster

        Point startPoint = points[i];
        for (int j = i + 1; j < points.size(); j++)
        {
            if (pointTaken[i] || pointTaken[j])
                continue;

            Point endPoint = points[j];
            double currentDistance = pointDistance(&startPoint, &endPoint);

            if (currentDistance < maxDistance || clusters == 0)
            {
                clusteredPoints[clusters].push_back({endPoint});
                pointTaken[j] = true;
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
        cout << "\n";
    }
}