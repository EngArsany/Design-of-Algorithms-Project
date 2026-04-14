#include "ClustersHelper.hpp"
using namespace std;

vector<vector<Point>> bruteForceClusters(vector<Point> &points, int clusters)
{
    if (clusters == points.size() || clusters == 1) // Edge Cases
        return {points};

    double maxDistance = calculateMaxDistance(points) / clusters;
    vector<bool> pointTaken(points.size());
    vector<vector<Point>> clusteredPoints(clusters);

    for (int i = 0; i < points.size(); i++)
    {
        if (clusters <= 0)
            break;
        if (pointTaken[i])
            continue;

        Point startPoint = points[i];
        clusteredPoints[--clusters].push_back({startPoint}); // add point to a cluster
        bool isLastCluster = (clusters == 0);

        for (int j = i + 1; j < points.size(); j++)
        {
            if (pointTaken[i] || pointTaken[j])
                continue;

            Point endPoint = points[j];
            double currentDistance = pointDistance(&startPoint, &endPoint);

            if (currentDistance < maxDistance || isLastCluster)
            {
                clusteredPoints[clusters].push_back({endPoint});
                pointTaken[j] = true;
            }
        }
    }
    return clusteredPoints;
}

vector<vector<Point>> iterativeImprovementClusters(vector<Point> &points, int clusters)
{
    // Use K-means clustering
    // The smallest move is to move a point to another cluster

    // Edge Cases
    int numOfPoints = points.size();
    if (clusters == numOfPoints || clusters == 1)
        return {points};

    // Generate random clusters
    vector<Point> clusterCenters;
    for (int i = 0; i < clusters; i++)
        clusterCenters.push_back(Point(rand() % 25, rand() % 25));

    // Iterative Improvement Step
    vector<Point> newClusterCenters = clusterCenters;
    do
    {
        vector<vector<Point>> clusteredPoints(clusters);
        clusteredPoints = addPointsToNearestCluster(points, clusterCenters);

        // Find k-means
        bool noChange = true;
        for (int i = 0; i < clusters; i++)
        {
            newClusterCenters[i] = findMeanPoint(clusteredPoints[i]);
            if (newClusterCenters[i] != clusterCenters[i])
                noChange = false;
        }

        // Break if no better improvement
        if (noChange)
            return clusteredPoints;

        clusterCenters = newClusterCenters;
    } while (true);

    return {{}};
}

void divideAndConquerClusters(vector<Point> *points, int length, int clusters)
{
    if (length <= 1)
        return;

    int middle = length / 2;
    vector<Point> leftPart(middle);
    vector<Point> rightPart(length - middle);

    int j = 0;
    for (int i = 0; i < length; i++)
    {
        if (i < middle)
            leftPart[i] = (*points)[i]; // Dereference pointer
        else
        {
            rightPart[j] = (*points)[i];
            j++;
        }
    }

    divideAndConquerClusters(&leftPart, middle, clusters);
    divideAndConquerClusters(&rightPart, length - middle, clusters);
    combineClusters(points, length, &leftPart, &rightPart, clusters);
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

    vector<vector<Point>> clusteredPoints = iterativeImprovementClusters(points, 3);

    for (int i = 0; i < clusteredPoints.size(); i++)
    {
        cout << "Cluster number " << i + 1 << ":\n";
        for (auto point : clusteredPoints[i])
            point.print();
        cout << "\n";
    }
}