#include "board.h"
#include "video_gr.h"
#include "rectangle.h"
#include "numberxpm.h"
#include "sprite.h"
#include "letterxpm.h"
#include "video_gr.h"
#include "rtc.h"

void drawnrcheckersplayer1 (int playercheckers1)
{
	Sprite *sp;
	Sprite *checkers;
	sp = create_sprite(player1, 650, 100,0,0);
	switch(playercheckers1)
	{
	case 3:
		checkers = create_sprite(num3, 690, 120,0,0);
		break;
	case 2:
		checkers = create_sprite(num2, 690, 120,0,0);
		break;
	case 1:
		checkers = create_sprite(num1, 690, 120,0,0);
		break;
	case 0:
		checkers = create_sprite(num0, 690, 120,0,0);
		break;
	}


	draw_xpm(sp);
	draw_xpm(checkers);

	destroy_sprite(sp);
	destroy_sprite(checkers);
}
void drawnrcheckersplayer2 (int playercheckers2)
{
	Sprite *sp;
	Sprite *checkers;
	sp = create_sprite(player2, 650, 300,0,0);
	switch (playercheckers2) {
	case 3:
		checkers = create_sprite(num3, 690, 320,0,0);
		break;
	case 2:
		checkers = create_sprite(num2, 690, 320,0,0);
		break;
	case 1:
		checkers = create_sprite(num1, 690, 320,0,0);
		break;
	case 0:
		checkers = create_sprite(num0, 690, 320,0,0);
		break;
	}
	draw_xpm(sp);
	draw_xpm(checkers);
	destroy_sprite(sp);
	destroy_sprite(checkers);
}
void winnerPlayer(int playercheckers1)
{
	Sprite *sp;
	Sprite *player;
	sp = create_sprite(winner,200,100,0,0);
	if(playercheckers1 == 0)
	{
		player = create_sprite(num2color, 380, 100,0,0);
		draw_xpm(sp);
		draw_xpm(player);
	}
	else
	{
		player = create_sprite(num1color, 380, 100,0,0);
		draw_xpm(sp);
		draw_xpm(player);
	}

	destroy_sprite(sp);
	destroy_sprite(player);
}
void drawplayer(int player)
{
	Sprite *p;
	switch(player)
	{
	case 1:
		p = create_sprite(player1, 610, 10,0,0);
		break;
	case 2:
		p = create_sprite(player2, 610, 10,0,0);
		break;
	}
	draw_xpm(p);
	destroy_sprite(p);
}

