CXX = g++
CC = $(CXX)

CFLAGS = -Wall -Werror
CFLAGS += -Wextra
CFLAGS += -pedantic
CFLAGS += -g3

CXXFLAGS = $(CFLAGS)
CXXFLAGS += -std=c++17

INCLUDES_DIR = ../../inc
SOURCES_DIR = ../../src

TARGET = utest

# flags for preprocessor
CPPFLAGS = -I$(INCLUDES_DIR)

LDLIBS += -lpthread

OBJECTS = utest.o $(SOURCES_DIR)/thread_vector.o

all: $(TARGET)

check : $(TARGET)
	@./$(TARGET) -v

recheck: clean check

$(TARGET) : $(OBJECTS)

valgrind: $(TARGET)
	valgrind --leak-check=yes -s -q ./$<

clean:
	@$(RM) thread_vector $(OBJECTS)

.PHONY: clean all

# dependencies
$(SOURCES_DIR)/thread_vector.o: $(INCLUDES_DIR)/thread_vector.hpp 
utest.o: $(INCLUDES_DIR)/thread_vector.hpp $(INCLUDES_DIR)/mu_test.h
