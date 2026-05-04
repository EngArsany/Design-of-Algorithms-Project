#include "ClustersHelper.hpp"
using namespace std;

vector<Cluster> mergeClusters(vector<Cluster> clusters, int targetCount)
{
    while ((int)clusters.size() > targetCount)
    {
        int firstIndex = 0, secondIndex = 1;
        double minDistance = clusterDistance(clusters[0], clusters[1]);

        for (int i = 0; i < (int)clusters.size(); i++)
        {
            for (int j = i + 1; j < (int)clusters.size(); j++)
            {
                double distance = clusterDistance(clusters[i], clusters[j]);
                if (distance < minDistance)
                {
                    minDistance = distance;
                    firstIndex = i;
                    secondIndex = j;
                }
            }
        }

        for (const Point &p : clusters[secondIndex])
            clusters[firstIndex].push_back(p);
        clusters.erase(clusters.begin() + secondIndex);
    }
    return clusters;
}

vector<Cluster> divideAndConquerClusters(const vector<Point> &points, int k)
{
    if ((int)points.size() <= k)
        return eachPointAsCluster(points);

    int middle = points.size() / 2;
    vector<Point> leftPoints(points.begin(), points.begin() + middle);
    vector<Point> rightPoints(points.begin() + middle, points.end());

    vector<Cluster> leftClusters = divideAndConquerClusters(leftPoints, k);
    vector<Cluster> rightClusters = divideAndConquerClusters(rightPoints, k);

    vector<Cluster> combined = leftClusters;
    combined.insert(combined.end(), rightClusters.begin(), rightClusters.end());

    return mergeClusters(combined, k);
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
        cout << "========== Divide & Conquer Testing for " << test << " Clusters ==========\n";
        printClusters(divideAndConquerClusters(points, test));
        cout << "\n";
    }
}