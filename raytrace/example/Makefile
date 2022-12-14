OBJ_DIR = ./obj
SRC_DIR = .

# [SEARCH PATHS]
INC_SRCH_PATH ?= -I../../gui/include -I../../drawer/include -I../../vector/include
LIB_SRCH_PATH ?= -L../../libs

# [FLAGS]
LIBS   = -ldrawer -lgui -lvector -lsfml-graphics -lsfml-window -lsfml-system
СXX    ?= g++
CFLAGS ?= -g -Wall -fsanitize=address -fopenmp
CXXFLAGS ?= -g -Wall -fsanitize=address -fopenmp
LDFLAGS  ?= -Wall -fsanitize=address -no-pie -ggdb3 -fopenmp

# [SERVICE]
DIR_GUARD ?= mkdir -p $(@D)

SRC		= $(shell find $(SOURCEDIR) -name '*.cpp')
PROG    = raytrace
OBJ		= $(SRC:%.cpp=$(OBJ_DIR)/%.o)

all: clean $(PROG)
	
$(PROG): $(OBJ)
	$(CXX) $(LDFLAGS) $(OBJ) -o $@.exe $(LIB_SRCH_PATH) $(LIBS) 

# https://www.gnu.org/software/make/manual/make.html#Static-Pattern
$(OBJ): $(OBJ_DIR)/%.o: %.cpp
	mkdir -p $(OBJ_DIR)
	$(CXX) -c $(CFLAGS) $< -o $@ $(INC_SRCH_PATH)

valgrind:
	valgrind --leak-check=full \
			--show-leak-kinds=all \
			--track-origins=yes \
			--verbose \
			--log-file=valgrind-out.txt \
         	./$(PROG).exe 

clean:
	rm -rf $(OBJ_DIR)/*.o $(PROG).exe
