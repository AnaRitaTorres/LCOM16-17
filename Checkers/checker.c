#include <minix/syslib.h>
#include <minix/drivers.h>
#include <machine/int86.h>
#include <sys/mman.h>
#include <sys/types.h>

#include "checker.h"
#include "keyboard.h"
#include "video_gr.h"
#include "board.h"

Checker* createChecker(int x, int y, int color)
{
	Checker* c = (Checker*)malloc(sizeof(Checker));
	c->x = x;
	c->y = y;
	c->color = color;
	return c;
}

void drawCheckers(int board[][6], char* buf) {
	int i, j;
	for (i = 0; i < 6; i++) {
		for (j = 0; j < 6; j++) {
			if (board[i][j] == 1)
				draw_circle(100 * j + 50, 100 * i + 50, 40, 4, buf);
			else if (board[i][j] == 2)
				draw_circle(100 * j + 50, 100 * i + 50, 40, 2,buf);
			else if (board[i][j] == 3)
				draw_circle(100 * j + 50, 100 * i + 50, 40, 5,buf);
			else if (board[i][j] == 4)
				draw_circle(100 * j + 50, 100 * i + 50, 40, 10,buf);
		}
	}
}

void deleteChecker(Checker* c)
{
	free(c);
}

void setCheckerLocation(Checker* c, int x, int y) {
	c->x = x;
	c->y = y;
}



int moveChecker(int board[][6], int x, int y, unsigned long scancode) {
	int playerFlag = board[y][x];
	switch (scancode) {
	case KEY_DOWN(KEY_A):
		if (playerFlag == 2)
			return -1;

		if (y < 5 && x > 0) {
			if (board[y + 1][x - 1] == 0) {
				board[y][x] = 0;

				if (y + 1 == 5 && playerFlag == 1)
					board[y + 1][x - 1] = 3;
				else
					board[y + 1][x - 1] = playerFlag;
				return 0;
			} else if (board[y + 1][x - 1] != playerFlag) {
				if (x - 2 >= 0 && y + 2 <= 5 && board[y + 2][x - 2] == 0) {
					board[y][x] = 0;
					board[y + 1][x - 1] = 0;
					if (y + 2 == 5 && playerFlag == 1)
						board[y + 2][x - 2] = 3;
					else
						board[y + 2][x - 2] = playerFlag;
					return (playerFlag % 2) + 1;
				}
			}
		}
		break;
	case KEY_DOWN(KEY_D):
		if (playerFlag == 2)
			return -1;
		if (y < 5 && x < 5) {
			if (board[y + 1][x + 1] == 0) {
				board[y][x] = 0;
				if (y + 1 == 5 && playerFlag == 1)
					board[y + 1][x + 1] = 3;
				else
					board[y + 1][x + 1] = playerFlag;
				return 0;
			} else if (board[y + 1][x + 1] != playerFlag) {
				if (x + 2 <= 5 && y + 2 <= 5 && board[y + 2][x + 2] == 0) {
					board[y][x] = 0;
					board[y + 1][x + 1] = 0;
					if (y + 2 == 5 && playerFlag == 1)
						board[y + 2][x + 2] = 3;
					else
						board[y + 2][x + 2] = playerFlag;
					return (playerFlag % 2) + 1;
				}
			}
		}
		break;
	case KEY_DOWN(KEY_Q):
		if (playerFlag == 1)
			return -1;

		if (y > 0 && x > 0) {
			if (board[y - 1][x - 1] == 0) {
				board[y][x] = 0;
				if (y - 1 == 0 && playerFlag == 2)
					board[y - 1][x - 1] = 4;
				else
					board[y - 1][x - 1] = playerFlag;
				return 0;
			} else if (board[y - 1][x - 1] != playerFlag) {
				if (x - 2 >= 0 && y - 2 >= 0 && board[y - 2][x - 2] == 0) {
					board[y][x] = 0;
					board[y - 1][x - 1] = 0;

					if (y - 2 == 0 && playerFlag == 2)
						board[y - 2][x - 2] = 4;
					else
						board[y - 2][x - 2] = playerFlag;
					return (playerFlag % 2) + 1;
				}
			}
		}
		break;

	case KEY_DOWN(KEY_E):
		if (playerFlag == 1)
			return -1;

		if (y > 0 && x < 5) {
			if (board[y - 1][x + 1] == 0) {
				board[y][x] = 0;
				if (y - 1 == 0 && playerFlag == 2)
					board[y - 1][x + 1] = 4;
				else
					board[y - 1][x + 1] = playerFlag;
				return 0;
			} else if (board[y - 1][x + 1] != playerFlag) {
				if (x + 2 >= 0 && y - 2 >= 0 && board[y - 2][x + 2] == 0) {
					board[y][x] = 0;
					board[y - 1][x + 1] = 0;
					if (y - 2 == 0 && playerFlag == 2)
						board[y - 2][x + 2] = 4;
					else
						board[y - 2][x + 2] = playerFlag;
					return (playerFlag % 2) + 1;
				}
			}
		}
		break;
	}
	return -1;
}




void highlightChecker(int xChecker, int yChecker, char* buf) {
	draw_circle(100*xChecker + 50, 100*yChecker + 50, 40, 3, buf);
}

