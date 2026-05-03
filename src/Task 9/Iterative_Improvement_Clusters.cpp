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

    // Choose centroids from random points inside the points vector
    vector<Point> centroids;
    vector<int> pointsIndices(points.size());
    iota(pointsIndices.begin(), pointsIndices.end(), 0);
    random_shuffle(pointsIndices.begin(), pointsIndices.end());
    for (int i = 0; i < k; i++){
        int randomPoint = pointsIndices[i];
        centroids.push_back(points[randomPoint]);
    }

    while (true)
    {
        vector<Cluster> clusters = assignPointsToNearestCluster(points, centroids);

        vector<Point> newCentroids;
        bool converged = true;
        for (int i = 0; i < k; i++)
        {
            Point newCentroid = computeCentroid(clusters[i]);
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
        Point(2, 3), Point(3, 2), Point(4, 5), Point(5, 4), Point(6, 3),
        Point(1, 6), Point(7, 2), Point(3, 7), Point(4, 4), Point(5, 5),
        Point(11, 12), Point(12, 11), Point(13, 14), Point(14, 13), Point(15, 12),
        Point(10, 15), Point(16, 11), Point(12, 16), Point(13, 13), Point(14, 14),
        Point(20, 21), Point(21, 20), Point(22, 23), Point(23, 22), Point(24, 21),
        Point(20, 24), Point(25, 22), Point(22, 25), Point(23, 23), Point(24, 24)
    };

    vector<int> testCases = {2, 3, 4, 5};
    for (int test : testCases)
    {
        cout << "========== Iterative Improvement Testing for " << test << " Clusters ==========\n";
        printClusters(iterativeImprovementClusters(points, test));
        cout << "\n";
    }
}