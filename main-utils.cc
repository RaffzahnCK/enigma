#include <iostream>
#include <sstream>
#include "main-utils.h"

bool matches_arg(std::string str, std::string pattern, int start_pos) {
  return str.compare(start_pos, pattern.size(), pattern) == 0;
}

std::string findOptionsArg(std::string str, int start_pos) {
  std::string str2 = str.substr(start_pos, str.size() - start_pos);
  return trim(str2);
}

std::string trim(std::string str) {
  int start = str.find_first_not_of(' ');
  int end = str.find_last_not_of(' ');
  return str.substr(start, (end + 1 - start));
}

std::vector<std::string> &split(const std::string &s,
                                char delim,
                                std::vector<std::string> &elems) {
  std::stringstream ss(s);
  std::string item;
  while (std::getline(ss, item, delim)) {
    if (!item.empty()) elems.push_back(item);
  }
  return elems;
}

std::vector<std::string> split(const std::string &s, char delim) {
  std::vector<std::string> elems;
  split(s, delim, elems);
  return elems;
}

void help() {
  std::cout << "--rotors : Displays available rotors" << std::endl;
  std::cout << "--debug [true/false] : Show inputs/outputs of each "
    "rotor/reflector during computation " << std::endl;
  std::cout << "--config <filename> : Loads available rotors from a rotor "
    "configuration file. See rotor.config for example." << std::endl;
  std::cout << "--set_rotors  <Rotor 1 name>,...<Rotor 2 name>,<Reflector name>"
    " : Defines current rotor configuration in Enigma " <<
    "\n\texample: --set_rotors 1,2,3,B loads Rotor 1, Rotor 2, Rotor 3, "
    "Reflector B" << std::endl;
  std::cout << "--set_pos : Sets current states of each rotor " <<
    "\n\texample: --set_rotors_pos A,B,C sets Rotor [1] to A, Rotor [2]  to B "
    "and Rotor [3] to C. Reflectors don't have a state, so no need to set a "
    "state for the reflector." << std::endl;
  std::cout << "Type words at > to encode/decode messages. " << std::endl;
}
