#include <iostream>
#include "BowlingGame.h"

int main() {
    BowlingGame game;
    std::vector<int> rolls = {1, 4, 4, 5, 6, 4, 5, 5, 10,
                               0, 1, 7, 3, 6, 4, 10, 2, 8, 6};

    try {
        for (int pins : rolls) {
            game.roll(pins);
        }
        std::cout << "Total score of Player: " << game.score() << std::endl;
    } catch (const std::invalid_argument& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }

    return 0;
}
