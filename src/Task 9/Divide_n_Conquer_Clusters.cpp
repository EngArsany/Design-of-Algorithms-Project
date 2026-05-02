#include "ClustersHelper.hpp"
using namespace std;

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
        Point(1, 2), Point(3, 4), Point(5, 6),
        Point(7, 8), Point(9, 10), Point(11, 12),
        Point(13, 14), Point(15, 16), Point(17, 18), Point{19, 20}};

    vector<int> testCases = {2, 3, 4, 5};
    for (int test : testCases)
    {
        cout << "========== Divide & Conquer Testing for " << test << " Clusters ==========\n";
        printClusters(divideAndConquerClusters(points, test));
        cout << "\n";
    }
}