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

    int index1a = dis(gen);
    int index2a = dis(gen);
    int index1b = 0;
    int index2b = 0;
    if (dis(gen) < temp.size() / 2)
    {
        index1b = (index1a + 1) % temp.size();
        index2b = (index2a + 1) % temp.size();
    }
    else
    {
        index1b = (index1a - 1) % temp.size();
        index2b = (index2a - 1) % temp.size();
    }

    std::swap(temp[index2b], temp[index1b]);

    return temp;
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

    return chance < exp(-(1 / temp * diff));
}
