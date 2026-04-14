#include "ClustersHelper.hpp"
using namespace std;

vector<Cluster> bruteForceClusters(const vector<Point> &points, int k)
{
    if (isBaseCase(points, k))
        return k == 1 ? vector<Cluster>{points} : eachPointAsCluster(points);

    double maxDistance = calculateMaxDistance(points) / k;
    vector<bool> pointTaken(points.size(), false);
    vector<Cluster> clusters(k);
    int clusterIndex = k - 1;

    for (int i = 0; i < (int)points.size(); i++)
    {
        if (clusterIndex < 0)
            break;
        if (pointTaken[i])
            continue;

        const Point &startPoint = points[i];
        clusters[clusterIndex].push_back(startPoint);
        bool isLastCluster = (clusterIndex == 0);

        for (int j = i + 1; j < (int)points.size(); j++)
        {
            if (pointTaken[i] || pointTaken[j])
                continue;
            double distance = startPoint.distanceTo(points[j]);
            if (distance < maxDistance || isLastCluster)
            {
                clusters[clusterIndex].push_back(points[j]);
                pointTaken[j] = true;
            }
        }
        clusterIndex--;
    }
    return clusters;
}

vector<Cluster> iterativeImprovementClusters(const vector<Point> &points, int k)
{
    if (isBaseCase(points, k))
        return k == 1 ? vector<Cluster>{points} : eachPointAsCluster(points);

    vector<Point> centroids;
    for (int i = 0; i < k; i++)
        centroids.push_back(Point(rand() % 25, rand() % 25));

    while (true)
    {
        vector<Cluster> clusters = assignPointsToNearestCluster(points, centroids);

        vector<Point> newCentroids;
        bool converged = true;
        for (int i = 0; i < k; i++)
        {
            Point newCentroid = computeMeanPoint(clusters[i]);
            if (newCentroid != centroids[i])
                converged = false;
            newCentroids.push_back(newCentroid);
        }

        if (converged)
            return clusters;
        centroids = newCentroids;
    }
}

vector<Cluster> divideAndConquerClusters(const vector<Point> &points, int k)
{
    if ((int)points.size() <= k)
        return eachPointAsCluster(points);

    int middle = points.size() / 2;
    vector<Point> left(points.begin(), points.begin() + middle);
    vector<Point> right(points.begin() + middle, points.end());

    vector<Cluster> leftClusters = divideAndConquerClusters(left, k);
    vector<Cluster> rightClusters = divideAndConquerClusters(right, k);

    vector<Cluster> combined = leftClusters;
    combined.insert(combined.end(), rightClusters.begin(), rightClusters.end());

    return mergeClusters(combined, k);
}

int main()
{
    vector<Point> points = {
        Point(1, 2), Point(3, 4), Point(5, 6),
        Point(7, 8), Point(9, 10), Point(11, 12),
        Point(13, 14), Point(15, 16), Point(17, 18),
        Point(19, 20), Point(21, 22), Point(23, 24)};

    vector<Cluster> clusters = divideAndConquerClusters(points, 3);

    for (int i = 0; i < (int)clusters.size(); i++)
    {
        cout << "Cluster " << i + 1 << ":\n";
        for (const Point &p : clusters[i])
            p.print();
        cout << "\n";
    }
}