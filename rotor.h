#ifndef ROTOR_H
#define ROTOR_H
#include <typeinfo>
#include <string>

int char_to_int(char c);
int int_to_char(int i);

class Rotor {
 public:
    Rotor()
      : name_("Default"), mapping_("ABCDEFGHIJKLMNOPQRSTUVWXYZ"), notch_("") {}
    Rotor(std::string name, std::string mapping, std::string notch)
      : name_(name), mapping_(mapping), notch_(notch), offset_(0) {}
    char forward(char c);
    char reverse(char c);
    // rotates the mapping, returns true if the next rotor should rotate
    virtual bool rotate();

    std::string type() const { return typeid(*this).name(); }
    std::string name() const { return name_; }
    std::string mapping() const { return mapping_; }
    std::string notch() const { return notch_; }
    int offset() const { return offset_; }
 private:
    std::string name_;
    std::string mapping_;
    std::string notch_;
    unsigned int offset_;
};

class Reflector : public Rotor {
 public:
    Reflector(std::string name, std::string mapping)
      : Rotor(name, mapping, "") {}
    bool rotate() { return false; }
};
#endif  // ROTOR_H
