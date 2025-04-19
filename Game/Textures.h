// Textures.h

#pragma once

#include <SFML/Graphics.hpp>
using namespace sf;

namespace textures {
    Texture player_texture;
    Texture map_texture;
    Texture spider_texture;
    Texture zombi_texture;

    static void setTextures() {
        Image heroimage;
        heroimage.loadFromFile("C:/Users/Kille/OneDrive/Рабочий стол/Дисциплины 2 курс/C++/Infinity Gate/Assets/RPGChars32x32Preview.png");
        heroimage.createMaskFromColor(Color(255, 0, 255));
        player_texture.loadFromImage(heroimage);

        Image mapimage;
        mapimage.loadFromFile("C:/Users/Kille/OneDrive/Рабочий стол/Дисциплины 2 курс/C++/Infinity Gate/Assets/map.png");
        mapimage.createMaskFromColor(Color(0, 0, 0));
        map_texture.loadFromImage(mapimage);
        
        Image spider_image;
        spider_image.loadFromFile("C:/Users/Kille/OneDrive/Рабочий стол/Дисциплины 2 курс/C++/Infinity Gate/Assets/map.png");
        spider_image.createMaskFromColor(Color(0, 0, 0));
        spider_texture.loadFromImage(spider_image);

        Image zombi_image;
        zombi_image.loadFromFile("C:/Users/Kille/OneDrive/Рабочий стол/Дисциплины 2 курс/C++/Infinity Gate/Assets/zombi.png");
        zombi_image.createMaskFromColor(Color(0, 0, 0));
        zombi_texture.loadFromImage(zombi_image);
    }
}