MAKE_DIR = $(PWD)

# [SEARCH PATHS]
INC_SRCH_PATH ?=
LIB_SRCH_PATH = -L$(MAKE_DIR)/libs

# [FLAGS]
LIBS = -lsfml-graphics -lsfml-window -lsfml-system
СXX    = g++
CFLAGS = -g -Wall

# [SERVICE]
DIR_GUARD = mkdir -p $(@D)

# [MODULES]
# difference ':=' and '='
# https://stackoverflow.com/questions/4879592/whats-the-difference-between-and-in-makefile
GUI_DIR 	:= $(MAKE_DIR)/gui
INC_SRCH_PATH += -I$(GUI_DIR)/include

RAYCAST_DIR := $(MAKE_DIR)/raycast
INC_SRCH_PATH += -I$(RAYCAST_DIR)/include

VECTOR_DIR 	:= $(MAKE_DIR)/vector
INC_SRCH_PATH += -I$(VECTOR_DIR)/include

DRAWER_DIR 	:= $(MAKE_DIR)/drawer
INC_SRCH_PATH += -I$(DRAWER_DIR)/include

export CFLAGS CXX LIBS INC_SRCH_PATH LIB_SRCH_PATH DIR_GUARD

# f.ex to do clean even if file with name 'clean' exists
.PHONY: clean lib rebuild

all: build

build:
	$(MAKE) -C $(VECTOR_DIR)
	$(MAKE) -C $(GUI_DIR)
	$(MAKE) -C $(RAYCAST_DIR)

clean:
	@$(MAKE) -C $(VECTOR_DIR) $@
	@$(MAKE) -C $(GUI_DIR) $@
	@$(MAKE) -C $(RAYCAST_DIR) $@

lib:
	@$(MAKE) -C $(RAYCAST_DIR) $@
	@$(MAKE) -C $(GUI_DIR) $@
	@$(MAKE) -C $(VECTOR_DIR) $@

.PHONY: vector gui drawer raycast clean

vector_lib:
	@$(MAKE) -C $(VECTOR_DIR)/lib

gui_lib:
	@$(MAKE) -C $(GUI_DIR)/lib
	
drawer_lib:
	@$(MAKE) -C $(DRAWER_DIR)/lib

raycast: vector_lib gui_lib drawer_lib
	@$(MAKE) -C $(RAYCAST_DIR)/example	

gui: vector_lib gui_lib drawer_lib
	@$(MAKE) -C $(GUI_DIR)/example

vector: vector_lib
	@$(MAKE) -C $(VECTOR_DIR)/example

drawer_clean:
	@$(MAKE) -C $(DRAWER_DIR)/lib clean

vector_clean:
	@$(MAKE) -C $(VECTOR_DIR)/lib clean
	@$(MAKE) -C $(VECTOR_DIR)/example clean

gui_clean:
	@$(MAKE) -C $(GUI_DIR)/lib clean
	@$(MAKE) -C $(GUI_DIR)/example clean

raycast_clean:
	@$(MAKE) -C $(RAYCAST_DIR)/example clean

clean: drawer_clean vector_clean gui_clean raycast_clean
	@echo "Clean performed"