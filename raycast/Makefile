INC_DIR = ../include
SRC_DIR =
OBJ_DIR = ./obj
LIB_DIR = ../libs

SRC		= main.cpp
EXEC 	= raycaster.exe
LIBS 	= -lvector -lsfml-graphics -lsfml-window -lsfml-system
OBJ		= $(SRC:%.cpp=$(OBJ_DIR)/%.o)

СXX = g++
CFLAGS  = -D _DEBUG -ggdb3 -std=c++17 -O0 -Wall -Wextra -Weffc++ -Waggressive-loop-optimizations -Wc++14-compat -Wmissing-declarations -Wcast-align -Wcast-qual -Wchar-subscripts -Wconditionally-supported -Wconversion -Wctor-dtor-privacy -Wempty-body -Wfloat-equal -Wformat-nonliteral -Wformat-security -Wformat-signedness -Wformat=2 -Winline -Wlogical-op -Wnon-virtual-dtor -Wopenmp-simd -Woverloaded-virtual -Wpacked -Wpointer-arith -Winit-self -Wredundant-decls -Wshadow -Wsign-conversion -Wsign-promo -Wstrict-null-sentinel -Wstrict-overflow=2 -Wsuggest-attribute=noreturn -Wsuggest-final-methods -Wsuggest-final-types -Wsuggest-override -Wswitch-default -Wswitch-enum -Wsync-nand -Wundef -Wunreachable-code -Wunused -Wuseless-cast -Wvariadic-macros -Wno-literal-suffix -Wno-missing-field-initializers -Wno-narrowing -Wno-old-style-cast -Wno-varargs -Wstack-protector -fcheck-new -fsized-deallocation -fstack-check -fstack-protector -fstrict-overflow -flto-odr-type-merging -fno-omit-frame-pointer -Wlarger-than=8192 -Wstack-usage=8192 -pie -fPIE -fsanitize=address,alignment,bool,bounds,enum,float-cast-overflow,float-divide-by-zero,integer-divide-by-zero,nonnull-attribute,leak,null,object-size,return,returns-nonnull-attribute,shift,signed-integer-overflow,undefined,unreachable,vla-bound,vptr
LDFLAGS =

DIR_GUARD=mkdir -p $(@D)

all: $(EXEC)
	
$(EXEC): $(OBJ)
	$(CXX) $(OBJ) -o $@  -L$(LIB_DIR) $(LIBS) 

# https://www.gnu.org/software/make/manual/make.html#Static-Pattern
$(OBJ): $(OBJ_DIR)/%.o: %.cpp
	$(DIR_GUARD)
	$(CXX) -c $< -o $@ -I $(INC_DIR)

lib: $(OBJ)
	mkdir -p $(LIB_DIR))
	ar rvs $(LIB_DIR)/libraycast.a $(OBJ)
	ar dv $(LIB_DIR)/libraycast.a main.o

clean:
	clear
	rm -rf $(OBJ_DIR)/*.o *.exe