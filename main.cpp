#include <iostream>
#include "BowlingGame.h"

int main() {
    BowlingGame game;
    int pins;
    int rollInFrame = 0;
    int frame = 1;
    bool isTenthFrame = false;
    int rollsInTenthFrame = 0;
    std::vector<int> tenthFrameRolls;

    std::cout << "Enter pins knocked down per roll:\n";

    while (frame <= 10) {
        std::cout << "Frame " << frame << ", Roll " << (isTenthFrame ? rollsInTenthFrame + 1 : rollInFrame + 1) << ": ";

        if (!(std::cin >> pins)) {
            std::cout << "Non-numeric input detected. Ending input...\n";
            break;
        }

        try {
            game.roll(pins);

            if (frame < 10) {
                if (pins == 10 && rollInFrame == 0) {
                    // Strike in non-10th frame
                    frame++;
                } else if (rollInFrame == 1) {
                    frame++;
                    rollInFrame = 0;
                } else {
                    rollInFrame++;
                }
            } else {
                // Tenth frame special handling
                tenthFrameRolls.push_back(pins);
                rollsInTenthFrame++;

                if (rollsInTenthFrame == 1) {
                    if (pins == 10) {
                        // Strike on first roll, allow 2 more
                        continue;
                    }
                } else if (rollsInTenthFrame == 2) {
                    if (tenthFrameRolls[0] + tenthFrameRolls[1] >= 10) {
                        // Spare or second strike, allow 1 more
                        continue;
                    } else {
                        break; // No bonus roll
                    }
                } else if (rollsInTenthFrame == 3) {
                    break;
                }
            }

        } catch (const std::invalid_argument& e) {
            std::cerr << "Error: " << e.what() << " Please try again.\n";
            std::cin.clear();
            std::cin.ignore(10000, '\n');
        }
    }

    std::cout << "\nTotal score of Player: " << game.score() << std::endl;
    return 0;
}
