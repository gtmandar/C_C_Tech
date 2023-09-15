#include <iostream>
#include <fstream>
#include <string>
#include <vector>

struct Point 
{
    int id;
    double x, y;
};

void readDataFromFile(const std::string& filename) 
{
    std::ifstream file(filename);
    if (!file.is_open()) 
    {
        std::cerr << "Error: Unable to open file " << filename << std::endl;
        exit(1);
    }

    std::string line;
    std::string section;
    Point point;
    std::vector<Point> points;
    bool inPTS = false;

    while (std::getline(file, line)) 
    {
        if (line.find("PTS") != std::string::npos) 
        {
            std::cout << "Point Data:" << std::endl;
            inPTS = true;
        } 
        else if (line.find("CON") != std::string::npos) 
        {
            std::cout << "Connection Data:" << std::endl;
            inPTS = false;
        } 
        else if (inPTS) 
        {
            if (sscanf(line.c_str(), "%d %lf %lf", &point.id, &point.x, &point.y) == 3) 
            {
                std::cout << "Point ID: " << point.id << ", X: " << point.x << ", Y: " << point.y << std::endl;
                points.push_back(point);
            }
        } 
        else 
        {
            int id1, id2;
            if (sscanf(line.c_str(), "%d %d", &id1, &id2) == 2) 
            {
                std::cout << "Connection between Point ID " << id1 << " and Point ID " << id2 << std::endl;
            }
        }
    }

    file.close();
}

int main() 
{
    const std::string filename = "Question1data.txt"; 
    readDataFromFile(filename);
    return 0;
}
