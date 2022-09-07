#include "SimulatedAnnealing.hpp"
class Logger
{
public:
    static void Log(String message)
    {
        std::cout << message << std::endl;
    };
    static void Log(int message)
    {
        std::cout << message << std::endl;
    };
};

void Neighboorhood(std::vector<City *> &cities)
{
    int index1 = rand() % cities.size();
    int index2 = rand() % cities.size();
    Logger::Log(cities[index1]->name);
    Logger::Log(cities[index2]->name);
    std::swap(cities[index1], cities[index2]);
}

double TotalDistance(std::vector<sf::Vertex> &roads)
{
    double totalLength = 0.0;
    for (int i = 0; i < roads.size(); i++)
    {
        sf::Vector2f p1 = roads[i*2].position;
        sf::Vector2f p2 = roads[i*2+1].position;
        totalLength += sqrtf(powf((p2.y-p2.x), 2)+powf((p1.x-p1.y), 2));
    }
    return totalLength;
}
