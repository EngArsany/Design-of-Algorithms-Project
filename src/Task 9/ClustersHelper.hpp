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