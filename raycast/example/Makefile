OBJ_DIR = ./obj
SRC_DIR = .

# [SEARCH PATHS]
INC_SRCH_PATH ?= -I../../include
LIB_SRCH_PATH ?= -L../../libs

# [FLAGS]
LIBS   = -ldrawer -lgui -lvector -lsfml-graphics -lsfml-window -lsfml-system
СXX    ?= g++
CFLAGS ?= -g -Wall

# [SERVICE]
DIR_GUARD ?= mkdir -p $(@D)

SRC		= $(shell find $(SOURCEDIR) -name '*.cpp')
PROG    = raycast
OBJ		= $(SRC:%.cpp=$(OBJ_DIR)/%.o)

all: clean $(PROG)
	
$(PROG): $(OBJ)
	$(CXX) $(OBJ) -o $@.exe $(LIB_SRCH_PATH) $(LIBS) 

# https://www.gnu.org/software/make/manual/make.html#Static-Pattern
$(OBJ): $(OBJ_DIR)/%.o: %.cpp
	mkdir -p $(OBJ_DIR)
	$(CXX) -c $(CFLAGS) $< -o $@ $(INC_SRCH_PATH)

clean:
	rm -rf $(OBJ_DIR)/*.o $(PROG).exe
