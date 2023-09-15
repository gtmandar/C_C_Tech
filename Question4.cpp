#include <iostream>

struct Point 
{
    int x, y;
};

Point calculateCentroid(Point points[], int n) 
{
    Point centroid;
    centroid.x = 0;
    centroid.y = 0;

    for (int i = 0; i < n; i++) 
    {
        centroid.x += points[i].x;
        centroid.y += points[i].y;
    }

    centroid.x /= n;
    centroid.y /= n;

    return centroid;
}

int main() 
{
    int n;
    std::cout << "Enter number of points in the shape: ";
    std::cin >> n;

    Point points[n];
    std::cout << "Enter the points (x y):\n";
    for (int i = 0; i < n; i++) 
    {
        std::cin >> points[i].x >> points[i].y;
    }

    Point centroid = calculateCentroid(points, n);

    std::cout << "The centroid of the shape is at point (" << centroid.x << ", " << centroid.y << ").\n";

    return 0;
}
