CPPC = g++
CFLAGS = -Wall -o list.x 

all: ListInt.cpp main.cpp 
$(CPPC) $(CFLAGS) ListInt.cpp main.cpp
