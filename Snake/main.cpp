#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h> // For clock_t and clock()
#include <conio.h>


#define SIZE 20
#define TICK_RATE 0.5

char*** board;

int snakeLength = 1;
int snakeDirection = 0;

// ���� ����, �� �� �� ��
int dx[] = {0, 0, -1, 1};
int dy[] = {-1, 1, 0, 0};

// Define a structure to represent the snake
typedef struct {
	int x;
	int y;
} SnakeBody;

SnakeBody snake[SIZE * SIZE];

// ���

// BOARD�� ��� �� ĭ���� �ʱ�ȭ�ϴ� �Լ�
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

// ���� �� ��ġ ����
void initializeSnake(int size) {
	snake[0].x = 10;
	snake[0].y = 10;
}

/**
* void moveSnake()
* ���� ��ġ�� ����, ���� �Ӹ��� ���� ��ġ�� �̵�
* ������ ���� ������ ��ȸ�ϸ� ���� ��ġ�� ������Ʈ
*/
void moveSnake() {
	int ny = snake[0].y + dy[snakeDirection];
	int nx = snake[0].x + dx[snakeDirection];

	if (ny >= SIZE || nx >= SIZE || ny < 0 || nx < 0) return;

	// ���� ��ġ ����
	int by = -1, bx = -1;
	for (int i = 0; i < snakeLength; i++) {
		by = snake[0].y;
		bx = snake[0].x;

		snake[0].y = ny;
		snake[0].x = nx;

		ny = by;
		nx = nx;
	}
}

// ���� �����ӿ� ���� ȭ�� ������Ʈ
void updateBoard() {
	/*
	�����ؾ� ��. �޸𸮸� ���ϰ� ����ϱ� ����
	*/
	initializeBoard(SIZE);

	for (int i = 0; i < snakeLength; i++) {
		int y = snake[i].y;
		int x = snake[i].x;

		strcpy(board[y][x], "��");
	}
}

// ȭ�� ���
void printBoard(int size) {
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			printf("%s", board[i][j]);
		}
		printf("\n");
	}
}


int main() {
	int size = 20;
	const char *whiteSquare = "��sdf";
	const char *blackSquare = "��";

	initializeBoard(size);
	initializeSnake(size);

	clock_t lastUpdateTime = clock(); // Get initial time

	while (true) {
		clock_t currentTime = clock(); // Get current time
		double elapsedTime = (double)(currentTime - lastUpdateTime) / CLOCKS_PER_SEC;


		if (_kbhit()) {
			//72 80 75 77
			int key_code = _getch();
			if (key_code == 224) {
				key_code = _getch();
				if (key_code == 72) snakeDirection = 0;
				else if (key_code == 80) snakeDirection = 1;
				else if (key_code == 75) snakeDirection = 2;
				else snakeDirection = 3;
			}
		}

		if (elapsedTime >= TICK_RATE) {
			system("cls"); // Clear the console (UNIX-based systems)

			moveSnake();
			updateBoard();
			printBoard(size);

			lastUpdateTime = currentTime; // Update last update time
		}
	}
}