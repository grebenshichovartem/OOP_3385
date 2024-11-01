#include <iostream>
#include <vector>

#include "BattleField.h"
#include "Segment.h"
#include "DebuggingException.h"
#include "Ship.h"
#include "ShipManager.h"
#include <cctype>

//тестирование Segment и DebuggingException
void TestSegment() {
    try {
        Segment segment;
        segment.printStatus();
        //std::cout << "Только что создался\n";
        segment.takeDamage(1);
        segment.printStatus();
        segment.takeDamage(2);
        segment.printStatus();
        //std::cout << "Должен был уйти в минус\n";
        segment.takeDamage(3);   //вызывает ошибку
    } catch (const DebuggingException &e) {
        std::cout << e.what() << '\n';
    }
    std::cout << "(__________)\n";
}

void TestBattleField() {
    unsigned number_of_ships{};
    std::cout << "Enter number of your ships:";
    std::cin >> number_of_ships;
    while (number_of_ships == 0 || number_of_ships >= 100) {
        std::cout << "You entered none number string or not suitable number(0 < number < 100)\n";
        std::cout << "Try one more time:";
        std::cin >> number_of_ships;
    }
    std::vector<unsigned> sizes(number_of_ships);

    std::cout << "Now enter sizes of your ships:";
    for (unsigned i = 0; i < number_of_ships; i++) {
        std::cin >> sizes.at(i);
    }

    ShipManager player_manager{number_of_ships, sizes};
    ShipManager enemy_manager{player_manager};

    unsigned width, height;
    std::cout << "Enter field width and height(the both are less than 27):\n";
    std::cin >> width >> height;
    while (width == 0 || width > 26 || height == 0 || height > 26) {
        std::cout << "Invalid width or height! Try one more time:";
        std::cin >> width >> height;
    }
    BattleField player_field{width, height, FieldStatus::PlayerField};
    BattleField enemy_field{width, height, FieldStatus::EnemyField};

    std::cout << "Now you need to place your ships\n";
    std::cout << "You'll see numbers - it's sizes of ships those you need to place\n";
    std::cout << "Just enter string in format \"LetterNumber Orientation[h - horizontal/v - vertical] in front of each number\"\n";
    for (unsigned i = 0; i < player_manager.getNumberOfShips(); i++) {
        std::cout << "Your field now:\n";
        player_field.printField();
        std::cout << '\n';
        char x;
        unsigned y;
        std::string orientation;
        Ship &ship = player_manager.getUnplacedShip(i);
        std::cout << ship.getSize() << ":";
        std::cin >> x >> y >> orientation;
        while (y > height || y == 0) {
            std::cout << "Invalid number! It must be less than width or equal it\n";
            std::cin >> y;
        }
        y -= 1;
        while (std::isalpha(x) == 0 || std::toupper(x) > static_cast<int>('A') + width - 1) {
            std::cout << "Invalid letter(or not letter at all lol)!\n";
            std::cin >> x;
        }
        x = std::toupper(x);
        x -= 'A';
        while (orientation != "h" && orientation != "v") {
            std::cout << "Invalid orientation! It must h or v [h - horizontal/v - vertical]\n";
            std::cin >> orientation;
        }

        player_field.placeShip(ship, x, y, (orientation == "h" ? ShipOrientation::Horizontal : ShipOrientation::Vertical));
    }

    for (unsigned i = 0; i < player_manager.getNumberOfShips(); i++) {
        unsigned x = player_manager.getUnplacedShip(i).getX();
        unsigned y = player_manager.getUnplacedShip(i).getY();
        ShipOrientation orientation = player_manager.getUnplacedShip(i).getOrientation();
        enemy_field.placeShip(enemy_manager.getUnplacedShip(i), x, y, orientation);
    }

    unsigned bot_attack = 0;
    char x;
    unsigned y;
    std::cout << "Enemy is ready\n";
    std::cout << "The game is going to start\n";
    while (true) {
        if (player_field.areAllShipsDestroyed()) {
            std::cout << "You loosed :(\n";
            break;
        }
        else if (enemy_field.areAllShipsDestroyed()) {
            std::cout << "Yo bro! You won!\n";
            break;
        }
        std::cout << "Your turn to attack\n";
        std::cout << "Current enemy field:\n";
        enemy_field.printField();
        std::cout << '\n';
        std::cout << "Enter the cell, you want to attack in format LetterNumber(as it was earlier):";
        std::cin >> x >> y;
        while (y > height || y == 0) {
            std::cout << "Invalid number! It must be less than width or equal it\n";
            std::cin >> y;
        }
        y -= 1;
        while (std::isalpha(x) == 0 || std::toupper(x) > static_cast<int>('A') + width - 1) {
            std::cout << "Invalid letter(or not letter at all lol)!\n";
            std::cin >> x;
        }
        x = std::toupper(x);
        x -= 'A';
        enemy_field.attackCell(x, y, 1);

        std::cout << "Enemy's turn to attack\n";
        player_field.attackCell(bot_attack % width, bot_attack / height, 1);
        bot_attack++;
        std::cout << "Your current field:\n";
        player_field.printField();
    }
}
