#pragma once
#include "Game.hpp"
#include <string>
#include <vector>

class Storage {
public:
    static void saveReactionResult(const ReactionResult& result);
    static void saveAccuracyResult(const AccuracyResult& result);

    static std::vector<ReactionResult> loadReactionResults();
    static std::vector<AccuracyResult> loadAccuracyResults();

    static void showHighScores();

private:
    static std::string reactionFile();
    static std::string accuracyFile();
};
