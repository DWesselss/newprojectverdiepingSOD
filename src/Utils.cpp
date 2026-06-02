#include "Utils.hpp"
#include <chrono>
#include <ctime>
#include <iomanip>
#include <iostream>
#include <limits>
#include <random>
#include <sstream>

namespace Utils {
    void clearScreen() {
#ifdef _WIN32
        system("cls");
#else
        system("clear");
#endif
    }

    void pause() {
        std::cout << "\nDruk op ENTER om verder te gaan...";
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }

    void printTitle(const std::string& title) {
        clearScreen();
        std::cout << Color::cyan << Color::bold;
        std::cout << "========================================\n";
        std::cout << "  " << title << "\n";
        std::cout << "========================================\n";
        std::cout << Color::reset;
    }

    void printLine() {
        std::cout << "----------------------------------------\n";
    }

    int askInt(const std::string& question, int min, int max) {
        int value;

        while (true) {
            std::cout << question << " (" << min << "-" << max << "): ";
            std::cin >> value;

            if (!std::cin.fail() && value >= min && value <= max) {
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                return value;
            }

            std::cout << Color::red << "Ongeldige keuze, probeer opnieuw.\n" << Color::reset;
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
    }

    std::string askText(const std::string& question) {
        std::string input;

        do {
            std::cout << question;
            std::getline(std::cin, input);
        } while (input.empty());

        return input;
    }

    int randomInt(int min, int max) {
        static std::random_device rd;
        static std::mt19937 gen(rd());
        std::uniform_int_distribution<int> distribution(min, max);
        return distribution(gen);
    }

    std::string currentDateTime() {
        auto now = std::chrono::system_clock::now();
        auto time = std::chrono::system_clock::to_time_t(now);

        std::stringstream ss;
        ss << std::put_time(std::localtime(&time), "%Y-%m-%d %H:%M:%S");
        return ss.str();
    }
}
