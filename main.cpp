#include <iostream>
#include <vector>
#include "BowlingGame.h"

// Helper function for validated user input
int getValidInput() {
    int pins;
    while (true) {
        std::cin >> pins;
        if (std::cin.fail() || pins < 0 || pins > 10) {
            std::cin.clear();
            std::cin.ignore(10000, '\n');
            std::cout << "Invalid input. Enter a number between 0 and 10: ";
        } else {
            break;
        }
    }
    return pins;
}

int main() {
    BowlingGame game;
    int frame = 1, rollInFrame = 0, rollsInTenthFrame = 0;
    std::vector<int> tenthFrameRolls;

    std::cout << "Enter pins knocked down per roll:\n";

    while (frame <= 10) {
        std::cout << "Frame " << frame << ", Roll " 
                  << ((frame == 10) ? rollsInTenthFrame + 1 : rollInFrame + 1) << ": ";

        int pins = getValidInput();

        // Handle 10th frame logic separately
        if (frame == 10) {
            if (rollsInTenthFrame == 1 && tenthFrameRolls[0] != 10 && tenthFrameRolls[0] + pins > 10) {
                std::cout << "Invalid frame: total pins in a frame cannot exceed 10. Please try again.\n";
                continue;
            }

            tenthFrameRolls.push_back(pins);
            try {
                game.roll(pins);
            } catch (const std::invalid_argument& e) {
                std::cerr << "Error: " << e.what() << " Please try again.\n";
                tenthFrameRolls.pop_back();
                continue;
            }

            rollsInTenthFrame++;
            if (rollsInTenthFrame == 1 && pins == 10) continue;
            if (rollsInTenthFrame == 2 && (tenthFrameRolls[0] == 10 || tenthFrameRolls[0] + tenthFrameRolls[1] == 10)) continue;
            if (rollsInTenthFrame == 3) break;
            if (rollsInTenthFrame == 2 && tenthFrameRolls[0] + tenthFrameRolls[1] < 10) break;

        } else {
            // Normal frame validation
      if (rollInFrame == 1) { // Validate second roll
    int previousRoll = game.getLastRoll();
    if (previousRoll + pins > 10) {
        std::cout << "Invalid frame: total pins cannot exceed 10. Try again.\n";
        continue;
    }
}





            try {
                game.roll(pins);
            } catch (const std::invalid_argument& e) {
                std::cerr << "Error: " << e.what() << " Please try again.\n";
                continue;
            }

            if (pins == 10 && rollInFrame == 0) {
                frame++;
            } else if (rollInFrame == 1) {
                frame++;
                rollInFrame = 0;
            } else {
                rollInFrame++;
            }
        }
    }

    std::cout << "\nTotal score of Player: " << game.score() << std::endl;
    return 0;
}
