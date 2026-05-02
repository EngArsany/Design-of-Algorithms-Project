#include "ClustersHelper.hpp"
using namespace std;

vector<Cluster> assignPointsToNearestCluster(const vector<Point> &points, const vector<Point> &centroids)
{
    vector<Cluster> clusters(centroids.size());
    for (const Point &point : points)
    {
        int nearestIndex = 0;
        double minDistance = point.distanceTo(centroids[0]);
        for (int i = 1; i < (int)centroids.size(); i++)
        {
            double distance = point.distanceTo(centroids[i]);
            if (distance < minDistance)
            {
                minDistance = distance;
                nearestIndex = i;
            }
        }
        clusters[nearestIndex].push_back(point);
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

int main()
{
    vector<Point> points = {
        Point(1, 2), Point(3, 4), Point(5, 6),
        Point(7, 8), Point(9, 10), Point(11, 12),
        Point(13, 14), Point(15, 16), Point(17, 18), Point{19, 20}};

    vector<int> testCases = {2, 3, 4, 5};
    for (int test : testCases)
    {
        cout << "========== Iterative Improvement Testing for " << test << " Clusters ==========\n";
        printClusters(iterativeImprovementClusters(points, test));
        cout << "\n";
    }
}