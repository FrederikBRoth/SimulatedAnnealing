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

std::vector<City> Neighboorhood(std::vector<City> cities)
{
    std::vector<City> temp = cities;
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> dis(0, cities.size()); // uniform distribution between 0 and

    int index1 = dis(gen);
    int index2 = dis(gen);
    int biggest = index1 > index2 ? index1 : index2;
    int smallest = index1 < index2 ? index1 : index2;
    Logger::Log(biggest);
    Logger::Log(smallest);
    if(index1 == index2) {
        return cities;
    }
    std::vector<City> temptemp;
    temptemp.reserve(cities.size());
    for (int i = 0; i <= smallest; i++)
    {
        temptemp.push_back(cities[i]);
    }
    for (int i = biggest; i > smallest; i--)
    {
        temptemp.push_back(cities[i]);
    }
    for (int i = biggest + 1; i < cities.size(); i++)
    {
        temptemp.push_back(cities[i]);
    }

    return temptemp;
}

double TotalDistance(std::vector<City> &cities)
{
    double totalLength = 0.0;
    for (int i = 0; i < cities.size(); i++)
    {
        sf::Vector2f p1 = sf::Vector2f(-(cities[i].point.x), -(cities[i].point.y));
        sf::Vector2f p2 = sf::Vector2f(-(cities[(i + 1) % cities.size()].point.x), -(cities[(i + 1) % cities.size()].point.y));
        totalLength += sqrtf(powf((p1.x - p2.x), 2) + powf((p1.y - p2.y), 2));
    }
    return totalLength;
}

bool AnnealFunction(double diff, double temp)
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> dis(0, 1); // uniform distribution between 0 and 1

    double chance = dis(gen);

    return chance < exp(-diff / temp);
}
