#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char*** board;

// ���

void initializeBoard(int size) {
	board = (char***)malloc(size * sizeof(char**));
	for (int i = 0; i < size; i++) {
		board[i] = (char**)malloc(size * sizeof(char*));
		for (int j = 0; j < size; j++) {
			board[i][j] = (char*)malloc(sizeof("��"));
			strcpy(board[i][j], "��");
		}
	}
}

int main() {
	int size = 20;
	const char *whiteSquare = "��sdf";
	const char *blackSquare = "��";

	initializeBoard(size);
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			printf("%s", board[i][j]);
		}
		printf("\n");
	}
}