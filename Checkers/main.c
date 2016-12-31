#include "main.h"
#include <minix/sysutil.h>
#include <minix/syslib.h>
#include <minix/drivers.h>
#include "main.h"
#include "video_gr.h"
#include <assert.h>
#include "keyboard.h"
#include <stdio.h>
#include "board.h"
#include "video_gr.h"
#include "checker.h"
#include "i8254.h"
#include "timer.h"
#include "mouse.h"
#include "numberxpm.h"
#include "graphic.h"
#include "rtc.h"


/** @defgroup main main
 * @{
 * Functions for main
 */
int main(int argc, char** argv) {
	int board[6][6]; //simulacao do board, com arrays
	int i, j;

	for (i = 0; i < 6; i++)
		for (j = 0; j < 6; j++)
			board[i][j] = 0;

	for (i = 0; i < 3; i++) {
		board[0][2 * i] = 1;//colocacao das pecas vermelhas
	}

	for (i = 0; i < 3; i++) {
		board[5][2 * i + 1] = 2;//colocacao das pecas verdes
	}

	sef_startup();
	char* video_mem = vg_init(MODE_800x600);
	newMouse();
	drawBoard(0, 63,getBuffer2());
	flipScreen2();
	drawCheckers(board,getVideoMem());

	Timer* t = newTimer();
	int ipc_status;
	message msg;
	int receive;
	int r;
	int counter = 0;
	unsigned long scan_code;
	int validation = 0;
	int irq_timer = timer_subscribe_int();
	int irq_mouse = mouse_subscribe_int();
	int irq_kbd = keyboard_subscribe_int();
	int irq_rtc = rtc_subscribe();

	rtc_time_t date;

	int xChecker;
	int yChecker;
	int highlighted = 0;
	int player1Checkers = 3;
	int player2Checkers = 3;
	int player = 1;

	while (validation != 1) {
		receive = driver_receive(ANY, &msg, &ipc_status);
		if (receive != 0) {
			printf("driver_receive failed with: %d", receive);
			continue;
		}

		if (is_ipc_notify(ipc_status)) {
			switch (_ENDPOINT_P(msg.m_source)) {
			case HARDWARE:
				if (msg.NOTIFY_ARG & irq_timer) {
					timer_handler(t);
					date = rtc_read_date();
					flipScreen2();
					drawCheckers(board, getVideoMem());

					if (highlighted)
						highlightChecker(xChecker, yChecker, getVideoMem());
				    drawMouse();
					drawCounter(10*60 - counter);
					drawplayer(player);
					drawDate(date);
					drawnrcheckersplayer1 (player1Checkers);
					drawnrcheckersplayer2 (player2Checkers);
					counter++;
					if (counter >= 10 * 60) {
						counter = 0;
						player = (player % 2) + 1;
						highlighted = 0;
					}
				}
				if (msg.NOTIFY_ARG & irq_mouse) {
					handle_mouse();
						if (clickedMouse() && !highlighted) {
							Mouse* m = getMouse();
							xChecker = m->x / 100;
							yChecker = m->y / 100;

							if (player == 1) {
								if (board[yChecker][xChecker] == 1
										|| board[yChecker][xChecker] == 3) //verifica se a dama que se quer selecionar com o rato e do player1
								{
									highlighted = 1;
								}
							} else if (player == 2) {
								if (board[yChecker][xChecker] == 2
										|| board[yChecker][xChecker] == 4) {
									highlighted = 1;
								}
							}
					}
				}
				if (msg.NOTIFY_ARG & irq_kbd) {
					scan_code = keyboard_get_resp();
					if (scan_code != -1) {
						if (highlighted) {
							int Flag = moveChecker(board, xChecker, yChecker,
									scan_code);

							if (Flag != -1) {
								counter = 0;
								highlighted = 0;
								if (Flag == 1)
									player1Checkers--;
								else if (Flag == 2)
									player2Checkers--;

								if (player1Checkers == 0
										|| player2Checkers == 0)
								{
									validation = 1;
								}
								player = (player % 2) + 1; //troca de jogadores
							}

						}
						else if (scan_code == KEY_UP(ESC))
								validation = 1;

					}
				}

				break;
			default:
				break;
			}
		}
	}

	keyboard_unsubscribe_int();
	timer_unsubscribe_int();
	mouse_unsubscribe_int();
	rtc_unsubscribe();
	deleteMouse();
	deleteTimer(t);


	if (player1Checkers == 0 || player2Checkers == 0) {
		cleanScreen();
		winnerPlayer(player1Checkers);
		sleep(2);
	}

	vg_exit();
	return 0;
}


