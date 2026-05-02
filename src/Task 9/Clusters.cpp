#include "ClustersHelper.hpp"
using namespace std;

vector<Cluster> bruteForceClusters(const vector<Point> &points, int k)
{
    if (isBaseCase(points, k))
        return k == 1 ? vector<Cluster>{points} : eachPointAsCluster(points);

    vector<vector<int>> allPartitions;
    vector<int> assignment(points.size(), 0);
    generateAllCombinations(points, 0, assignment, k, 0, allPartitions);

    double bestScore = INT_MAX; // minimum distance to centroid
    vector<int> bestAssignment;
    for (const vector<int> &partition : allPartitions)
    {
        double score = calculatePartitionScore(points, partition, k);
        if (score >= bestScore)
            continue;

        bestScore = score;
        bestAssignment = partition;
    }

    vector<Cluster> clusters(k);
    for (int i = 0; i < points.size(); i++)
    {
        auto cluster = bestAssignment[i];
        clusters[cluster].push_back(points[i]);
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
    vector<Point> leftPoints(points.begin(), points.begin() + middle);
    vector<Point> rightPoints(points.begin() + middle, points.end());

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
        Point(13, 14), Point(15, 16), Point(17, 18), Point{19, 20}};

    vector<int> testCases = {2, 3, 4, 5};
    for (int test : testCases)
    {
        cout << "========== Testing for " << test << " Clusters ==========\n";
        printClusters(bruteForceClusters(points, test), "Brute Force");
        printClusters(iterativeImprovementClusters(points, test), "Iterative Improvement (K-Means)");
        printClusters(divideAndConquerClusters(points, test), "Divide & Conquer");
        cout << "\n";
    }
}