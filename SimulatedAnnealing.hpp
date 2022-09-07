#pragma once
#include <vector>
#include "City.hpp"
#include "math.h"
#include "SFML/Graphics.hpp"

void Neighboorhood(std::vector<City*> &cities);
double TotalDistance(std::vector<sf::Vertex> &roads);
