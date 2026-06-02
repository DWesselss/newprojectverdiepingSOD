#include "Game.hpp"
#include "Storage.hpp"
#include "Utils.hpp"
#include <iostream>

int main() {
    Utils::printTitle("Reaction Lab");

    std::cout << "Welkom bij Reaction Lab.\n";
    std::cout << "Een C++ terminal game voor reactietijd, accuracy en high scores.\n\n";

    std::string playerName = Utils::askText("Voer je naam in: ");
    Game game(playerName);

    bool running = true;

    while (running) {
        Utils::printTitle("Reaction Lab - Menu");

        std::cout << "Speler: " << Utils::Color::green << playerName << Utils::Color::reset << "\n\n";
        std::cout << "1. Reaction Test\n";
        std::cout << "2. Accuracy Trainer\n";
        std::cout << "3. High Scores bekijken\n";
        std::cout << "4. Session Stats\n";
        std::cout << "5. Naam aanpassen\n";
        std::cout << "6. Stoppen\n\n";

        int choice = Utils::askInt("Kies een optie", 1, 6);

        switch (choice) {
            case 1:
                game.reactionTest();
                break;
            case 2:
                game.accuracyTrainer();
                break;
            case 3:
                Storage::showHighScores();
                break;
            case 4:
                game.showSessionStats();
                Utils::pause();
                break;
            case 5: {
                Utils::printTitle("Naam aanpassen");
                playerName = Utils::askText("Voer je nieuwe naam in: ");
                game = Game(playerName);
                std::cout << Utils::Color::green << "\nNaam aangepast naar: "
                          << playerName << Utils::Color::reset << "\n";
                Utils::pause();
                break;
            }
            case 6:
                running = false;
                break;
        }
    }

    Utils::printTitle("Reaction Lab");
    std::cout << "Bedankt voor het spelen, " << playerName << "!\n";
    return 0;
}
