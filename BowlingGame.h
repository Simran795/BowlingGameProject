#include <vector>

class BowlingGame {
public:
    BowlingGame(); 
    void roll(int pins);
    int score() const;
    int getLastRoll() const;

private:
    std::vector<int> rolls;

    bool isStrike(int index) const;
    bool isSpare(int index) const;
    int strikeBonus(int index) const;
    int spareBonus(int index) const;
    int sumOfBallsInFrame(int index) const;
    int sumRemainingRolls(int index) const;
    bool isValidRoll(int pins) const;

};