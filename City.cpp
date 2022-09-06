#include "City.hpp"

City::City(String name, Point point) : name(name), point(point) {
    City::count++;
}

City::~City() {
    City::count--;
}

int City::count;