#include <iostream>
#include "City.hpp"
#include <vector>
#include "math.h"
#include <SFML/Graphics.hpp>
#include "SimulatedAnnealing.hpp"

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
    static void Log(Point message)
    {
        std::cout << message << std::endl;
    };
};

std::vector<City *> RandomizedCitySpread(int amount, int windowSize)
{
    int size = windowSize - 20;
    std::vector<City *> cities;
    cities.reserve(amount);
    int x = 0;
    int y = 0;
    String name = "City ";
    for (int i = 0; i < amount; i++)
    {
        x = -((rand() % size) + 10);
        y = -((rand() % size) + 10);
        City *city = new City((name + std::to_string(i + 1)), {x, y});
        cities.emplace_back(city);
    }
    return cities;
}

void CreateRouteShapes(std::vector<City *> cities, std::vector<sf::CircleShape> &shapes, std::vector<sf::Vertex> &roads)
{

    for (int i = 0; i < cities.size(); i++)
    {
        sf::CircleShape shape(2.f);
        shape.setOrigin(sf::Vector2f((cities[i]->point.x) + 2, (cities[i]->point.y) + 2));
        shape.setFillColor(sf::Color::Green);
        shapes.emplace_back(shape);
        roads.push_back(sf::Vertex(sf::Vector2f(-(cities[i]->point.x), -(cities[i]->point.y)), sf::Color::Red));
        roads.push_back(sf::Vertex(sf::Vector2f(-(cities[(i + 1) % cities.size()]->point.x), -(cities[(i + 1) % cities.size()]->point.y)), sf::Color::Red));
    }
}

int main()
{
    int size = 500;
    srand(time(0) ^ getpid());
    City::count = 0;
    std::vector<City *> cities = RandomizedCitySpread(20, size);
    Logger::Log("Before Scrambling");
    // for (City *city : cities)
    // {
    //     Logger::Log(city->point);
    // }
    // Logger::Log("After Scrambling");
    // Neighboorhood(cities);
    // for (City *city : cities)
    // {
    //     Logger::Log(city->point);
    // }

    // Starts rendering window
    sf::RenderWindow window(sf::VideoMode(size, size), "SFML works!");

    // Setup shapes
    std::vector<sf::CircleShape> shapes;
    std::vector<sf::Vertex> roads;
    shapes.reserve(cities.size());
    roads.reserve(cities.size()*2);

    // Inits shapes for rendering
    CreateRouteShapes(cities, shapes, roads);

    sf::Time elapsed_time;
    sf::Clock r;

    // Update/Refresh frequency
    sf::Time delta_time = sf::milliseconds(1500);

    // We have enough time to spawn a sprite. ( may be for several ? )
    while (window.isOpen())
    {
        elapsed_time += r.restart();
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        window.clear();

        window.draw(&roads[0], roads.size(), sf::Lines);
        for (sf::CircleShape shape : shapes)
        {
            window.draw(shape);
        }
        window.display();
        while (elapsed_time >= delta_time)
        {
            // Spawn your sprite
            // ...
            window.clear();
            shapes.clear();
            roads.clear();
            Neighboorhood(cities);
            CreateRouteShapes(cities, shapes, roads);
            Logger::Log(TotalDistance(roads));
            // Substract the time consumed
            elapsed_time -= delta_time;
        }
    }

    return 0;
}
