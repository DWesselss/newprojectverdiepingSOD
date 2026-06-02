#include "Storage.hpp"
#include "Utils.hpp"
#include <algorithm>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>

std::string Storage::reactionFile() {
    return "../data/reaction_scores.csv";
}

std::string Storage::accuracyFile() {
    return "../data/accuracy_scores.csv";
}

void Storage::saveReactionResult(const ReactionResult& result) {
    std::ofstream file(reactionFile(), std::ios::app);

    if (!file) {
        std::cout << Utils::Color::red << "Kon reaction score niet opslaan.\n" << Utils::Color::reset;
        return;
    }

    file << Utils::currentDateTime() << ","
         << result.playerName << ","
         << result.round << ","
         << result.reactionMs << ","
         << (result.falseStart ? "true" : "false") << "\n";
}

void Storage::saveAccuracyResult(const AccuracyResult& result) {
    std::ofstream file(accuracyFile(), std::ios::app);

    if (!file) {
        std::cout << Utils::Color::red << "Kon accuracy score niet opslaan.\n" << Utils::Color::reset;
        return;
    }

    file << Utils::currentDateTime() << ","
         << result.playerName << ","
         << result.score << ","
         << result.total << ","
         << std::fixed << std::setprecision(2) << result.accuracy << "\n";
}

std::vector<ReactionResult> Storage::loadReactionResults() {
    std::vector<ReactionResult> results;
    std::ifstream file(reactionFile());
    std::string line;

    while (std::getline(file, line)) {
        std::stringstream ss(line);
        std::string date, name, round, reaction, falseStart;

        std::getline(ss, date, ',');
        std::getline(ss, name, ',');
        std::getline(ss, round, ',');
        std::getline(ss, reaction, ',');
        std::getline(ss, falseStart, ',');

        if (!name.empty() && !reaction.empty()) {
            ReactionResult r;
            r.playerName = name;
            r.round = std::stoi(round);
            r.reactionMs = std::stoll(reaction);
            r.falseStart = falseStart == "true";
            results.push_back(r);
        }
    }

    return results;
}

std::vector<AccuracyResult> Storage::loadAccuracyResults() {
    std::vector<AccuracyResult> results;
    std::ifstream file(accuracyFile());
    std::string line;

    while (std::getline(file, line)) {
        std::stringstream ss(line);
        std::string date, name, score, total, accuracy;

        std::getline(ss, date, ',');
        std::getline(ss, name, ',');
        std::getline(ss, score, ',');
        std::getline(ss, total, ',');
        std::getline(ss, accuracy, ',');

        if (!name.empty() && !score.empty()) {
            AccuracyResult r;
            r.playerName = name;
            r.score = std::stoi(score);
            r.total = std::stoi(total);
            r.accuracy = std::stod(accuracy);
            results.push_back(r);
        }
    }

    return results;
}

void Storage::showHighScores() {
    Utils::printTitle("High Scores");

    auto reactions = loadReactionResults();
    auto accuracies = loadAccuracyResults();

    reactions.erase(
        std::remove_if(reactions.begin(), reactions.end(),
            [](const ReactionResult& r) { return r.falseStart; }),
        reactions.end()
    );

    std::sort(reactions.begin(), reactions.end(),
        [](const ReactionResult& a, const ReactionResult& b) {
            return a.reactionMs < b.reactionMs;
        }
    );

    std::sort(accuracies.begin(), accuracies.end(),
        [](const AccuracyResult& a, const AccuracyResult& b) {
            if (a.accuracy == b.accuracy) return a.score > b.score;
            return a.accuracy > b.accuracy;
        }
    );

    std::cout << Utils::Color::yellow << "Beste reactietijden:\n" << Utils::Color::reset;
    if (reactions.empty()) {
        std::cout << "Nog geen scores.\n";
    } else {
        for (size_t i = 0; i < reactions.size() && i < 5; ++i) {
            std::cout << i + 1 << ". " << reactions[i].playerName
                      << " - " << reactions[i].reactionMs << " ms\n";
        }
    }

    Utils::printLine();

    std::cout << Utils::Color::yellow << "Beste accuracy scores:\n" << Utils::Color::reset;
    if (accuracies.empty()) {
        std::cout << "Nog geen scores.\n";
    } else {
        for (size_t i = 0; i < accuracies.size() && i < 5; ++i) {
            std::cout << i + 1 << ". " << accuracies[i].playerName
                      << " - " << accuracies[i].score << "/" << accuracies[i].total
                      << " (" << std::fixed << std::setprecision(1)
                      << accuracies[i].accuracy << "%)\n";
        }
    }

    Utils::pause();
}
