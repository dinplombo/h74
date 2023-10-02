CXX = g++
CC = $(CXX)

CFLAGS = -Wall -Werror
CFLAGS+= -Wextra
CFLAGS+= -pedantic
CFLAGS+= -g3

CXXFLAGS = $(CFLAGS)
CXXFLAGS += -std=c++17

# INCLUDES_DIR = ../../inc
# SOURCES_DIR = ../../src

TARGET = demo

# flags for preprocessor
# CPPFLAGS = -I$(INCLUDES_DIR)
LDLIBS = -lsfml-graphics -lsfml-window -lsfml-system

OBJECTS = demo.o 

all: $(TARGET)

check : $(TARGET)
	@./$(TARGET) -v

recheck: clean check

$(TARGET) : $(OBJECTS)

# valgrind: $(TARGET)
# 	valgrind --log-file=memleak.log --leak-check=full --track-origins=yes -s ./$<

clean:
	@$(RM) demo $(OBJECTS)

.PHONY: clean all

# dependencies 

