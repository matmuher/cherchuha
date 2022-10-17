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
GUI_DIR 	:= $(MAKE_DIR)/GUI
RAYCAST_DIR := $(MAKE_DIR)/raycast
VECTOR_DIR 	:= $(MAKE_DIR)/vector

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
