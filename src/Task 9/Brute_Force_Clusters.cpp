#include "ClustersHelper.hpp"
using namespace std;

// Using Stirling numbers of the second kind
void generateAllCombinations(
    const vector<Point> &points,
    int index,
    vector<int> &combination,
    int k,
    int usedClusters,
    vector<vector<int>> &allAssignments)
{
    int n = points.size();

    // Prune when not enough remaining points
    int remaining = n - index;
    int neededClusters = k - usedClusters;
    if (remaining < neededClusters)
        return;

    // Return when all points assigned
    if (index == n)
    {
        if (usedClusters == k) // Only assignments that have filled clusters
            allAssignments.push_back(combination);

        return;
    }

    // Always assign to cluster 0 to avoid symmetric duplicates
    if (index == 0)
    {
        combination[index] = 0;
        generateAllCombinations(points, index + 1, combination, k, 1, allAssignments);
        return;
    }

    // Assign to existing clusters
    for (int cluster = 0; cluster < usedClusters; cluster++)
    {
        combination[index] = cluster;
        generateAllCombinations(points, index + 1, combination, k, usedClusters, allAssignments);
    }

    // Assign to new cluster if there are any
    if (usedClusters < k)
    {
        combination[index] = usedClusters;
        generateAllCombinations(points, index + 1, combination, k, usedClusters + 1, allAssignments);
    }
}

// Score is evaluated as sum of distances to centroid
double calculatePartitionScore(const vector<Point> &points, const vector<int> &combination, int k)
{
    vector<Cluster> clusters(k);
    for (int i = 0; i < (int)points.size(); i++)
        clusters[combination[i]].push_back(points[i]);

    double totalScore = 0;
    for (const Cluster &cluster : clusters)
    {
        Point centroid = computeCentroid(cluster);
        for (const Point &point : cluster)
            totalScore += point.distanceTo(centroid);
    }
    return totalScore;
}
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

int main()
{
    vector<Point> points = {
        Point(1, 2), Point(3, 4), Point(5, 6),
        Point(7, 8), Point(9, 10), Point(11, 12),
        Point(13, 14), Point(15, 16), Point(17, 18), Point{19, 20}};

    vector<int> testCases = {2, 3, 4, 5};
    for (int test : testCases)
    {
        cout << "========== Brute Force Testing for " << test << " Clusters ==========\n";
        printClusters(bruteForceClusters(points, test));
        cout << "\n";
    }
}