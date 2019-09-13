spell: spell.c
	gcc -std=c99 -o spell spell.c dictionary.c spell_main.c -I. `pkg-config --cflags --libs check`

testfiles := $(shell ls testing/*)
test:
	@echo $(shell ls testing/*)
	$(foreach input, $(testfiles), ./spell $(input) ./wordlist.txt;)
