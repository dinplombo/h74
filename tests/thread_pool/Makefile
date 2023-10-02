CXX = g++
CC = $(CXX)

CFLAGS = -Wall -Werror
CFLAGS += -Wextra
CFLAGS += -pedantic
CFLAGS += -g3
CFLAGS += -pthread

CXXFLAGS = $(CFLAGS)
CXXFLAGS += -std=c++17

INCLUDES_DIR = ../../inc
SOURCES_DIR = ../../src

TARGET = utest 

# flags for preprocessor
CPPFLAGS = -I$(INCLUDES_DIR)

LDLIBS += -lpthread

OBJECTS = utest.o $(SOURCES_DIR)/thread_pool.o

all: $(TARGET)

check : $(TARGET)
	@./$(TARGET) -v

recheck: clean check

$(TARGET) : $(OBJECTS)

hell: $(TARGET)
	valgrind --tool=helgrind -s ./$(TARGET) 2> hell.log

valgrind: $(TARGET)
	valgrind --leak-check=yes -s -q ./$<

clean:
	@$(RM) $(OBJECTS) hell.log

.PHONY: clean all

# dependencies
utest.o: $(INCLUDES_DIR)/blocking_queue.hpp $(INCLUDES_DIR)/inl/blocking_queue.hxx $(INCLUDES_DIR)/mu_test.h
$(SOURCES_DIR)/thread_pool.o: $(INCLUDES_DIR)/thread_pool.hpp $(INCLUDES_DIR)/blocking_queue.hpp $(INCLUDES_DIR)/task.hpp\
	$(INCLUDES_DIR)/my_execption.hpp

