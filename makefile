CC=g++
CXX=g++
CFLAGS = -g -std=c++11 -Wall -pedantic
CXXFLAGS = -g -std=c++11 -Wall -pedantic
DEPS = controller.h rotor.h utils.h main-utils.h
OBJ = enigma.o controller.o rotor.o utils.o main-utils.o

all: enigma

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< 

enigma: $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^
#g++ $(CFLAGS) -o $@ $^

clean:
	rm -r *.o enigma
