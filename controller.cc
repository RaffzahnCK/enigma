#include "controller.h"
#include <ctype.h>
#include <iostream>
#include <fstream>
#include "rotor.h"
#include "utils.h"

std::string Controller::translate(std::string s) {
  if (current_rotors_.size() == 0)
    throw std::invalid_argument("No rotors set. "
        "--set_rotors <R1>,...,<RK>,Reflector");
  std::string result = "";
  for (int i = 0; i < s.size(); ++i) {
    // the enigma only translates letters, but in case that the user mistypes
    // let's just not translate that specific non-letter char and output it
    // obviously, this is bad for cryptography
    if (!isalpha(s[i])) {
      result += s[i];
    } else {
      result += Controller::translate(toupper(s[i]));
    }
  }
  return result;
}

char Controller::translate(char c) {
  if (debug_) {
    std::cout << "-- Input [" << c << "]" << std::endl;
  }
  std::vector<Rotor>::size_type num_rotors = current_rotors_.size();
  // first rotor always rotates
  bool should_rotate_next = true;
  char input = c;
  // rotor 1 -> ... -> rotor k -> reflector
  for (int i = 0; i < num_rotors; ++i) {
    input = c;
    if (should_rotate_next) {
      should_rotate_next = current_rotors_[i]->rotate();
    }
    c = current_rotors_[i]->forward(c);
    if (debug_) {
      std::cout << "----- " << "[" << input << "->"  << c << "] (offset="
        << current_rotors_[i]->offset() << ") (pos=" << i << ") - "
        << current_rotors_[i]->type() << " [" << current_rotors_[i]->name()
        << "]" << std::endl;
    }
  }
  // reflector_out -> rotor k -> ... rotor 1
  for (int j = num_rotors - 2; j >= 0; --j) {
    input = c;
    c = current_rotors_[j]->reverse(c);
    if (debug_) {
      std::cout << "----- " << "[" << c << "<-"  << input << "] (offset="
        << current_rotors_[j]->offset() << ") (pos=" << j << ") - "
        << current_rotors_[j]->type() << " [" << current_rotors_[j]->name()
        << "]" << std::endl;
    }
  }
  return c;
}

bool Controller::loadConfig(std::string filename) {
  std::ifstream config_file(filename);
  if (!config_file.good()) {
    throw std::invalid_argument("ERROR: Bad configuration file: " + filename);
  }
  std::vector<std::string> v;
  do {
    v = utils::getNextLineAndSplitIntoTokens(config_file);
    // break when no lines left and ignore comment lines
    if (v.empty() || v[0] == "#") continue;
    if (v.size() != 4)
      throw std::invalid_argument("ERROR: Bad configuration file. "
          " There exists a non-empty non-comment line without 4 csv items");

    if (v[CONFIG::IS_REFLECTOR] == "T") {
      rotors_[v[CONFIG::NAME]] = new Reflector(v[CONFIG::NAME],
                                               v[CONFIG::MAPPING]);
    } else {
      rotors_[v[CONFIG::NAME]] = new Rotor(v[CONFIG::NAME],
                                           v[CONFIG::MAPPING],
                                           v[CONFIG::NOTCH]);
    }
  } while (!v.empty());
  std::cout << "SUCCESS! " << filename << " loaded." << std::endl;
  return 1;
}

bool Controller::setConfig(std::vector<std::string> config_vector) {
  current_rotors_.clear();
  if (rotors_.size() == 0)
    throw std::invalid_argument("No rotor configs available");
  for (int i = 0; i < config_vector.size(); ++i) {
    if (rotors_.count(config_vector[i])) {
      current_rotors_.push_back(rotors_[config_vector[i]]);
    } else {
      current_rotors_.clear();
      throw std::invalid_argument("Rotor/Reflector [" + config_vector[i] +
                                    "] does not exist");
    }
  }

  std::cout << "SUCCESS! New configuration: " << std::endl;
  std::cout << "\tINPUT/OUTPUT";
  for (int i = 0; i < config_vector.size(); ++i) {
    std::cout << " <-> " << rotors_[config_vector[i]]->type() << " ["
      << config_vector[i] << "]";
  }
  std::cout << std::endl;
  return 1;
}

void Controller::displayAvailableRotors() {
  if (rotors_.size() == 0) {
    std::cout << "No rotors available. Did you load the config file via "
      "--config <filename>?" << std::endl;
    return;
  }
  std::cout << "Here are the available rotors:" << std::endl;
  for (auto r = rotors_.begin(); r != rotors_.end(); ++r) {
    std::cout << "% " << r->second->type() << " [" << r->second->name()
      << "]" << std::endl;
    std::cout << "    FRM: " << "ABCDEFGHIJKLMNOPQRSTUVWXYZ" << std::endl;
    std::cout << "    MAP: " << r->second->mapping() << std::endl;

    if (r->second->type() == typeid(Rotor).name())
      std::cout << "    TURN NOTCH: " << r->second->notch() << std::endl;
  }
}

void Controller::setDebug(bool on) {
  debug_ = on;
  std::string state = on ? "on." : "off.";
  std::cout << "Debug is " << state << std::endl;
}
