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

int main()
{
    int size = 500;
    srand(time(0) ^ getpid());
    City::count = 0;
    std::vector<City *> cities = RandomizedCitySpread(20, size);
    Logger::Log("Before Scrambling");
    for (City *city : cities)
    {
        Logger::Log(city->point);
    }
    Logger::Log("After Scrambling");
    Neighboorhood(cities);
    for (City *city : cities)
    {
        Logger::Log(city->point);
    }

    // Starts rendering window
    sf::RenderWindow window(sf::VideoMode(size, size), "SFML works!");

    // Setup shapes
    std::vector<sf::CircleShape> shapes;
    shapes.reserve(cities.size());

    // Inits shapes for rendering
    for (City *v : cities)
    {
        sf::CircleShape shape(2.f);
        shape.setOrigin(sf::Vector2f(v->point.x, v->point.y));
        shape.setFillColor(sf::Color::Green);
        shapes.emplace_back(shape);
    }
    // Rendering of graphics
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();
        for (sf::CircleShape shape : shapes)
        {
            window.draw(shape);
        }
        window.display();
    }

    return 0;
}
