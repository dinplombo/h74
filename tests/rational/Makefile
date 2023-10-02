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

OBJECTS = $(SOURCES_DIR)/rational.o utest.o $(SOURCES_DIR)/helpers.o

all: $(TARGET)

check : $(TARGET)
	@./$(TARGET) -v

recheck: clean check

utest : $(OBJECTS)

clean:
	@$(RM) utest $(OBJECTS)

.PHONY: clean all


# dependencies
helpers.o: helpers.hpp
rational.o: $(INCLUDES_DIR)/rational.hpp $(INCLUDES_DIR)/helpers.hpp 
utest.o: $(INCLUDES_DIR)/rational.hpp $(INCLUDES_DIR)/mu_test.h

