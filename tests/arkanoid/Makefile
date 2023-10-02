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

# flags for preprocessor
CPPFLAGS = -I$(INCLUDES_DIR)

LDLIBS = -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio

OBJECTS = demo.o $(SOURCES_DIR)/player.o $(SOURCES_DIR)/ball.o $(SOURCES_DIR)/bricks.o $(SOURCES_DIR)/paddle.o\
	 $(SOURCES_DIR)/collision_manager.o $(SOURCES_DIR)/ui.o $(SOURCES_DIR)/score_manager.o\
	 $(SOURCES_DIR)/window_topten.o $(SOURCES_DIR)/window_opening.o $(SOURCES_DIR)/level_base.o\
	 $(SOURCES_DIR)/music.o

OBJECTS_SCORE = utest.o $(SOURCES_DIR)/player.o $(SOURCES_DIR)/score_manager.o

TARGET = demo
TARGET_UTEST = utest

all: $(TARGET)

$(TARGET) : $(OBJECTS)
$(TARGET_UTEST) : $(OBJECTS_SCORE)

check : $(TARGET)
	@./$(TARGET) -v

check_utest : $(TARGET_UTEST)
	@./$(TARGET_UTEST) -v

recheck: clean check

valgrind: $(TARGET)
	valgrind --log-file=memleak.log --leak-check=full --track-origins=yes -s ./$<

clean:
	@$(RM) ./$(TARGET) ./$(OBJECTS)./$(TARGET_UTEST) $(OBJECTS_SCORE)

.PHONY: clean all

# dependencies
$(SOURCES_DIR)/player.o: $(INCLUDES_DIR)/player.hpp
$(SOURCES_DIR)/ball.o: $(INCLUDES_DIR)/ball.hpp $(INCLUDES_DIR)/paddle.hpp
$(SOURCES_DIR)/paddle.o: $(INCLUDES_DIR)/paddle.hpp
$(SOURCES_DIR)/bricks.o: $(INCLUDES_DIR)/bricks.hpp $(INCLUDES_DIR)/ui.hpp $(INCLUDES_DIR)/player.hpp\
			 $(INCLUDES_DIR)/paddle.hpp $(INCLUDES_DIR)/ball.hpp $(INCLUDES_DIR)/ui.hpp 
$(SOURCES_DIR)/ui.o: $(INCLUDES_DIR)/ui.hpp 
$(SOURCES_DIR)/window_topten.o: $(INCLUDES_DIR)/window_topten.hpp $(INCLUDES_DIR)/score_manager.hpp $(INCLUDES_DIR)/window_manager.hpp
$(SOURCES_DIR)/music.o: $(INCLUDES_DIR)/music.hpp
$(SOURCES_DIR)/window_opening.o: $(INCLUDES_DIR)/window_opening.hpp $(INCLUDES_DIR)/window_manager.hpp
$(SOURCES_DIR)/score_manager.o: $(INCLUDES_DIR)/score_manager.hpp $(INCLUDES_DIR)/player.hpp
$(SOURCES_DIR)/collision_manager.o: $(INCLUDES_DIR)/collision_manager.hpp $(INCLUDES_DIR)/player.hpp\
			 $(INCLUDES_DIR)/paddle.hpp $(INCLUDES_DIR)/ball.hpp $(INCLUDES_DIR)/bricks.hpp
$(SOURCES_DIR)/level_base.o: $(INCLUDES_DIR)/level_base.hpp $(INCLUDES_DIR)/bricks.hpp $(INCLUDES_DIR)/ball.hpp\
							$(INCLUDES_DIR)/player.hpp $(INCLUDES_DIR)/collision_manager.hpp $(INCLUDES_DIR)/ui.hpp\
							$(INCLUDES_DIR)/global_varibal.hpp $(INCLUDES_DIR)/music.hpp $(INCLUDES_DIR)/level_manager.hpp
demo.o: $(INCLUDES_DIR)/player.hpp $(INCLUDES_DIR)/window_topten.hpp\
			 $(INCLUDES_DIR)/window_opening.hpp $(INCLUDES_DIR)/level_base.hpp $(INCLUDES_DIR)/global_varibal.hpp

# dependencies
$(SOURCES_DIR)/score_manager.o: $(INCLUDES_DIR)/score_manager.hpp $(INCLUDES_DIR)/player.hpp
$(SOURCES_DIR)/player.o: $(INCLUDES_DIR)/player.hpp 
utest.o: $(INCLUDES_DIR)/player.hpp $(INCLUDES_DIR)/score_manager.hpp $(INCLUDES_DIR)/mu_test.h