#pragma once
#include <string>
#include <vector>

struct ReactionResult {
    std::string playerName;
    int round = 0;
    long long reactionMs = 0;
    bool falseStart = false;
};

struct AccuracyResult {
    std::string playerName;
    int score = 0;
    int total = 0;
    double accuracy = 0.0;
};

class Game {
public:
    explicit Game(std::string playerName);

    void reactionTest();
    void accuracyTrainer();
    void showSessionStats() const;

private:
    std::string playerName;
    std::vector<ReactionResult> reactionResults;
    std::vector<AccuracyResult> accuracyResults;

    long long getAverageReaction() const;
    long long getBestReaction() const;
};
