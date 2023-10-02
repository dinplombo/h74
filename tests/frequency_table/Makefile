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

OBJECTS = $(SOURCES_DIR)/frequency_table.o utest.o

all: $(TARGET)

freq: freq

check : $(TARGET)
	@./$(TARGET) -v

recheck: clean check

utest : $(OBJECTS)

freq: freq.o $(SOURCES_DIR)/frequency_table.o

valgrind: $(TARGET)
	valgrind --log-file=memleak.log --leak-check=full --track-origins=yes -s ./$<

clean:
	@$(RM) utest $(OBJECTS)

.PHONY: clean all



# dependencies
$(SOURCES_DIR)/frequency_table.cpp: $(INCLUDES_DIR)/frequency_table.hpp 
utest.cpp: $(INCLUDES_DIR)/frequency_table.hpp $(INCLUDES_DIR)/mu_test.h
# $(INCLUDES_DIR)/frequency_table.hpp: $(INCLUDES_DIR)/genric_aloritms.hpp
freq.o: $(INCLUDES_DIR)/frequency_table.hpp $(SOURCES_DIR)/frequency_table.cpp