//Map.h
#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include <cstdlib>
#include <ctime>

// Константы карты
const int HEIGHT_MAP = 23; // Высота карты
const int WIDTH_MAP = 40;  // Ширина карты

// Объявление карты
extern sf::String TileMap[HEIGHT_MAP][WIDTH_MAP];
extern void randomMapGenerate();
void generateLevel();
