#pragma once
#include <bits/stdc++.h>
using namespace std;

class Point
{
private:
    double x, y;
    static constexpr double EPSILON = 1.0;

public:
    Point(double x, double y) : x(x), y(y) {}

    double getX() const { return x; }
    double getY() const { return y; }

    double distanceTo(const Point &other) const
    {
        double dx = x - other.x;
        double dy = y - other.y;
        return sqrt(dx * dx + dy * dy);
    }

    bool operator==(const Point &other) const
    {
        return abs(x - other.x) < EPSILON && abs(y - other.y) < EPSILON;
    }

    bool operator!=(const Point &other) const
    {
        return abs(x - other.x) >= EPSILON || abs(y - other.y) >= EPSILON;
    }

    void print() const
    {
        cout << "(" << x << ", " << y << "), ";
    }
};

using Cluster = vector<Point>;

// --- Point utilities ---

Point computeMeanPoint(const vector<Point> &points)
{
    double totalX = 0, totalY = 0;
    for (const Point &p : points)
    {
        totalX += p.getX();
        totalY += p.getY();
    }
    return Point(totalX / points.size(), totalY / points.size());
}

double calculateMaxDistance(const vector<Point> &points)
{
    double maxDistance = 0;
    for (int i = 0; i < (int)points.size(); i++)
        for (int j = i + 1; j < (int)points.size(); j++)
            maxDistance = max(maxDistance, points[i].distanceTo(points[j]));
    return maxDistance;
}

bool containsPoint(const vector<Point> &points, const Point &target)
{
    for (const Point &p : points)
        if (p == target)
            return true;
    return false;
}

// --- Cluster utilities ---

vector<Cluster> eachPointAsCluster(const vector<Point> &points)
{
    vector<Cluster> clusters;
    for (const Point &p : points)
        clusters.push_back({p});
    return clusters;
}

bool isBaseCase(const vector<Point> &points, int k)
{
    return k == 1 || k >= (int)points.size();
}

Point computeCentroid(const Cluster &cluster)
{
    return computeMeanPoint(cluster);
}

double clusterDistance(const Cluster &a, const Cluster &b)
{
    Point centroidA = computeCentroid(a);
    Point centroidB = computeCentroid(b);
    return centroidA.distanceTo(centroidB);
}

void printClusters(const vector<Cluster> &clusters)
{
    for (int i = 0; i < (int)clusters.size(); i++)
    {
        cout << "  Cluster " << i + 1 << ": ";
        for (const Point &p : clusters[i])
            p.print();
        cout << "\n";
    }
    cout << "\n";
}

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