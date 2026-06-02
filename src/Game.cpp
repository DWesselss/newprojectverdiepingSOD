#include "Game.hpp"
#include "Storage.hpp"
#include "Utils.hpp"
#include <chrono>
#include <iostream>
#include <limits>
#include <thread>

Game::Game(std::string playerName) : playerName(std::move(playerName)) {}

void Game::reactionTest() {
    Utils::printTitle("Reaction Test");

    int rounds = Utils::askInt("Hoeveel rondes wil je spelen?", 3, 10);

    std::cout << "\nRegels:\n";
    std::cout << "- Druk ENTER zodra je GO ziet.\n";
    std::cout << "- Minder dan 80 ms telt als valse start.\n";
    std::cout << "- Elke ronde wordt opgeslagen.\n\n";

    std::cout << "Druk ENTER om te starten...";
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    for (int i = 1; i <= rounds; ++i) {
        Utils::printTitle("Reaction Test - Ronde " + std::to_string(i));

        int waitTime = Utils::randomInt(1200, 4200);
        std::cout << Utils::Color::yellow << "Wacht op groen...\n" << Utils::Color::reset;

        std::this_thread::sleep_for(std::chrono::milliseconds(waitTime));

        std::cout << Utils::Color::green << Utils::Color::bold << "\nGO! Druk ENTER!\n" << Utils::Color::reset;

        auto start = std::chrono::high_resolution_clock::now();
        std::string input;
        std::getline(std::cin, input);
        auto end = std::chrono::high_resolution_clock::now();

        long long reactionMs = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();

        ReactionResult result;
        result.playerName = playerName;
        result.round = i;
        result.reactionMs = reactionMs;
        result.falseStart = reactionMs < 80;

        reactionResults.push_back(result);
        Storage::saveReactionResult(result);

        if (result.falseStart) {
            std::cout << Utils::Color::red << "Valse start! " << reactionMs << " ms\n" << Utils::Color::reset;
        } else if (reactionMs < 180) {
            std::cout << Utils::Color::green << "Insane reactie: " << reactionMs << " ms\n" << Utils::Color::reset;
        } else if (reactionMs < 260) {
            std::cout << Utils::Color::cyan << "Goede reactie: " << reactionMs << " ms\n" << Utils::Color::reset;
        } else {
            std::cout << Utils::Color::yellow << "Reactie: " << reactionMs << " ms\n" << Utils::Color::reset;
        }

        std::this_thread::sleep_for(std::chrono::milliseconds(900));
    }

    showSessionStats();
    Utils::pause();
}

void Game::accuracyTrainer() {
    Utils::printTitle("Accuracy Trainer");

    int rounds = Utils::askInt("Hoeveel targets wil je?", 5, 20);
    int score = 0;

    std::cout << "\nJe krijgt steeds een letter. Typ exact die letter en druk ENTER.\n";
    std::cout << "Druk ENTER om te starten...";
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    for (int i = 1; i <= rounds; ++i) {
        char target = static_cast<char>('A' + Utils::randomInt(0, 25));

        Utils::printTitle("Accuracy Trainer - Target " + std::to_string(i));
        std::cout << "Target: "
                  << Utils::Color::green << Utils::Color::bold
                  << target
                  << Utils::Color::reset << "\n";

        std::string answer;
        std::cout << "Input: ";
        std::getline(std::cin, answer);

        if (!answer.empty() && std::toupper(answer[0]) == target) {
            score++;
            std::cout << Utils::Color::green << "Hit!\n" << Utils::Color::reset;
        } else {
            std::cout << Utils::Color::red << "Miss! Correct was: " << target << "\n" << Utils::Color::reset;
        }

        std::this_thread::sleep_for(std::chrono::milliseconds(600));
    }

    AccuracyResult result;
    result.playerName = playerName;
    result.score = score;
    result.total = rounds;
    result.accuracy = (static_cast<double>(score) / rounds) * 100.0;

    accuracyResults.push_back(result);
    Storage::saveAccuracyResult(result);

    Utils::printTitle("Accuracy Resultaat");
    std::cout << "Score: " << result.score << "/" << result.total << "\n";
    std::cout << "Accuracy: " << result.accuracy << "%\n";

    if (result.accuracy >= 90.0) {
        std::cout << Utils::Color::green << "Sterk, bijna aimbot maar legaal.\n" << Utils::Color::reset;
    } else if (result.accuracy >= 70.0) {
        std::cout << Utils::Color::cyan << "Prima score.\n" << Utils::Color::reset;
    } else {
        std::cout << Utils::Color::yellow << "Kan beter, maar daarom train je.\n" << Utils::Color::reset;
    }

    Utils::pause();
}

void Game::showSessionStats() const {
    Utils::printTitle("Session Stats");

    long long avg = getAverageReaction();
    long long best = getBestReaction();

    if (reactionResults.empty()) {
        std::cout << "Nog geen reaction test gespeeld.\n";
    } else {
        std::cout << "Aantal reaction rondes: " << reactionResults.size() << "\n";
        std::cout << "Beste reactie: " << best << " ms\n";
        std::cout << "Gemiddelde reactie: " << avg << " ms\n";
    }

    Utils::printLine();

    if (accuracyResults.empty()) {
        std::cout << "Nog geen accuracy trainer gespeeld.\n";
    } else {
        const AccuracyResult& last = accuracyResults.back();
        std::cout << "Laatste accuracy score: " << last.score << "/" << last.total << "\n";
        std::cout << "Laatste accuracy: " << last.accuracy << "%\n";
    }
}

long long Game::getAverageReaction() const {
    long long total = 0;
    int count = 0;

    for (const auto& result : reactionResults) {
        if (!result.falseStart) {
            total += result.reactionMs;
            count++;
        }
    }

    if (count == 0) return 0;
    return total / count;
}

long long Game::getBestReaction() const {
    long long best = 999999;

    for (const auto& result : reactionResults) {
        if (!result.falseStart && result.reactionMs < best) {
            best = result.reactionMs;
        }
    }

    if (best == 999999) return 0;
    return best;
}
