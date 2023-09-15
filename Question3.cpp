#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

struct Point {
    int x, y;
};

bool comparePoints(const Point& a, const Point& b) {
    return (a.x < b.x) || (a.x == b.x && a.y < b.y);
}

int crossProduct(const Point& A, const Point& B, const Point& C) {
    return (B.x - A.x) * (C.y - A.y) - (B.y - A.y) * (C.x - A.x);
}

void convexHull(const std::vector<Point>& points, std::vector<bool>& isInsideConvexHull) {
    int n = points.size();
    if (n < 3) {
        return;
    }

    std::vector<Point> sortedPoints = points;
    std::sort(sortedPoints.begin(), sortedPoints.end(), comparePoints);

    std::vector<Point> upperHull;
    std::vector<Point> lowerHull;
    int upperSize = 0;
    int lowerSize = 0;

    for (int i = 0; i < n; i++) {
        while (upperSize >= 2 && crossProduct(upperHull[upperSize - 2], upperHull[upperSize - 1], sortedPoints[i]) <= 0) {
            upperSize--;
            upperHull.pop_back();
        }
        upperHull.push_back(sortedPoints[i]);
        upperSize++;
    }

    for (int i = n - 1; i >= 0; i--) {
        while (lowerSize >= 2 && crossProduct(lowerHull[lowerSize - 2], lowerHull[lowerSize - 1], sortedPoints[i]) <= 0) {
            lowerSize--;
            lowerHull.pop_back();
        }
        lowerHull.push_back(sortedPoints[i]);
        lowerSize++;
    }

    for (int i = 1; i < lowerSize - 1; i++) {
        upperHull.push_back(lowerHull[i]);
    }

    for (int i = 0; i < n; i++) {
        isInsideConvexHull[i] = false;
    }

    for (const Point& p : upperHull) {
        isInsideConvexHull[p.x] = true;
    }
}

double areaOfPolygon(const std::vector<Point>& polygon) {
    double area = 0.0;
    int n = polygon.size();
    for (int i = 0; i < n - 1; i++) {
        area += (double)(polygon[i].x * polygon[i + 1].y - polygon[i + 1].x * polygon[i].y);
    }
    area += (double)(polygon[n - 1].x * polygon[0].y - polygon[0].x * polygon[n - 1].y);
    area = std::fabs(area) / 2.0;
    return area;
}

int main() {
    int n;
    std::cout << "Enter the number of points: ";
    std::cin >> n;

    std::vector<Point> points(n);
    std::vector<bool> isInsideConvexHull(n, false);

    std::cout << "Enter the points (x y):\n";
    for (int i = 0; i < n; i++) {
        std::cin >> points[i].x >> points[i].y;
    }

    double maxArea = 0.0;
    int pointToRemove = -1;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            isInsideConvexHull[j] = false;
        }
        isInsideConvexHull[i] = true; // Temporarily remove the point

        std::vector<Point> remainingPoints;
        for (int j = 0; j < n; j++) {
            if (isInsideConvexHull[j]) {
                remainingPoints.push_back(points[j]);
            }
        }

        convexHull(remainingPoints, isInsideConvexHull);
        double currentArea = areaOfPolygon(remainingPoints);

        if (currentArea > maxArea) {
            maxArea = currentArea;
            pointToRemove = i;
        }

        isInsideConvexHull[i] = false; // Restore the removed point
    }

    std::cout << "To maximize the area, remove point (" << points[pointToRemove].x << ", " << points[pointToRemove].y << ").\n";

    return 0;
}
