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

// 뱀의 방향, 상 하 좌 우
int dx[] = {0, 0, -1, 1};
int dy[] = {-1, 1, 0, 0};

// Define a structure to represent the snake
typedef struct {
	int x;
	int y;
} SnakeBody;

SnakeBody snake[SIZE * SIZE];

// □■

// BOARD를 모두 빈 칸으로 초기화하는 함수
void initializeBoard(int size) {
	board = (char***)malloc(size * sizeof(char**));
	for (int i = 0; i < size; i++) {
		board[i] = (char**)malloc(size * sizeof(char*));
		for (int j = 0; j < size; j++) {
			board[i][j] = (char*)malloc(sizeof("□"));
			strcpy(board[i][j], "□");
		}
	}
}

// 최초 뱀 위치 설정
void initializeSnake(int size) {
	snake[0].x = 10;
	snake[0].y = 10;
}

/**
* void moveSnake()
* 다음 위치를 저장, 뱀의 머리를 다음 위치로 이동
* 나머지 뱀의 몸통을 순회하며 이전 위치로 업데이트
*/
void moveSnake() {
	int ny = snake[0].y + dy[snakeDirection];
	int nx = snake[0].x + dx[snakeDirection];

	if (ny >= SIZE || nx >= SIZE || ny < 0 || nx < 0) return;

	// 이전 위치 저장
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

// 뱀이 움직임에 따른 화면 업데이트
void updateBoard() {
	/*
	삭제해야 함. 메모리를 과하게 사용하기 때문
	*/
	initializeBoard(SIZE);

	for (int i = 0; i < snakeLength; i++) {
		int y = snake[i].y;
		int x = snake[i].x;

		strcpy(board[y][x], "■");
	}
}

// 화면 출력
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
	const char *whiteSquare = "ㅁsdf";
	const char *blackSquare = "ㅁ";

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