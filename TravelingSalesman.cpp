#include <iostream>
#include "City.hpp"
#include <vector>
#include "math.h"
#include <SFML/Graphics.hpp>
#include "SimulatedAnnealing.hpp"

/*
TODO:
Add "Temp steps" in which it goes through different iterations of neighboors untill it finds a better one then decrease temp
Add better Neighboor functions.


*/

std::ostream &operator<<(std::ostream &stream, Point &point)
{
    stream << point.x << ", " << point.y;
    return stream;
};

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
    static void Log(double message)
    {
        std::cout << message << std::endl;
    };
    static void Log(Point message)
    {
        std::cout << message << std::endl;
    };
    static void Log(bool message)
    {
        std::cout << (message ? "true" : "false") << std::endl;
    };
};

std::vector<City> RandomizedCitySpread(int amount, int windowSize)
{
    int size = windowSize - 20;
    std::vector<City> cities;
    cities.reserve(amount);
    int x = 0;
    int y = 0;
    String name = "City ";
    for (int i = 0; i < amount; i++)
    {
        x = -((rand() % size) + 10);
        y = -((rand() % size) + 10);
        City city = City((std::to_string(i + 1)), {x, y});
        cities.emplace_back(city);
    }
    return cities;
}

void CreateRouteShapes(std::vector<City> cities, std::vector<sf::CircleShape> &shapes, std::vector<sf::Vertex> &roads)
{

    for (int i = 0; i < cities.size(); i++)
    {
        sf::CircleShape shape(2.f);
        shape.setPosition(sf::Vector2f(-(cities[i].point.x), -(cities[i].point.y)));
        shape.setFillColor(sf::Color::Green);
        shapes.emplace_back(shape);
        roads.push_back(sf::Vertex(sf::Vector2f(-(cities[i].point.x), -(cities[i].point.y)), sf::Color::Red));
        roads.push_back(sf::Vertex(sf::Vector2f(-(cities[(i + 1) % cities.size()].point.x), -(cities[(i + 1) % cities.size()].point.y)), sf::Color::Red));
    }
}

int main()
{
    sf::Font font;
    if (!font.loadFromFile("arial.ttf"))
    {
        Logger::Log("Fuck");
    }
    int size = 750;
    srand(time(0) ^ getpid());
    City::count = 0;
    int cityCize = 100;
    std::vector<City> cities = RandomizedCitySpread(cityCize, size);
    Logger::Log("Before Scrambling");

    // Starts rendering window
    sf::RenderWindow window(sf::VideoMode(size, size), "SFML works!");

    // Setup shapes
    std::vector<sf::CircleShape> shapes;
    std::vector<sf::Vertex> roads;
    shapes.reserve(cities.size());
    roads.reserve(cities.size() * 2);

    // Inits shapes for rendering
    CreateRouteShapes(cities, shapes, roads);

    sf::Time elapsed_time;
    sf::Clock r;

    // Update/Refresh frequency
    sf::Time delta_time = sf::milliseconds(50);
    double temp = 1000;
    double cooling = 0.90;
    // We have enough time to spawn½ a sprite. ( may be for several ? )
    int stepCountMax = cityCize * 100;
    int stepCount = 0;
    int improvementCount = 0;
    bool running = true;
    while (window.isOpen())
    {
        elapsed_time += r.restart();
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        // while (elapsed_time >= delta_time)
        // {
        // Spawn your sprite
        // ...
        if (running)
        {
            shapes.clear();
            roads.clear();
            std::vector<City> altCities = Neighboorhood(cities);
            double diff = TotalDistance(altCities) - TotalDistance(cities);
            if (diff < 0.0 || AnnealFunction(diff, temp))
            {

                cities = altCities;
                CreateRouteShapes(cities, shapes, roads);
                window.clear();

                window.draw(&roads[0], roads.size(), sf::Lines);
                int index = 0;
                for (sf::CircleShape shape : shapes)
                {
                    window.draw(shape);
                    index++;
                }
                if (diff < 0.0)
                {
                    improvementCount++;
                }
                if (improvementCount > 9)
                {
                    temp *= cooling;
                    improvementCount = 0;
                    stepCount = -1;
                }

                window.display();
            }
            stepCount++;
            if(stepCount > stepCountMax) {
                Logger::Log("Found Solution");
                running = false;
            }

            // Substract the time consumed
            elapsed_time -= delta_time;
            // }
        }
    }

    return 0;
}
