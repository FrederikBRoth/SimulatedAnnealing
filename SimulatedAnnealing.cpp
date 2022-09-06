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

void Neighboorhood(std::vector<City*> &cities) {
    int index1 = rand() % cities.size();
    int index2 = rand() % cities.size();
    Logger::Log(cities[index1]->name);
    Logger::Log(cities[index2]->name);
    std::swap(cities[index1], cities[index2]);
}

