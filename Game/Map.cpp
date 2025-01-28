//Map.cpp

#include "Map.h"

sf::String TileMap[HEIGHT_MAP][WIDTH_MAP];

void generateLevel() {
    // Очистка карты (заполняем стенами)
    for (int i = 0; i < HEIGHT_MAP; i++) {
        for (int j = 0; j < WIDTH_MAP; j++) {
            TileMap[i][j] = '0';
        }
    }

    // Генерация комнат
    const int roomCount = 15; // Количество комнат
    const int roomSize = 6;  // Размер комнаты (например, 3x3)
    std::vector<std::pair<int, int>> roomCenters;

    srand(time(0)); // Инициализация генератора случайных чисел
    int key_count = 0;

    for (int i = 0; i < roomCount; i++) {
        bool roomPlaced = false;
        int attempts = 0;
        

        while (!roomPlaced && attempts < 100) {
            int roomX = rand() % (WIDTH_MAP - roomSize - 1) + 1; // Случайные координаты
            int roomY = rand() % (HEIGHT_MAP - roomSize - 1) + 1;

            // Проверяем, свободно ли место для комнаты
            bool isSpaceAvailable = true;
            for (int y = roomY; y < roomY + roomSize && isSpaceAvailable; y++) {
                for (int x = roomX; x < roomX + roomSize; x++) {
                    if (TileMap[y][x] != '0') { // Если место занято
                        isSpaceAvailable = false;
                        break;
                    }
                }
            }


            if (isSpaceAvailable) {
                // Создание комнаты
                for (int y = roomY; y < roomY + roomSize; y++) {
                    for (int x = roomX; x < roomX + roomSize; x++) {
                        TileMap[y][x] = ' ';
                    }
                }

                // Добавление ключа в комнату
                int keyX = roomX + rand() % roomSize; // Случайная позиция внутри комнаты
                int keyY = roomY + rand() % roomSize;

                if (key_count < 5) {
                    char keys[] = { '+', '-', '*','/' };
                    char Key = keys[rand() % 4];
                    TileMap[keyY][keyX] = Key;   // Размещаем предмет
                    key_count++;
                }
                // Добавление случайного сокровища/собираемого предмета в комнату
                int itemX = roomX + rand() % roomSize; // Случайная позиция внутри комнаты по X
                int itemY = roomY + rand() % roomSize; // Случайная позиция внутри комнаты по Y

                char items[] = { 's', 'h','1','2','3','4'};       // Доступные типы предметов
                char randomItem = items[rand() % 6];  // Выбираем случайный предмет

                if (keyY != itemY && keyX != itemX) TileMap[itemY][itemX] = randomItem;   // Размещаем предмет

                //Добавление довушки в комнату
                int trapX = roomX + rand() % roomSize;
                int trapY = roomY + rand() % roomSize;

                char traps[] = { 'f','b','w'};
                char randomTrap = traps[rand() % 3];

                if (itemY!= trapY && itemX != trapX) TileMap[trapY][trapX] = randomTrap;

                // Сохранение центра комнаты
                roomCenters.push_back({ roomX + roomSize / 2, roomY + roomSize / 2 });
                roomPlaced = true;
            }

            attempts++;
        }
    }

    // Соединение комнат коридорами
    for (size_t i = 1; i < roomCenters.size(); i++) {
        int x1 = roomCenters[i - 1].first;
        int y1 = roomCenters[i - 1].second;
        int x2 = roomCenters[i].first;
        int y2 = roomCenters[i].second;

        // Горизонтальный коридор
        for (int x = std::min(x1, x2); x <= std::max(x1, x2); x++) {
            TileMap[y1][x] = ' ';
        }

        // Вертикальный коридор
        for (int y = std::min(y1, y2); y <= std::max(y1, y2); y++) {
            TileMap[y][x2] = ' ';
        }
    }
}