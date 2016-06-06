#include <iostream>
#include <string>
#include "rotor.h"
#include "utils.h"

int char_to_int(char c) { return static_cast<int>(c - 'A'); }
int int_to_char(int i) { return static_cast<char>('A' + i); }

char Rotor::forward(char c) {
  char new_char = Rotor::mapping()[(char_to_int(c) + offset_) % 26];
  int new_char_int = char_to_int(new_char);
  while (new_char_int - offset() < 0) new_char_int += 26;
  return int_to_char((new_char_int - offset()) % 26);
}

char Rotor::reverse(char c) {
  // takes in output from reverse on the previous rotor, adds offset
  // and finds the map that will generate the letter
  // e.g. rotor1_offset=2, so rotor2_reverse=E, rotor1 maps C->(F=E+1), C-1=[B]
  int pos = mapping().find(std::string(1,
                          int_to_char((char_to_int(c) + offset()) % 26)));
  // b/c -1 % 26 == -1
  while (pos - offset() < 0) pos += 26;
  return int_to_char((pos - offset()) % 26);
}

bool Rotor::rotate() {
  bool should_rotate_next = false;
  if (notch().size() == 0) {
    should_rotate_next = false;
  } else {
    for (int i = 0; i < notch().size(); ++i) {
      if (notch()[i] == int_to_char(offset())) {
        should_rotate_next = true;
        break;
      }
    }
  }
  ++offset_;
  return should_rotate_next;
}
