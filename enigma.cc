#include <string>
#include <sstream>
#include <iostream>
#include <algorithm>
#include <exception>
#include "controller.h"
#include "main-utils.h"

static const std::string OPTIONS_FLAG = "--";
static int OPTIONS_POS = 2;
static const std::string HELP = "help";
static const std::string DISPLAY_AVAILABLE_ROTORS = "rotors";
static const std::string LOAD_CONFIG = "config";
static const std::string SET_ROTORS = "set_rotors";
static const std::string SET_START_POS = "set_rotors_pos";
static const std::string DEBUG = "debug";


int main() {
  Controller c;
  try {
    c.loadConfig("rotor.config");
    const std::vector<std::string> config_vector = {"3", "2", "1", "B"};
    c.setConfig(config_vector);
  } catch (std::exception& e) {
    std::cout << e.what() << std::endl;
  }

  std::cout << "Use --help for available commands." << std::endl;

  std::cout << "> ";
  std::string input;
  std::string encoding;
  bool state;
  while (getline(std::cin, input)) {
    try {
      if (matches_arg(input, OPTIONS_FLAG, 0)) {
        if (matches_arg(input, HELP, OPTIONS_POS)) {
          help();
        } else if (matches_arg(input, DISPLAY_AVAILABLE_ROTORS, OPTIONS_POS)) {
          c.displayAvailableRotors();
        } else if (matches_arg(input, LOAD_CONFIG, OPTIONS_POS)) {
          std::string filename = findOptionsArg(input,
                                            OPTIONS_POS + LOAD_CONFIG.size());
          c.loadConfig(filename);
        } else if (matches_arg(input, SET_ROTORS, OPTIONS_POS)) {
          std::string str = findOptionsArg(input,
                                            OPTIONS_POS + SET_ROTORS.size());
          std::vector<std::string> config_vec = split(str, ',');
          for (int i = 0; i < config_vec.size(); ++i) {
            config_vec[i] = trim(config_vec[i]);
          }
          c.setConfig(config_vec);
        } else if (matches_arg(input, SET_START_POS, OPTIONS_POS)) {
        } else if (matches_arg(input, DEBUG, OPTIONS_POS)) {
          std::string str = findOptionsArg(input, OPTIONS_POS + DEBUG.size());
          std::transform(str.begin(), str.end(), str.begin(), ::toupper);
          state = str.compare("TRUE") == 0 ? true : false;
          c.setDebug(state);
        } else {
          std::cout << "Command not recognized. Use --help to see "
            "available commands." << std::endl;
        }
      } else {
        encoding = c.translate(input);
        std::cout << "INPUT  - " << input << std::endl;
        std::cout << "OUTPUT - " << encoding << std::endl;
      }
    } catch (std::exception& e) {
      std::cout << e.what() << std::endl;
    }
    std::cout << "> ";
  }
}
