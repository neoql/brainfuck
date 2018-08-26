//
// Created by neoql on 18-8-26.
//

#include "brainfuck.h"

#include <stdlib.h>
#include <stdio.h>

static struct Node {
	char val;
	struct Node *prev;
	struct Node *next;
};

typedef struct Node Node;

static Node * newNode(char val, Node *prev) {
	Node *node = malloc(sizeof(Node));
	node->next = NULL;
	node->prev = prev;
	node->val = val;
	return node;
}

static void delList(Node *head) {
	while (head != NULL) {
		head = head->next;
		free(head);
	}
}

struct bf_State {
	Node* code;
};

bf_State *bf_open() {
	bf_State *BF;
	BF = malloc(sizeof(bf_State));
	BF->code = newNode(0, NULL);
	return BF;
}

void bf_close(bf_State *BF) {
	delList(BF->code);
	free(BF);
}

int bf_load(bf_State *BF, FILE *f) {
	char symbol;
	Node *node = BF->code;
	delList(node->next);
	node->next = NULL;
	while (!feof(f)) {
		symbol = (char)fgetc(f);
		switch (symbol) {
			case '>':
			case '<':
			case '+':
			case '-':
			case '.':
			case ',':
			case '[':
			case ']':
				node->next = newNode(symbol, node);
				node = node->next;
				break;
			default:
				return -1;
		}

	}
	return 0;
}

int bf_loadfile(bf_State *BF, const char *path) {
	int code = 0;
	FILE *file = fopen(path, "r");
	code = bf_load(BF, file);
	if (code) {
		return code;
	}
	fclose(file);
	return 0;
}

int bf_execx(bf_State *BF, FILE *in, FILE *out) {
	Node *head = BF->code;
	Node *data = newNode(0, NULL);
	int count;

	for (Node *cur = head->next; cur != NULL; cur = cur->next) {
		switch (cur->val) {
			case '>':
				if (data->next == NULL) {
					data->next = newNode(0, data);
				}
				data = data->next;
				break;
			case '<':
				if (data->prev == NULL) {
					return -1;
				}
				data = data->prev;
				break;
			case '+':
				data->val++;
				break;
			case '-':
				data->val--;
				break;
			case '.':
				fputc(data->val, out);
				break;
			case ',':
				data->val = (char)fgetc(in);
				break;
			case '[':
				if (data->val == 0) {
					count = 1;
					for (cur = cur->next; cur != NULL && count != 0; cur = cur->next) {
						switch (cur->val) {
							case '[':
								count++;
								break;
							case ']':
								count--;
								break;
							default:
								break;
						}
					}
					if (count != 0 || cur == NULL) {
						return -1;
					}
					cur = cur->prev;
				}
				break;
			case ']':
				if (data->val != 0) {
					count = -1;
					for (; cur->prev != NULL && count != 0; cur = cur->prev) {
						switch (cur->prev->val) {
							case '[':
								count++;
								break;
							case ']':
								count--;
								break;
							default:
								break;
						}
					}
					if (count != 0) {
						return -1;
					}
				}
				break;
			default:
				return -1;
		}
	}
	return 0;
}

int bf_exec(bf_State *BF) {
	return bf_execx(BF, stdin, stdout);
}
