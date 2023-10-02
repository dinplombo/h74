CXX = g++
CC = $(CXX)

CFLAGS = -Wall -Werror
CFLAGS+= -Wextra
CFLAGS+= -pedantic
CFLAGS+= -g3

CXXFLAGS = $(CFLAGS)
CXXFLAGS += -std=c++17

INCLUDES_DIR = ../../inc
SOURCES_DIR = ../../src

TARGET = utest

# flags for preprocessor
CPPFLAGS = -I$(INCLUDES_DIR)

OBJECTS = utest.o $(SOURCES_DIR)/stack.o 

all: $(TARGET)

check : $(TARGET)
	@./$(TARGET) -v

recheck: clean check

utest : $(OBJECTS)

valgrind: $(TARGET)
	valgrind --log-file=memleak.log --leak-check=full --track-origins=yes -s ./$<

clean:
	@$(RM) utest $(OBJECTS)

.PHONY: clean all



# dependencies
$(SOURCES_DIR)/stack.o: $(INCLUDES_DIR)/stack.hpp
utest.cpp: $(INCLUDES_DIR)/stack.hpp $(INCLUDES_DIR)/mu_test.h

