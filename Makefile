path_f = ~/.local/bin
SRC = src
BIN = bin
programs_src = $(shell ls $(SRC) | grep .c)
programs = $(foreach prog,$(programs_src),$(shell echo $(prog) | cut -d '.' -f 1))
CFLAGS = -Wall -Wextra -Werror -pedantic -O2

def:
	@echo "Install any of these programs with \"make [PROGRAM]\" command!"
	@echo "Programs:"
	@echo $(programs)
	@echo "Or just type \"make all\" or \"make install\""

all: $(programs)
	@

install: all
	@

uninstall:
	rm $(foreach prog,$(programs),$(path_f)/$(prog))

$(BIN):
	mkdir $(BIN)

$(BIN)/% : $(SRC)/%.c
	gcc -o $@ $< $(CFLAGS)

compile-all: $(BIN) $(programs:%=$(BIN)/%)
	@

clean: $(BIN)
	rm $(BIN)/*

$(path_f):
	@echo "Seems like you don't have $(path_f) folder!"
	mkdir -p $(path_f)

$(programs): $(path_f)
	gcc $(SRC)/$@.c -o $(path_f)/$@ $(CFLAGS)

.PHONY: compile-all install uninstall all clean def
