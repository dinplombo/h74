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

OBJECTS = utest.o $(SOURCES_DIR)/caesar_encryption.o $(SOURCES_DIR)/text_message.o

all: $(TARGET)

check : $(TARGET)
	@$(RM) my_secrets.txt
	@echo "nznmba cnf12f\nsnprobbx cnffjbeq" > load_test.txt
	@./$(TARGET) -v

recheck: clean check

utest : $(OBJECTS)

valgrind: $(TARGET)
	valgrind --leak-check=yes -s -q ./$<

clean:
	@$(RM) utest $(OBJECTS) my_secrets.txt load_test.txt

.PHONY: clean all

# dependencies
utest.o: $(INCLUDES_DIR)/vault_secrets.hpp $(INCLUDES_DIR)/mu_test.h $(INCLUDES_DIR)/inl/vault_secrets.hxx\
		 $(INCLUDES_DIR)/caesar_encryption.hpp $(INCLUDES_DIR)/encoder.hpp 
$(INCLUDES_DIR)/vault_secrets.hpp : $(INCLUDES_DIR)/encoder.hpp 
$(INCLUDES_DIR)/inl/vault_secrets.hxx : $(INCLUDES_DIR)/vault_secrets.hpp $(INCLUDES_DIR)/text_message.hpp $(INCLUDES_DIR)/encoder.hpp 
$(SOURCES_DIR)/caesar_encryption.o: $(INCLUDES_DIR)/caesar_encryption.hpp $(INCLUDES_DIR)/encoder.hpp 
$(SOURCES_DIR)/text_message.o: $(INCLUDES_DIR)/text_message.hpp $(INCLUDES_DIR)/message.hpp 

