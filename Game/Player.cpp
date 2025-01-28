// Player.cpp

#include "Player.h"
#include "PlayerController.h"
#include "Map.h"

Player::Player(sf::Texture& texture, sf::Vector2f start_pos, float health,int PlayerScore,bool life,int choice) {
    m_pos = start_pos;
    m_health = health;
    m_score = PlayerScore;
    m_life = life;
    m_keys = 0;
    m_class = choice;

    m_controller = PlayerController::getPlayerController();

    // Установка текстуры в зависимости от класса
    m_sprite.setTexture(texture);
    m_sprite.setTextureRect(sf::IntRect(66, 96, 32, 32));

    m_sprite.setScale(0.8f, 0.8f);
    m_size = sf::Vector2f(m_sprite.getTextureRect().width-10, m_sprite.getTextureRect().height-10);
}

Player::~Player() {}

void Player::setClass(int newClass) {
    m_class = newClass;

    switch (m_class) {
    case 1: // Knight
        m_sprite.setTextureRect(sf::IntRect(66, 96, 32, 32));
        break;
    case 2: // Archer
        m_sprite.setTextureRect(sf::IntRect(0, 64, 32, 32));
        break;
    case 3: // Wizard
        m_sprite.setTextureRect(sf::IntRect(65, 0, 32, 32));
        break;
    case 4: // Thief
        m_sprite.setTextureRect(sf::IntRect(65, 33, 32, 32));
        break;
    }
}

void Player::reset() {
    m_life = true;       // Возвращаем жизнь
    m_score = 0;         // Сбрасываем счёт
    m_keys = 0;          //Сбрасываем ключи
    setHP(100);        // Восстанавливаем здоровье

    // Обновляем текстуру для текущего класса
    switch (m_class) {
    case 1: // Knight
        m_sprite.setTextureRect(sf::IntRect(66, 96, 32, 32));
        break;
    case 2: // Archer
        m_sprite.setTextureRect(sf::IntRect(0, 64, 32, 32));
        break;
    case 3: // Wizard
        m_sprite.setTextureRect(sf::IntRect(65, 0, 32, 32));
        break;
    case 4: // Thief
        m_sprite.setTextureRect(sf::IntRect(65, 33, 32, 32));
        break;
    }
}


void Player::Update(float time) {
    float CurrentFrame = 0;
    float speed;
    m_state = State::IDLE;
    if (m_life == false) {
        m_state = State::DEAD;
        speed = 0;
    }
    else {
        speed = 1;
        m_controller->controllPlayer(this, time);
    }

    // Выбор текстуры в зависимости от состояния
    switch (m_state) {
    case State::DEAD:
        speed = 0;
        break;

    case State::LEFT:
    case State::RIGHT:
    case State::UP:
    case State::DOWN:
        CurrentFrame += speed * time/800;
        if (CurrentFrame > 3) CurrentFrame -= 3;

        // Анимация зависит от класса
        switch (m_class) {
        case 1: // Knight
            m_sprite.setTextureRect(sf::IntRect(66+32*(int(CurrentFrame)%2), 96, 32, 32));
            break;
        case 2: // Archer
            m_sprite.setTextureRect(sf::IntRect(0 + 32 * (int(CurrentFrame) % 2), 64, 32, 32));
            break;
        case 3: // Wizard
            m_sprite.setTextureRect(sf::IntRect(65 + 32 * (int(CurrentFrame) % 2), 0, 32, 32));
            break;
        case 4: // Thief
            m_sprite.setTextureRect(sf::IntRect(65 + 32 * (int(CurrentFrame) % 2), 33, 32, 32));
            break;
        }
        break;
    }

    m_sprite.setPosition(m_pos);
    interactionWithMap();//вызываем функцию, отвечающую за взаимодействие с картой
    if (m_health <= 0) { m_life = false; speed = 0; }
}

void Player::setState(State state) {
    m_state = state;
}