void drawDate(rtc_time_t t)
{
	Sprite *day1;
	Sprite *day2;

	switch(t.day)
	{
	case 1:
		day1 = create_sprite(num0, 605, 400,0,0);
		day2 = create_sprite(num1, 630, 400,0,0);
		break;
	case 2:
		day1 = create_sprite(num0, 605, 400,0,0);
		day2 = create_sprite(num2, 630, 400,0,0);
		break;
	case 3:
		day1 = create_sprite(num0, 605, 400,0,0);
		day2 = create_sprite(num3, 630, 400,0,0);
		break;
	case 4:
		day1 = create_sprite(num0, 605, 400,0,0);
		day2 = create_sprite(num4, 630, 400,0,0);
		break;
	case 5:
		day1 = create_sprite(num0, 605, 400,0,0);
		day2 = create_sprite(num5, 630, 400,0,0);
		break;
	case 6:
		day1 = create_sprite(num0, 605, 400,0,0);
		day2 = create_sprite(num6, 630, 400,0,0);
		break;
	case 7:
		day1 = create_sprite(num0, 605, 400,0,0);
		day2 = create_sprite(num7, 630, 400,0,0);
		break;
	case 8:
		day1 = create_sprite(num0, 605, 400,0,0);
		day2 = create_sprite(num8, 630, 400,0,0);
		break;
	case 9:
		day1 = create_sprite(num0, 605, 400,0,0);
		day2 = create_sprite(num9, 630, 400,0,0);
		break;
	case 10:
		day1 = create_sprite(num1, 605, 400,0,0);
		day2 = create_sprite(num0, 630, 400,0,0);
		break;
	case 11:
		day1 = create_sprite(num1, 605, 400,0,0);
		day2 = create_sprite(num1, 630, 400,0,0);
		break;
	case 12:
		day1 = create_sprite(num1, 605, 400,0,0);
		day2 = create_sprite(num2, 630, 400,0,0);
		break;
	case 13:
		day1 = create_sprite(num1, 605, 400,0,0);
		day2 = create_sprite(num3, 630, 400,0,0);
		break;
	case 14:
		day1 = create_sprite(num1, 605, 400,0,0);
		day2 = create_sprite(num4, 630, 400,0,0);
		break;
	case 15:
		day1 = create_sprite(num1, 605, 400,0,0);
		day2 = create_sprite(num5, 630, 400,0,0);
		break;
	case 16:
		day1 = create_sprite(num1, 605, 400,0,0);
		day2 = create_sprite(num6, 630, 400,0,0);
		break;
	case 17:
		day1 = create_sprite(num1, 605, 400,0,0);
		day2 = create_sprite(num7, 630, 400,0,0);
		break;
	case 18:
		day1 = create_sprite(num1, 605, 400,0,0);
		day2 = create_sprite(num8, 630, 400,0,0);
		break;
	case 19:
		day1 = create_sprite(num1, 605, 400,0,0);
		day2 = create_sprite(num9, 630, 400,0,0);
		break;
	case 20:
		day1 = create_sprite(num2, 605, 400,0,0);
		day2 = create_sprite(num0, 630, 400,0,0);
		break;

	case 21:
		day1 = create_sprite(num2, 605, 400,0,0);
		day2 = create_sprite(num1, 630, 400,0,0);
		break;
	case 22:
		day1 = create_sprite(num2, 605, 400,0,0);
		day2 = create_sprite(num2, 630, 400,0,0);
		break;
	case 23:
		day1 = create_sprite(num2, 605, 400,0,0);
		day2 = create_sprite(num3, 630, 400,0,0);
		break;
	case 24:
		day1 = create_sprite(num2, 605, 400,0,0);
		day2 = create_sprite(num4, 630, 400,0,0);
		break;
	case 25:
		day1 = create_sprite(num2, 605, 400,0,0);
		day2 = create_sprite(num5, 630, 400,0,0);
		break;
	case 26:
		day1 = create_sprite(num2, 605, 400,0,0);
		day2 = create_sprite(num6, 630, 400,0,0);
		break;
	case 27:
		day1 = create_sprite(num2, 605, 400,0,0);
		day2 = create_sprite(num7, 630, 400,0,0);
		break;
	case 28:
		day1 = create_sprite(num2, 605, 400,0,0);
		day2 = create_sprite(num8, 630, 400,0,0);
		break;
	case 29:
		day1 = create_sprite(num2, 605, 400,0,0);
		day2 = create_sprite(num9, 630, 400,0,0);
		break;
	case 30:
		day1 = create_sprite(num3, 605, 400,0,0);
		day2 = create_sprite(num0, 630, 400,0,0);
		break;
	case 31:
		day1 = create_sprite(num3, 605, 400,0,0);
		day2 = create_sprite(num1, 630, 400,0,0);
		break;
	}
	Sprite *separate1;
	separate1 = create_sprite(separate, 655, 400,0,0);


	Sprite *month1;
	Sprite *month2;

	switch(t.month)
		{
		case 1:
			month1 = create_sprite(num0, 680, 400,0,0);
			month2 = create_sprite(num1, 705, 400,0,0);
			break;
		case 2:
			month1 = create_sprite(num0, 680, 400,0,0);
			month2 = create_sprite(num2, 705, 400,0,0);
			break;
		case 3:
			month1 = create_sprite(num0, 680, 400,0,0);
			month2 = create_sprite(num3, 705, 400,0,0);
			break;
		case 4:
			month1 = create_sprite(num0, 680, 400,0,0);
			month2 = create_sprite(num4, 705, 400,0,0);
			break;
		case 5:
			month1 = create_sprite(num0, 680, 400,0,0);
			month2 = create_sprite(num5, 705, 400,0,0);
			break;
		case 6:
			month1 = create_sprite(num0, 680, 400,0,0);
			month2 = create_sprite(num6, 705, 400,0,0);
			break;
		case 7:
			month1 = create_sprite(num0, 680, 400,0,0);
			month2 = create_sprite(num7, 705, 400,0,0);
			break;
		case 8:
			month1 = create_sprite(num0, 680, 400,0,0);
			month2 = create_sprite(num8, 705, 400,0,0);
			break;
		case 9:
			month1 = create_sprite(num0, 680, 400,0,0);
			month2 = create_sprite(num9, 705, 400,0,0);
			break;
		case 10:
			month1 = create_sprite(num1, 680, 400,0,0);
			month2 = create_sprite(num0, 705, 400,0,0);
			break;
		case 11:
			month1 = create_sprite(num1, 680, 400,0,0);
			month2 = create_sprite(num1, 705, 400,0,0);
			break;
		case 12:
			month1 = create_sprite(num1, 680, 400,0,0);
			month2 = create_sprite(num2, 705, 400,0,0);
			break;
		}

	Sprite *separate2;
	separate2 = create_sprite(separate, 725, 400,0,0);

	Sprite *year1;
	Sprite *year2;

	switch(t.year)
	{
	case 16:
		year1 = create_sprite(num1, 735, 400,0,0);
		year2 = create_sprite(num6, 760, 400,0,0);
		break;
	case 17:
		year1 = create_sprite(num1, 735, 400,0,0);
		year2 = create_sprite(num7, 735, 400,0,0);
		break;
	case 18:
		year1 = create_sprite(num1, 735, 400,0,0);
		year2 = create_sprite(num8, 735, 400,0,0);
		break;
	case 19:
		year1 = create_sprite(num1, 735, 400,0,0);
		year2 = create_sprite(num9, 735, 400,0,0);
		break;
	case 20:
		year1 = create_sprite(num2, 735, 400,0,0);
		year2 = create_sprite(num0, 735, 400,0,0);
		break;
	case 21:
		year1 = create_sprite(num2, 735, 400,0,0);
		year2 = create_sprite(num1, 735, 400,0,0);
		break;
	case 22:
		year1 = create_sprite(num2, 735, 400,0,0);
		year2 = create_sprite(num2, 735, 400,0,0);
		break;
	}





	Sprite *hour1;
	Sprite *hour2;
	switch (t.hours) {
	case 0:
		hour1 = create_sprite(num0, 660, 420,0,0);
		hour2 = create_sprite(num0, 675, 420,0,0);
		break;
	case 1:
		hour1 = create_sprite(num0, 660, 420,0,0);
		hour2 = create_sprite(num1, 675, 420,0,0);
		break;
	case 2:
		hour1 = create_sprite(num0, 660, 420,0,0);
		hour2 = create_sprite(num2, 675, 420,0,0);
		break;
	case 3:
		hour1 = create_sprite(num0, 660, 420,0,0);
		hour2 = create_sprite(num3, 675, 420,0,0);
		break;
	case 4:
		hour1 = create_sprite(num0, 650, 420,0,0);
		hour2 = create_sprite(num4, 675, 420,0,0);
		break;
	case 5:
		hour1 = create_sprite(num0, 650, 420,0,0);
		hour2 = create_sprite(num5, 675, 420,0,0);
		break;
	case 6:
		hour1 = create_sprite(num0, 650, 420,0,0);
		hour2 = create_sprite(num6, 675, 420,0,0);
		break;
	case 7:
		hour1 = create_sprite(num0, 650, 420,0,0);
		hour2 = create_sprite(num7, 675, 420,0,0);
		break;
	case 8:
		hour1 = create_sprite(num0, 650, 420,0,0);
		hour2 = create_sprite(num8, 675, 420,0,0);
		break;
	case 9:
		hour1 = create_sprite(num0, 650, 420,0,0);
		hour2 = create_sprite(num9, 675, 420,0,0);
		break;
	case 10:
		hour1 = create_sprite(num1, 650, 420,0,0);
		hour2 = create_sprite(num0, 675, 420,0,0);
		break;
	case 11:
		hour1 = create_sprite(num1, 650, 420,0,0);
		hour2 = create_sprite(num1, 675, 420,0,0);
		break;
	case 12:
		hour1 = create_sprite(num1, 650, 420,0,0);
		hour2 = create_sprite(num2, 675, 420,0,0);
		break;
	case 13:
		hour1 = create_sprite(num1, 650, 420,0,0);
		hour2 = create_sprite(num3, 675, 420,0,0);
		break;
	case 14:
		hour1 = create_sprite(num1, 650, 420,0,0);
		hour2 = create_sprite(num4, 675, 420,0,0);
		break;
	case 15:
		hour1 = create_sprite(num1, 650, 420,0,0);
		hour2 = create_sprite(num5, 675, 420,0,0);
		break;
	case 16:
		hour1 = create_sprite(num1, 650, 420,0,0);
		hour2 = create_sprite(num6, 675, 420,0,0);
		break;
	case 17:
		hour1 = create_sprite(num1, 650, 420,0,0);
		hour2 = create_sprite(num7, 675, 420,0,0);
		break;
	case 18:
		hour1 = create_sprite(num1, 650, 420,0,0);
		hour2 = create_sprite(num8, 675, 420,0,0);
		break;
	case 19:
		hour1 = create_sprite(num1, 650, 420,0,0);
		hour2 = create_sprite(num9, 675, 420,0,0);
		break;
	case 20:
		hour1 = create_sprite(num2, 650, 420,0,0);
		hour2 = create_sprite(num0, 675, 420,0,0);
		break;
	case 21:
		hour1 = create_sprite(num2, 650, 420,0,0);
		hour2 = create_sprite(num1, 675, 420,0,0);
		break;
	case 22:
		hour1 = create_sprite(num2, 650, 420,0,0);
		hour2 = create_sprite(num2, 675, 420,0,0);
		break;
	case 23:
		hour1 = create_sprite(num2, 650, 420,0,0);
		hour2 = create_sprite(num3, 675, 420,0,0);
		break;
	case 24:
		hour1 = create_sprite(num2, 650, 420,0,0);
		hour2 = create_sprite(num4, 675, 420,0,0);
		break;
	}

	Sprite *separate3;
	separate3 = create_sprite(twodots, 700, 420,0,0);


	Sprite *minutes1;
	Sprite *minutes2;

	switch(t.minutes)
	{
	case 0:
		minutes1 = create_sprite(num0, 725, 420,0,0);
		minutes2 = create_sprite(num0, 750, 420,0,0);
		break;
	case 1:
		minutes1 = create_sprite(num0, 725, 420,0,0);
		minutes2 = create_sprite(num1, 750, 420,0,0);
		break;
	case 2:
		minutes1 = create_sprite(num0, 725, 420,0,0);
		minutes2 = create_sprite(num2, 750, 420,0,0);
		break;
	case 3:
		minutes1 = create_sprite(num0, 725, 420,0,0);
		minutes2 = create_sprite(num3, 750, 420,0,0);
		break;
	case 4:
		minutes1 = create_sprite(num0, 725, 420,0,0);
		minutes2 = create_sprite(num4, 750, 420,0,0);
		break;
	case 5:
		minutes1 = create_sprite(num0, 725, 420,0,0);
		minutes2 = create_sprite(num5, 750, 420,0,0);
		break;
	case 6:
		minutes1 = create_sprite(num0, 725, 420,0,0);
		minutes2 = create_sprite(num6, 750, 420,0,0);
		break;
	case 7:
		minutes1 = create_sprite(num0, 725, 420,0,0);
		minutes2 = create_sprite(num7, 750, 420,0,0);
		break;
	case 8:
		minutes1 = create_sprite(num0, 725, 420,0,0);
		minutes2 = create_sprite(num8, 750, 420,0,0);
		break;
	case 9:
		minutes1 = create_sprite(num0, 725, 420,0,0);
		minutes2 = create_sprite(num9, 750, 420,0,0);
		break;
	case 10:
		minutes1 = create_sprite(num1, 725, 420,0,0);
		minutes2 = create_sprite(num0, 750, 420,0,0);
		break;
	case 11:
		minutes1 = create_sprite(num1, 725, 420,0,0);
		minutes2 = create_sprite(num1, 750, 420,0,0);
		break;
	case 12:
		minutes1 = create_sprite(num1, 725, 420,0,0);
		minutes2 = create_sprite(num2, 750, 420,0,0);
		break;
	case 13:
		minutes1 = create_sprite(num1, 725, 420,0,0);
		minutes2 = create_sprite(num3, 750, 420,0,0);
		break;
	case 14:
		minutes1 = create_sprite(num1, 725, 420,0,0);
		minutes2 = create_sprite(num4, 750, 420,0,0);
		break;
	case 15:
		minutes1 = create_sprite(num1, 725, 420,0,0);
		minutes2 = create_sprite(num5, 750, 420,0,0);
		break;
	case 16:
		minutes1 = create_sprite(num1, 725, 420,0,0);
		minutes2 = create_sprite(num6, 750, 420,0,0);
		break;
	case 17:
		minutes1 = create_sprite(num1, 725, 420,0,0);
		minutes2 = create_sprite(num7, 750, 420,0,0);
		break;
	case 18:
		minutes1 = create_sprite(num1, 725, 420,0,0);
		minutes2 = create_sprite(num8, 750, 420,0,0);
		break;
	case 19:
		minutes1 = create_sprite(num1, 725, 420,0,0);
		minutes2 = create_sprite(num9, 750, 420,0,0);
		break;
	case 20:
		minutes1 = create_sprite(num2, 725, 420,0,0);
		minutes2 = create_sprite(num0, 750, 420,0,0);
		break;
	case 21:
		minutes1 = create_sprite(num2, 725, 420,0,0);
		minutes2 = create_sprite(num1, 750, 420,0,0);
		break;
	case 22:
		minutes1 = create_sprite(num2, 725, 420,0,0);
		minutes2 = create_sprite(num2, 750, 420,0,0);
		break;
	case 23:
		minutes1 = create_sprite(num2, 725, 420,0,0);
		minutes2 = create_sprite(num3, 750, 420,0,0);
		break;
	case 24:
		minutes1 = create_sprite(num2, 725, 420,0,0);
		minutes2 = create_sprite(num4, 750, 420,0,0);
		break;
	case 25:
		minutes1 = create_sprite(num2, 725, 420,0,0);
		minutes2 = create_sprite(num5, 750, 420,0,0);
		break;
	case 26:
		minutes1 = create_sprite(num2, 725, 420,0,0);
		minutes2 = create_sprite(num6, 750, 420,0,0);
		break;
	case 27:
		minutes1 = create_sprite(num2, 725, 420,0,0);
		minutes2 = create_sprite(num7, 750, 420,0,0);
		break;
	case 28:
		minutes1 = create_sprite(num2, 725, 420,0,0);
		minutes2 = create_sprite(num8, 750, 420,0,0);
		break;
	case 29:
		minutes1 = create_sprite(num2, 725, 420,0,0);
		minutes2 = create_sprite(num9, 750, 420,0,0);
		break;

	case 30:
		minutes1 = create_sprite(num3, 725, 420,0,0);
		minutes2 = create_sprite(num0, 750, 420,0,0);
		break;
	case 31:
		minutes1 = create_sprite(num3, 725, 420,0,0);
		minutes2 = create_sprite(num1, 750, 420,0,0);
		break;
	case 32:
		minutes1 = create_sprite(num3, 725, 420,0,0);
		minutes2 = create_sprite(num2, 750, 420,0,0);
		break;
	case 33:
		minutes1 = create_sprite(num3, 725, 420,0,0);
		minutes2 = create_sprite(num3, 750, 420,0,0);
		break;
	case 34:
		minutes1 = create_sprite(num3, 725, 420,0,0);
		minutes2 = create_sprite(num4, 750, 420,0,0);
		break;
	case 35:
		minutes1 = create_sprite(num3, 725, 420,0,0);
		minutes2 = create_sprite(num5, 750, 420,0,0);
		break;

	case 36:
		minutes1 = create_sprite(num3, 725, 420,0,0);
		minutes2 = create_sprite(num6, 750, 420,0,0);
		break;
	case 37:
		minutes1 = create_sprite(num3, 725, 420,0,0);
		minutes2 = create_sprite(num7, 750, 420,0,0);
		break;
	case 38:
		minutes1 = create_sprite(num3, 725, 420,0,0);
		minutes2 = create_sprite(num8, 750, 420,0,0);
		break;
	case 39:
		minutes1 = create_sprite(num3, 725, 420,0,0);
		minutes2 = create_sprite(num9, 750, 420,0,0);
		break;

	case 40:
		minutes1 = create_sprite(num4, 725, 420,0,0);
		minutes2 = create_sprite(num0, 750, 420,0,0);
		break;
	case 41:
		minutes1 = create_sprite(num4, 725, 420,0,0);
		minutes2 = create_sprite(num1, 750, 420,0,0);
		break;
	case 42:
		minutes1 = create_sprite(num4, 725, 420,0,0);
		minutes2 = create_sprite(num2, 750, 420,0,0);
		break;
	case 43:
		minutes1 = create_sprite(num4, 725, 420,0,0);
		minutes2 = create_sprite(num3, 750, 420,0,0);
		break;
	case 44:
		minutes1 = create_sprite(num4, 725, 420,0,0);
		minutes2 = create_sprite(num4, 750, 420,0,0);
		break;
	case 45:
		minutes1 = create_sprite(num4, 725, 420,0,0);
		minutes2 = create_sprite(num5, 750, 420,0,0);
		break;
	case 46:
		minutes1 = create_sprite(num4, 725, 420,0,0);
		minutes2 = create_sprite(num6, 750, 420,0,0);
		break;
	case 47:
		minutes1 = create_sprite(num4, 725, 420,0,0);
		minutes2 = create_sprite(num7, 750, 420,0,0);
		break;
	case 48:
		minutes1 = create_sprite(num4, 725, 420,0,0);
		minutes2 = create_sprite(num8, 750, 420,0,0);
		break;
	case 49:
		minutes1 = create_sprite(num4, 725, 420,0,0);
		minutes2 = create_sprite(num9, 750, 420,0,0);
		break;
	case 50:
		minutes1 = create_sprite(num5, 725, 420,0,0);
		minutes2 = create_sprite(num0, 750, 420,0,0);
		break;
	case 51:
		minutes1 = create_sprite(num5, 725, 420,0,0);
		minutes2 = create_sprite(num1, 750, 420,0,0);
		break;
	case 52:
		minutes1 = create_sprite(num5, 725, 420,0,0);
		minutes2 = create_sprite(num2, 750, 420,0,0);
		break;
	case 53:
		minutes1 = create_sprite(num5, 725, 420,0,0);
		minutes2 = create_sprite(num3, 750, 420,0,0);
		break;
	case 54:
		minutes1 = create_sprite(num5, 725, 420,0,0);
		minutes2 = create_sprite(num4, 750, 420,0,0);
		break;
	case 55:
		minutes1 = create_sprite(num5, 725, 420,0,0);
		minutes2 = create_sprite(num5, 750, 420,0,0);
		break;
	case 56:
		minutes1 = create_sprite(num5, 725, 420,0,0);
		minutes2 = create_sprite(num6, 750, 420,0,0);
		break;
	case 57:
		minutes1 = create_sprite(num5, 725, 420,0,0);
		minutes2 = create_sprite(num7, 750, 420,0,0);
		break;
	case 58:
		minutes1 = create_sprite(num5, 725, 420,0,0);
		minutes2 = create_sprite(num8, 750, 420,0,0);
		break;
	case 59:
		minutes1 = create_sprite(num5, 725, 420,0,0);
		minutes2 = create_sprite(num9, 750, 420,0,0);
		break;
	}


	draw_xpm(day1);
	draw_xpm(day2);
	draw_xpm(separate1);
	draw_xpm(month1);
	draw_xpm(month2);
	draw_xpm(separate2);
    draw_xpm(year1);
    draw_xpm(year2);
	draw_xpm(separate3);
	draw_xpm(minutes1);
	draw_xpm(minutes2);
	draw_xpm(hour1);
	draw_xpm(hour2);


	destroy_sprite(day1);
	destroy_sprite(day2);
	destroy_sprite(separate1);
	destroy_sprite(month1);
	destroy_sprite(month2);
	destroy_sprite(separate2);
	destroy_sprite(year1);
	destroy_sprite(year2);
	destroy_sprite(hour1);
	destroy_sprite(hour2);
	destroy_sprite(separate3);
	destroy_sprite(minutes1);
	destroy_sprite(minutes2);
}



