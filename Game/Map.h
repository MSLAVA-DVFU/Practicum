//Map.h
#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include <cstdlib>
#include <ctime>

// Константы карты
const int HEIGHT_MAP = 33; // Высота карты
const int WIDTH_MAP = 60;  // Ширина карты

extern sf::String TileMap[HEIGHT_MAP][WIDTH_MAP];
std::vector<std::pair<int, int>> generateLevel();
