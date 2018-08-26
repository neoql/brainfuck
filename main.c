#include <stdio.h>
#include "brainfuck.h"

int main(int argc, const char* argv[]) {
	bf_State *env = bf_open();
	if (argc == 1) {
		bf_load(env, stdin);
	} else {
		bf_loadfile(env, argv[1]);
	}

	return bf_exec(env);
}