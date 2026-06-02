#pragma once
#include <string>

namespace Utils {
    void clearScreen();
    void pause();
    void printTitle(const std::string& title);
    void printLine();
    int askInt(const std::string& question, int min, int max);
    std::string askText(const std::string& question);
    int randomInt(int min, int max);
    std::string currentDateTime();

    namespace Color {
        const std::string reset = "\033[0m";
        const std::string red = "\033[31m";
        const std::string green = "\033[32m";
        const std::string yellow = "\033[33m";
        const std::string blue = "\033[34m";
        const std::string cyan = "\033[36m";
        const std::string bold = "\033[1m";
    }
}
