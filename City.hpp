#pragma once
#include <string>
#include "Point.hpp"

using String = std::string;

class City {
public:
    static int count;
    String name;
    Point point;
    City(String name, Point point);
    ~City();
};

