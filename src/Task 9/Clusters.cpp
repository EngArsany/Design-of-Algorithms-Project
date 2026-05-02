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
    if (k == 1)
        return vector<Cluster>{points};
    if ((int)points.size() <= k)
        return eachPointAsCluster(points);

    int middle = points.size() / 2;
    vector<Point> leftPoints(points.begin(), points.begin() + middle);
    vector<Point> rightPoints(points.begin() + middle, points.end());

    int leftAmount = k / 2;
    int rightAmount = k - leftAmount;
    vector<Cluster> leftClusters = divideAndConquerClusters(leftPoints, leftAmount);
    vector<Cluster> rightClusters = divideAndConquerClusters(rightPoints, rightAmount);

    vector<Cluster> combinedClusters = leftClusters;
    combinedClusters.insert(combinedClusters.end(), rightClusters.begin(), rightClusters.end());
    return combinedClusters;
}

int main()
{
    vector<Point> points = {
        Point(1, 2), Point(3, 4), Point(5, 6),
        Point(7, 8), Point(9, 10), Point(11, 12),
        Point(13, 14), Point(15, 16), Point(17, 18),
        Point(19, 20), Point(21, 22), Point(23, 24)};
    int k = 3;

    vector<int> testCases = {2, 3, 4, 5};
    for (int test : testCases)
    {
        cout << "========== Testing for " << test << " Clusters ==========\n";
        printClusters(bruteForceClusters(points, k), "Brute Force");
        printClusters(iterativeImprovementClusters(points, k), "Iterative Improvement (K-Means)");
        printClusters(divideAndConquerClusters(points, k), "Divide & Conquer");
        cout << "\n";
    }
}