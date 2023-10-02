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

OBJECTS = $(SOURCES_DIR)/udp_client.o $(SOURCES_DIR)/file_destination.o $(SOURCES_DIR)/precious_stone.o $(SOURCES_DIR)/consol_destination.o $(SOURCES_DIR)/consol_source.o\
	$(SOURCES_DIR)/message.o $(SOURCES_DIR)/substitution_encoder.o $(SOURCES_DIR)/scytale.o $(SOURCES_DIR)/stream_base.o\
	$(SOURCES_DIR)/file_source.o $(SOURCES_DIR)/leetcode.o $(SOURCES_DIR)/uppercase.o $(SOURCES_DIR)/caesar_encryption.o $(SOURCES_DIR)/vowels.o\
	$(SOURCES_DIR)/stream_destination.o $(SOURCES_DIR)/text_message.o $(SOURCES_DIR)/transposition_ciper.o $(SOURCES_DIR)/rot13.o utest.o

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
$(SOURCES_DIR)/uppercase.o: $(INCLUDES_DIR)/uppercase.hpp $(INCLUDES_DIR)/encoder.hpp 
$(SOURCES_DIR)/message.o: $(INCLUDES_DIR)/message.hpp
$(SOURCES_DIR)/leetcode.o: $(INCLUDES_DIR)/leetcode.hpp $(INCLUDES_DIR)/substitution_encoder.hpp 
$(SOURCES_DIR)/scytale.o: $(INCLUDES_DIR)/scytale.hpp $(INCLUDES_DIR)/encoder.hpp 
$(SOURCES_DIR)/vowels.o: $(INCLUDES_DIR)/vowels.hpp $(INCLUDES_DIR)/substitution_encoder.hpp 
$(SOURCES_DIR)/substitution_encoder.o: $(INCLUDES_DIR)/substitution_encoder.hpp $(INCLUDES_DIR)/encoder.hpp 
$(SOURCES_DIR)/caesar_encryption.o: $(INCLUDES_DIR)/caesar_encryption.hpp $(INCLUDES_DIR)/encoder.hpp 
$(SOURCES_DIR)/transposition_ciper.hpp.o: $(INCLUDES_DIR)/transposition_ciper.hpp.hpp $(INCLUDES_DIR)/encoder.hpp 
$(SOURCES_DIR)/rot13.o: $(INCLUDES_DIR)/rot13.hpp $(INCLUDES_DIR)/encoder.hpp $(INCLUDES_DIR)/caesar_encryption.hpp
$(SOURCES_DIR)/text_message.o: $(INCLUDES_DIR)/text_message.hpp $(INCLUDES_DIR)/message.hpp 
$(SOURCES_DIR)/consol_destination.o: $(INCLUDES_DIR)/consol_destination.hpp $(INCLUDES_DIR)/stream_destination.hpp
$(SOURCES_DIR)/udp_client.o: $(INCLUDES_DIR)/udp_client.hpp $(INCLUDES_DIR)/message_destination.hpp $(INCLUDES_DIR)/message.hpp
$(SOURCES_DIR)/file_destination.o: $(INCLUDES_DIR)/file_destination.hpp $(INCLUDES_DIR)/stream_destination.hpp
$(SOURCES_DIR)/stream_base.o: $(INCLUDES_DIR)/stream_base.hpp $(INCLUDES_DIR)/message_source.hpp $(INCLUDES_DIR)/message.hpp $(INCLUDES_DIR)/text_message.hpp
$(SOURCES_DIR)/stream_destination.o: $(INCLUDES_DIR)/stream_destination.hpp $(INCLUDES_DIR)/message_destination.hpp $(INCLUDES_DIR)/message.hpp
$(SOURCES_DIR)/consol_source.o: $(INCLUDES_DIR)/consol_source.hpp $(INCLUDES_DIR)/stream_base.hpp 
$(SOURCES_DIR)/file_source.o: $(INCLUDES_DIR)/file_source.hpp $(INCLUDES_DIR)/stream_base.hpp 
$(SOURCES_DIR)/precious_stone.o: $(INCLUDES_DIR)/precious_stone.hpp $(INCLUDES_DIR)/message_source.hpp\
								$(INCLUDES_DIR)/message_destination.hpp $(INCLUDES_DIR)/encoder.hpp $(INCLUDES_DIR)/text_message.hpp 
$(SOURCES_DIR)/utest.o: $(INCLUDES_DIR)/message.hpp $(INCLUDES_DIR)/substitution_encoder.hpp \
						$(INCLUDES_DIR)/scytale.hpp $(INCLUDES_DIR)/leetcode.hpp $(INCLUDES_DIR)/vowels.hp\
						$(INCLUDES_DIR)/uppercase.hpp $(INCLUDES_DIR)/caesar_encryption.hpp $(INCLUDES_DIR)/transposition_ciper.hpp\
						$(INCLUDES_DIR)/rot13.hpp $(INCLUDES_DIR)/udp_server.hpp

						