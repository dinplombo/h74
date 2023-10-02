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

OBJECTS = $(SOURCES_DIR)/stack.o $(SOURCES_DIR)/queue_stack.o utest.o 

all: $(TARGET)

check : $(TARGET)
	@./$(TARGET) -v

recheck: clean check

utest : $(OBJECTS)

valgrind: $(TARGET)
	valgrind --log-file=memleak.log --leak-check=full --track-origins=yes -s -s ./$<

clean:
	@$(RM) utest $(OBJECTS)

.PHONY: clean all


# dependencies
$(SOURCES_DIR)/stack.cpp: $(INCLUDES_DIR)/stack.hpp 
$(SOURCES_DIR)/queue_stack.cpp: $(INCLUDES_DIR)/queue_stack.hpp $(INCLUDES_DIR)/stack.hpp
utest.cpp: $(INCLUDES_DIR)/ministack.hpp  $(INCLUDES_DIR)/mu_test.h

