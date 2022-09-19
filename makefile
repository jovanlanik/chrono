# Chronograph
# Copyright (c) 2022 Jovan Lanik

# Makefile

NAME := chrono

CFLAGS += -std=c11

SRC = $(wildcard *.c)
OBJ = $(SRC:%.c=%.o)

TRASH = $(OBJ) $(NAME)

.PHONY: all clean install uninstall

all: $(NAME)

clean:
	@rm $(TRASH) | true

$(NAME): $(OBJ)
	$(LINK.c) $^ $(LDLIBS) -o $@