void Player::interactionWithMap() {
    sf::Vector2f updated_pos = getPosition();
    for (int i = m_pos.y / 32; i < (m_pos.y + m_size.y) / 32; i++)//проходимся по тайликам, контактирующим с игроком, то есть по всем квадратикам размера 32*32, которые мы окрашивали в 9 уроке. про условия читайте ниже.
        for (int j = m_pos.x / 32; j < (m_pos.x + m_size.x) / 32; j++)//икс делим на 32, тем самым получаем левый квадратик, с которым персонаж соприкасается. (он ведь больше размера 32*32, поэтому может одновременно стоять на нескольких квадратах). А j<(x + w) / 32 - условие ограничения координат по иксу. то есть координата самого правого квадрата, который соприкасается с персонажем. таким образом идем в цикле слева направо по иксу, проходя по от левого квадрата (соприкасающегося с героем), до правого квадрата (соприкасающегося с героем)
        {
            if (TileMap[i][j] == '0')//если наш квадратик соответствует символу 0 (стена), то проверяем "направление скорости" персонажа:
            {
                if (m_state==State::DOWN)//если мы шли вниз,
                {
                    m_pos.y = i * 32 - m_size.y;//то стопорим координату игрек персонажа. сначала получаем координату нашего квадратика на карте(стены) и затем вычитаем из высоты спрайта персонажа.
                }
                if (m_state == State::UP)
                {
                    m_pos.y = i * 32 + 32;//аналогично с ходьбой вверх. dy<0, значит мы идем вверх (вспоминаем координаты паинта)
                }
                if (m_state == State::RIGHT)
                {
                    m_pos.x = j * 32 - m_size.x;//если идем вправо, то координата Х равна стена (символ 0) минус ширина персонажа
                }
                if (m_state == State::LEFT)
                {
                    m_pos.x = j * 32 + 32;//аналогично идем влево
                }
            }

            if (TileMap[i][j] == 's') { //если символ равен 's' (камень)
                m_score=m_score+10;
                TileMap[i][j] = ' ';//убираем камень, типа взяли бонус. можем и не убирать, кстати.
            }

            if (TileMap[i][j] == '1') { //если взяли маленькое сокровище
                m_score = m_score + 100;
                TileMap[i][j] = ' ';//убираем камень, типа взяли бонус. можем и не убирать, кстати.
            }

            if (TileMap[i][j] == '2') { //если взяли среднее сокровище
                m_score = m_score + 150;
                TileMap[i][j] = ' ';//убираем камень, типа взяли бонус. можем и не убирать, кстати.
            }

            if (TileMap[i][j] == '3') { //если взяли большое сокровище
                m_score = m_score + 200;
                TileMap[i][j] = ' ';//убираем камень, типа взяли бонус. можем и не убирать, кстати.
            }

            if (TileMap[i][j] == '4') { //если взяли огромное сокровище
                m_score = m_score + 250;
                TileMap[i][j] = ' ';//убираем камень, типа взяли бонус. можем и не убирать, кстати.
            }

            if (TileMap[i][j] == 'f') {
                m_health -= 20;//если взяли ядовитейший в мире цветок
                TileMap[i][j] = ' ';//убрали цветок
            }

            if (TileMap[i][j] == 'w') {
                m_health -= 1;//если взяли коснулись шипов
                if (m_state == State::DOWN)//если мы шли вниз,
                {
                    m_pos.y = i * 32 - m_size.y;//то стопорим координату игрек персонажа. сначала получаем координату нашего квадратика на карте(стены) и затем вычитаем из высоты спрайта персонажа.
                }
                if (m_state == State::UP)
                {
                    m_pos.y = i * 32 + 32;//аналогично с ходьбой вверх. dy<0, значит мы идем вверх (вспоминаем координаты паинта)
                }
                if (m_state == State::RIGHT)
                {
                    m_pos.x = j * 32 - m_size.x;//если идем вправо, то координата Х равна стена (символ 0) минус ширина персонажа
                }
                if (m_state == State::LEFT)
                {
                    m_pos.x = j * 32 + 32;//аналогично идем влево
                }
            }

            if (TileMap[i][j] == 'b') {
                m_health -= 40;//если коснулись бомбу
                TileMap[i][j] = ' ';//убрали бомбу
            }

            if (TileMap[i][j] == 'h') {
                m_health += 20;//если взяли сердечко,то переменная health=health+20;
                TileMap[i][j] = ' ';//убрали сердечко
            }

            if (TileMap[i][j] == '+' || TileMap[i][j] == '-' || TileMap[i][j] == '*' || TileMap[i][j] == '/') {
                m_keys ++;//если взяли ключ,то переменная увеличиваех их число на 1;
                TileMap[i][j] = ' ';//убрали ключ
            }


        }
}
