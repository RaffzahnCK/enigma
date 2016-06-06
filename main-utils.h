#include <string>
#include <vector>

bool matches_arg(std::string str, std::string pattern, int start_pos);

std::string findOptionsArg(std::string str, int start_pos);

std::string trim(std::string str);

std::vector<std::string> &split(const std::string &s, char delim, std::vector<std::string> &elems);

std::vector<std::string> split(const std::string &s, char delim);

void help();
