#include "BowlingGame.h"
#include <stdexcept>

// Constructor//
BowlingGame::BowlingGame() {}

// Function to roll a ball
void BowlingGame::roll(int pins) {
    if (!isValidRoll(pins)) {
        throw std::invalid_argument("Invalid pin count. Must be between 0 and 10.");
    }

    int frame = 0, i = 0;
    
    while (frame < 9 && i < rolls.size()) {
        if (rolls[i] == 10) {
            i += 1; // Strike
        } else {
            i += 2; // Normal frame
        }
        frame++;
    }

    // Validation: Ensure the total pins in a frame (except the 10th) don't exceed 10
  if (frame < 9 && rolls.size() % 2 == 1) { // Second roll validation
    int lastRoll = rolls.back();
    if (lastRoll != 10 && (lastRoll + pins > 10)) {
        throw std::invalid_argument("Invalid frame: total pins cannot exceed 10.");
    }
}



    rolls.push_back(pins);
}

// Get the last roll value
int BowlingGame::getLastRoll() const {
    return (!rolls.empty()) ? rolls.back() : 0;
}

// Calculate total score
int BowlingGame::score() const {
    int totalScore = 0;
    int rollIndex = 0;

    for (int frame = 0; frame < 10; ++frame) {
        if (rollIndex >= rolls.size()) break;

        if (isStrike(rollIndex)) {  
            if (rollIndex + 2 >= rolls.size()) break; // Ensure safe indexing
            totalScore += 10 + strikeBonus(rollIndex);
            rollIndex += 1;
        } else if (isSpare(rollIndex)) {  
            if (rollIndex + 2 >= rolls.size()) break; // Ensure safe indexing
            totalScore += 10 + spareBonus(rollIndex);
            rollIndex += 2;
        } else {  
            if (rollIndex + 1 >= rolls.size()) break; // Ensure safe indexing
            totalScore += sumOfBallsInFrame(rollIndex);
            rollIndex += 2;
        }
    }

    return totalScore;
}

// Check if a roll is a strike
bool BowlingGame::isStrike(int index) const {
    return index < rolls.size() && rolls[index] == 10;
}

// Check if a roll is a spare
bool BowlingGame::isSpare(int index) const {
    return index + 1 < rolls.size() && rolls[index] + rolls[index + 1] == 10;
}

// Get strike bonus (next two rolls)
int BowlingGame::strikeBonus(int index) const {
    if (index + 2 >= rolls.size()) {
        return 0; // Ensure function always returns a valid integer
    }
    return rolls[index + 1] + rolls[index + 2];
}


// Get spare bonus (next roll)
int BowlingGame::spareBonus(int index) const {
    if (index + 2 >= rolls.size()) {
        return 0; // Return zero if index is out of bounds
    }
    return rolls[index + 2];
}


// Get sum of two rolls in a frame
int BowlingGame::sumOfBallsInFrame(int index) const {
    return (index + 1 < rolls.size()) ? rolls[index] + rolls[index + 1] : 0;
}

// Validate roll input
bool BowlingGame::isValidRoll(int pins) const {
    return pins >= 0 && pins <= 10;
}
