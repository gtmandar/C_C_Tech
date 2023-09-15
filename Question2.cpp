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

void convexHull(Point points[], int n, std::vector<Point>& hull) {
    if (n < 3) {
        std::cout << "Convex hull not possible with less than 3 points." << std::endl;
        return;
    }

    std::sort(points, points + n, comparePoints);

    std::vector<Point> upperHull(n);
    std::vector<Point> lowerHull(n);
    int upperSize = 0;
    int lowerSize = 0;

    for (int i = 0; i < n; i++) {
        while (upperSize >= 2 && crossProduct(upperHull[upperSize - 2], upperHull[upperSize - 1], points[i]) <= 0)
            upperSize--;
        upperHull[upperSize++] = points[i];
    }

    for (int i = n - 1; i >= 0; i--) {
        while (lowerSize >= 2 && crossProduct(lowerHull[lowerSize - 2], lowerHull[lowerSize - 1], points[i]) <= 0)
            lowerSize--;
        lowerHull[lowerSize++] = points[i];
    }

    for (int i = 1; i < lowerSize - 1; i++) {
        upperHull[upperSize++] = lowerHull[i];
    }

    for (int i = 0; i < upperSize; i++) {
        hull.push_back(upperHull[i]);
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

    Point* points = new Point[n];
    std::cout << "Enter the points (x y):\n";
    for (int i = 0; i < n; i++) {
        std::cin >> points[i].x >> points[i].y;
    }

    std::vector<Point> hull;
    convexHull(points, n, hull);

    double maxArea = areaOfPolygon(hull);

    std::cout << "The largest area of the shape formed by the given points is: " << std::fixed << maxArea << std::endl;

    delete[] points;

    return 0;
}
