#pragma once
#include <vector>
#include <random>
#include "City.hpp"
#include "math.h"
#include "SFML/Graphics.hpp"

std::vector<City> Neighboorhood(std::vector<City> cities);
double TotalDistance(std::vector<City> &cities);
bool AnnealFunction(double diff, double temp);