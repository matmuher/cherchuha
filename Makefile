MAKE_DIR = $(PWD)

# [SEARCH PATHS]
INC_SRCH_PATH = -I$(MAKE_DIR)/include
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
RAYCAST_DIR := $(MAKE_DIR)/raycast
VECTOR_DIR 	:= $(MAKE_DIR)/vector
DRAWER_DIR 	:= $(MAKE_DIR)/drawer

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

raycast:
	@$(MAKE) -C $(VECTOR_DIR)/lib
	@$(MAKE) -C $(DRAWER_DIR)/lib
	@$(MAKE) -C $(RAYCAST_DIR)/example	

gui:
	@$(MAKE) -C $(VECTOR_DIR)/lib
	@$(MAKE) -C $(DRAWER_DIR)/lib
	@$(MAKE) -C $(GUI_DIR)/lib
	@$(MAKE) -C $(GUI_DIR)/example

drawer:
	@$(MAKE) -C $(DRAWER_DIR)/lib

vector:
	@$(MAKE) -C $(VECTOR_DIR)/lib
	@$(MAKE) -C $(DRAWER_DIR)/lib
	@$(MAKE) -C $(VECTOR_DIR)/example
