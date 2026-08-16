#include "utils.h"

#include <iostream>

namespace utils {

std::string trim(const std::string &text) {
    size_t first = text.find_first_not_of(" \t\r\n");
    if (first == std::string::npos) {
        return "";
    }
    size_t last = text.find_last_not_of(" \t\r\n");
    return text.substr(first, last - first + 1);
}

bool parseInt(const std::string &text, int &out) {
    std::string cleaned = trim(text);
    if (cleaned.empty()) {
        return false;
    }
    size_t start = (cleaned[0] == '-') ? 1 : 0;
    if (start == cleaned.size()) {
        return false;
    }
    for (size_t i = start; i < cleaned.size(); ++i) {
        if (cleaned[i] < '0' || cleaned[i] > '9') {
            return false;
        }
    }
    out = std::stoi(cleaned);
    return true;
}

int readMenuChoice(int lowest, int highest) {
    std::string line;
    int value = 0;
    while (true) {
        std::getline(std::cin, line);
        if (parseInt(line, value) && value >= lowest && value <= highest) {
            return value;
        }
        std::cout << "Enter a number between " << lowest << " and " << highest << ": ";
    }
}

std::vector<int> readMarks(int subjectCount, int maxPerSubject) {
    std::vector<int> marks;
    for (int i = 1; i <= subjectCount; ++i) {
        std::cout << "Marks for subject " << i << " (0-" << maxPerSubject << "): ";
        marks.push_back(readMenuChoice(0, maxPerSubject));
    }
    return marks;
}

}
