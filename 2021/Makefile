DAYS := 01 02 03 04 05 06 07 08 09 10 11 12 13 14 15 16 17 18 19 20 21 22 23 24 25
.DEFAULT_GOAL := help
.PHONY: $(DAYS) all help clean

CC := gcc
CFLAGS := -Wall -Wextra -O2 -std=c99 -g -fsanitize=address

inputs/%.in:
	../fetch.sh 2021 $*

bin/main: src/*.c | bin
	$(CC) $(CFLAGS) -o $@ src/*.c

bin:
	mkdir -p bin

$(DAYS): %: inputs/%.in bin/main
	./bin/main $* input

all: $(patsubst %,inputs/%.in,$(DAYS)) bin/main
	./bin/main all input

clean:
	rm -rf bin/

help:
	@$(MAKE) --no-print-directory -C .. help
