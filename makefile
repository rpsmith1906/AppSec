spell: spell.c
	gcc -std=c99 -o spell spell.c dictionary.c my_test_main.c -I. `pkg-config --cflags --libs check`
