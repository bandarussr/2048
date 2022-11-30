CFLAGS ?= -std=c++98 -Wall -Wextra -Iinclude

# -------------------------
# This means that when you just type "make", you make all of the executables

ALL = bin/main \

all: $(ALL)

# -------------------------
# "make clean" deletes the object files and binaries

clean:
	rm -f obj/* bin/*

# -------------------------
# Object files

obj/twenty-fourty-eight.o: src/twenty-fourty-eight.cpp src/twenty-fourty-eight.h
	g++ $(CFLAGS) -c -o obj/twenty-fourty-eight.o src/twenty-fourty-eight.cpp

obj/main.o: src/main.cpp src/twenty-fourty-eight.h
	g++ $(CFLAGS) -c -o obj/main.o src/main.cpp

# -------------------------
# Executables

bin/main: obj/twenty-fourty-eight.o obj/main.o
	g++ $(CFLAGS) -o bin/2048 obj/main.o obj/twenty-fourty-eight.o
