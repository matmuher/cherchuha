OBJ_DIR = ./obj
SRC_DIR = .

SRC		= $(shell find $(SRC_DIR) -name '*.cpp')
PROG    = gui
LIBS 	:= -lvector $(LIBS)
OBJ		= $(SRC:%.cpp=$(OBJ_DIR)/%.o)

all: $(PROG)
	
$(PROG): $(OBJ)
	$(CXX) $(OBJ) -o $@ $(LIB_SRCH_PATH) $(LIBS) 

# https://www.gnu.org/software/make/manual/make.html#Static-Pattern
$(OBJ): $(OBJ_DIR)/%.o: %.cpp
	$(DIR_GUARD)
	$(CXX) -c $(CFLAGS) $< -o $@ $(INC_SRCH_PATH)

lib: $(OBJ)
	mkdir -p $(LIB_SRCH_PATH:-L%=%)
	ar rvs $(LIB_SRCH_PATH:-L%=%)/lib$(PROG).a $(OBJ)
	ar dv  $(LIB_SRCH_PATH:-L%=%)/lib$(PROG).a main.o

clean:
	rm -rf $(OBJ_DIR)/*.o $(PROG)
