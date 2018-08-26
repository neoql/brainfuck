//
// Created by neoql on 18-8-26.
//

#ifndef BRAINFUCK_BRAINFUCK_H
#define BRAINFUCK_BRAINFUCK_H

#include <bits/types/FILE.h>

typedef struct bf_State bf_State;

bf_State *bf_open();
void bf_close(bf_State *BF);

int bf_load(bf_State *BF, FILE *f);
int bf_loadfile(bf_State *BF, const char *path);

int bf_exec(bf_State *BF);
int bf_execx(bf_State *BF, FILE *in, FILE *out);

#endif //BRAINFUCK_BRAINFUCK_H
