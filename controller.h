#ifndef CONTROLLER_H
#define CONTROLLER_H
#include <string>
#include <vector>
#include <map>
#include "rotor.h"

enum CONFIG { NAME, IS_REFLECTOR, MAPPING, NOTCH };

class Controller {
 public:
    Controller() {}
    std::string translate(std::string s);
    bool loadConfig(std::string filename);
    bool setConfig(std::vector<std::string> config_vector);
    void setDebug(bool on);
    void displayAvailableRotors();
 private:
    char translate(char c);
    std::vector<Rotor*> current_rotors_;
    std::map<std::string, Rotor*> rotors_;
    bool debug_;
};
#endif  // CONTROLLER_H
