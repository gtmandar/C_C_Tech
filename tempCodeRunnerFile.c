#include <stdio.h>
#include <stdlib.h>

struct Point 
{
    int x, y;
};

struct Point calculateCentroid(struct Point points[], int n) 
{
    struct Point centroid;
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
    printf("Enter number of points in the shape: ");
    scanf("%d", &n);

    struct Point points[n];
    printf("Enter the points (x y):\n");
    for (int i = 0; i < n; i++) 
    {
        scanf("%d %d", &points[i].x, &points[i].y);
    }

    struct Point centroid = calculateCentroid(points, n);

    printf("The centroid of shape is at point (%d, %d).\n", centroid.x, centroid.y);

    return 0;
}
