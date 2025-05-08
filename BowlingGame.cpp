#include "BowlingGame.h"
#include <stdexcept>

void BowlingGame::roll(int pins) {
    if (!isValidRoll(pins)) {
        throw std::invalid_argument("Invalid pin count. Must be between 0 and 10.");
    }
    rolls.push_back(pins);
}

int BowlingGame::score() const {
    int totalScore = 0;
    int rollIndex = 0;

    for (int frame = 0; frame < 9; ++frame) {
        if (rollIndex >= rolls.size()) break;

        if (isStrike(rollIndex)) {
            if (rollIndex + 2 >= rolls.size()) break;
            totalScore += 10 + strikeBonus(rollIndex);
            rollIndex += 1;
        } else if (isSpare(rollIndex)) {
            if (rollIndex + 2 >= rolls.size()) break;
            totalScore += 10 + spareBonus(rollIndex);
            rollIndex += 2;
        } else {
            if (rollIndex + 1 >= rolls.size()) break;
            totalScore += sumOfBallsInFrame(rollIndex);
            rollIndex += 2;
        }
    }

    totalScore += sumRemainingRolls(rollIndex);
    return totalScore;
}

bool BowlingGame::isStrike(int index) const {
    return index < rolls.size() && rolls[index] == 10;
}

bool BowlingGame::isSpare(int index) const {
    return index + 1 < rolls.size() && rolls[index] + rolls[index + 1] == 10;
}

int BowlingGame::strikeBonus(int index) const {
    return rolls[index + 1] + rolls[index + 2];
}

int BowlingGame::spareBonus(int index) const {
    return rolls[index + 2];
}

int BowlingGame::sumOfBallsInFrame(int index) const {
    return rolls[index] + rolls[index + 1];
}

int BowlingGame::sumRemainingRolls(int index) const {
    int sum = 0;
    for (int i = index; i < rolls.size(); ++i) {
        sum += rolls[i];
    }
    return sum;
}

bool BowlingGame::isValidRoll(int pins) const {
    return pins >= 0 && pins <= 10;
}