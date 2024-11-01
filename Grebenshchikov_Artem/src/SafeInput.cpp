#include <iostream>
#include <limits>
#include "SafeInput.h"
#include "BattleshipException.h"



int safeInput() {
    int number;
    while (true) {
        try {
            std::cin >> number;
            if (std::cin.fail()) {
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                throw InvalidInputError();
            }
            return number;
        } catch (InvalidInputError& e) {
            std::cout << e.what() << std::endl;
        }
    }
}