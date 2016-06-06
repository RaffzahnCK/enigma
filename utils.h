#ifndef ENIGMA_UTILS_H
#define ENIGMA_UTILS_H
#include <string>
#include <vector>

namespace utils {
  std::vector<std::string> getNextLineAndSplitIntoTokens(std::istream& str);
}  // namespace utils

#endif  // ENIGMA_UTILS_H