void drawCounter(int counter) {
	counter = (counter / 60) + 1;
	char str[20];
	sprintf(str, "%d", counter);
	int i = 0;

	while (str[i] != '\0') {
		Sprite *sp;

		switch (str[i]) {
		case '0':
			sp = create_sprite(num0, 730 + 25*i, 10,0,0);
			break;
		case '1':
			sp = create_sprite(num1, 730  + 25*i, 10,0,0);
			break;
		case '2':
			sp = create_sprite(num2, 730  + 25*i, 10,0,0);
			break;
		case '3':
			sp = create_sprite(num3, 730 + 25*i, 10,0,0);
			break;
		case '4':
			sp = create_sprite(num4, 730  + 25*i, 10,0,0);
			break;
		case '5':
			sp = create_sprite(num5, 730 + 25*i, 10,0,0);
			break;
		case '6':
			sp = create_sprite(num6, 730  + 25*i, 10,0,0);
			break;
		case '7':
			sp = create_sprite(num7, 730  + 25*i, 10,0,0);
			break;
		case '8':
			sp = create_sprite(num8, 730  + 25*i, 1,0,0);
			break;
		case '9':
			sp = create_sprite(num9, 730 + 25*i, 10,0,0);
			break;
		}

		draw_xpm(sp);
		destroy_sprite(sp);
		i++;
	}
}

