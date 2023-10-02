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
	valgrind --leak-check=yes -s -q ./$<

clean:
	@$(RM) utest $(OBJECTS) 

.PHONY: clean all

# dependencies
utest.o: $(INCLUDES_DIR)/smart_ptr.hpp $(INCLUDES_DIR)/mu_test.h $(INCLUDES_DIR)/inl/smart_ptr.hxx $(INCLUDES_DIR)/stack.hpp
$(SOURCES_DIR)/stack.o: $(INCLUDES_DIR)/stack.hpp