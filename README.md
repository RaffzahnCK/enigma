# Enigma
C++ implementation of the WWII German cipher machine.

### Dependencies
[Bazel](http://www.bazel.io)

### Usage
1. Build enigma
 * `bazel build :enigma`
2. Run enigma
 * `bazel-bin/enigma`

#### Available commands (--help):
* --rotors : Displays available rotors
* --debug [true/false] : Show inputs/outputs of each rotor/reflector during computation
* --config <filename> : Loads available rotors from a rotor configuration file. See rotor.config for example.
* --set_rotors  <Rotor 1 name>,...<Rotor 2 name>,<Reflector name> : Defines current rotor configuration in Enigma
 * 	example: --set_rotors 1,2,3,B loads Rotor 1, Rotor 2, Rotor 3, Reflector B
* --set_pos : Sets current states of each rotor
 *	example: --set_rotors_pos A,B,C sets Rotor [1] to A, Rotor [2]  to B and Rotor [3] to C. Reflectors don't have a state, so no need to set a state for the reflector.
* Type words at > to encode/decode messages.

### Screenshots

![alt text](https://github.com/bsuper/enigma/blob/master/imgs/ss1.png "HELLOWORLD from this Enigma Machine")

[3rd party Enigma Machine](http://enigmaco.de/enigma/enigma.html)
![alt text](https://github.com/bsuper/enigma/blob/master/imgs/3p-2.png "3rd party same setup")
![alt text](https://github.com/bsuper/enigma/blob/master/imgs/3p-1.png "HELLOWORLD from 3rd party Machine")
