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

OBJECTS = utest.o $(SOURCES_DIR)/helpers.o

all: $(TARGET)

check : $(TARGET)
	@./$(TARGET) -v

recheck: clean check

utest : $(OBJECTS)

valgrind: $(TARGET)
	valgrind --leak-check=yes -s -q ./$<

clean:
	@$(RM) utest $(OBJECTS)

.PHONY: clean all


# dependencies
utest.o: $(INCLUDES_DIR)/sym_matrix.hpp  $(INCLUDES_DIR)/mu_test.h 
$(INCLUDES_DIR)/sym_matrix.hpp: $(INCLUDES_DIR)/helpers.hpp
$(SOURCES_DIR)/helpers.o: $(INCLUDES_DIR)/helpers.hpp



