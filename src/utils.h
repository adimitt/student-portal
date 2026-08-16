#ifndef UTILS_H
#define UTILS_H

#include <string>
#include <vector>

// Console input helpers. Every read re-prompts until the value parses,
// so the menu loop never has to deal with a failed stream.
namespace utils {

std::string trim(const std::string &text);
bool parseInt(const std::string &text, int &out);
int readMenuChoice(int lowest, int highest);
std::vector<int> readMarks(int subjectCount, int maxPerSubject);

}

#endif
