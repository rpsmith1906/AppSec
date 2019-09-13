spell: spell.c
	gcc -std=c99 -o spell spell.c dictionary.c spell_main.c -I. `pkg-config --cflags --libs check`

test:
	@echo $(shell ls testing/*)
