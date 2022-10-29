OBJ_DIR = ./obj
SRC_DIR = .

# [SEARCH PATHS]
INC_SRCH_PATH ?= -I../../include
LIB_SRCH_PATH ?= -L../../libs

# [FLAGS]
LIBS   = -lvector
СXX    ?= g++
CFLAGS ?= -g -Wall

# [SERVICE]
DIR_GUARD ?= mkdir -p $(@D)

SRC		= $(shell find $(SOURCEDIR) -name '*.cpp')
PROG    = gui
OBJ		= $(SRC:%.cpp=$(OBJ_DIR)/%.o)

all: lib

# https://www.gnu.org/software/make/manual/make.html#Static-Pattern
$(OBJ): $(OBJ_DIR)/%.o: %.cpp
	mkdir -p $(OBJ_DIR)
	$(CXX) -c $(CFLAGS) $< -o $@ $(INC_SRCH_PATH)

lib: $(OBJ)
	mkdir -p $(LIB_SRCH_PATH:-L%=%)
	ar rvs $(LIB_SRCH_PATH:-L%=%)/lib$(PROG).a $(OBJ)

clean:
	rm -rf $(OBJ_DIR)/*.o $(LIB_SRCH_PATH:-L%=%)/lib$(PROG).a
