spell: spell.c
	gcc -std=c99 -o spell spell.c dictionary.c spell_main.c

testfiles := $(shell ls testing/input/*)
test:
	@echo $(shell ls testing/input/*)
	$(foreach input, $(testfiles), ./spell $(input) ./testing/wordlist.txt;)
