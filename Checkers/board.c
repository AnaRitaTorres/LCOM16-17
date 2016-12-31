#include "board.h"
#include "video_gr.h"
#include "rectangle.h"
#include "numberxpm.h"
#include "sprite.h"
#include "letterxpm.h"
#include "video_gr.h"



void drawBoard(int color1, int color2, char* buf)
{
	Rectangle* r1 = newRectangle(  0,  0,100,100); //1 linha
	Rectangle* r2 = newRectangle(100,  0,100,100);
	Rectangle* r3 = newRectangle(200,  0,100,100);
	Rectangle* r4 = newRectangle(300,  0,100,100);
	Rectangle* r5 = newRectangle(400,  0,100,100);
	Rectangle* r6 = newRectangle(500,  0,100,100);
	Rectangle* r7 = newRectangle(  0,100,100,100);//2 linha
	Rectangle* r8 = newRectangle(100,100,100,100);
	Rectangle* r9 = newRectangle(200,100,100,100);
	Rectangle* r10= newRectangle(300,100,100,100);
	Rectangle* r11= newRectangle(400,100,100,100);
	Rectangle* r12= newRectangle(500,100,100,100);
	Rectangle* r13= newRectangle(  0,200,100,100);//3 linha
	Rectangle* r14= newRectangle(100,200,100,100);
	Rectangle* r15= newRectangle(200,200,100,100);
	Rectangle* r16= newRectangle(300,200,100,100);
	Rectangle* r17= newRectangle(400,200,100,100);
	Rectangle* r18= newRectangle(500,200,100,100);
	Rectangle* r19= newRectangle(  0,300,100,100);//4 linha
	Rectangle* r20= newRectangle(100,300,100,100);
	Rectangle* r21= newRectangle(200,300,100,100);
	Rectangle* r22= newRectangle(300,300,100,100);
	Rectangle* r23= newRectangle(400,300,100,100);
	Rectangle* r24= newRectangle(500,300,100,100);
	Rectangle* r25= newRectangle(  0,400,100,100);//5 linha
	Rectangle* r26= newRectangle(100,400,100,100);
	Rectangle* r27= newRectangle(200,400,100,100);
	Rectangle* r28= newRectangle(300,400,100,100);
	Rectangle* r29= newRectangle(400,400,100,100);
	Rectangle* r30= newRectangle(500,400,100,100);
	Rectangle* r31= newRectangle(  0,500,100,100);//6 linha
	Rectangle* r32= newRectangle(100,500,100,100);
	Rectangle* r33= newRectangle(200,500,100,100);
	Rectangle* r34= newRectangle(300,500,100,100);
	Rectangle* r35= newRectangle(400,500,100,100);
	Rectangle* r36= newRectangle(500,500,100,100);


	drawRectangle( r1, color1, buf);//1 linha
	drawRectangle( r2, color2, buf);
	drawRectangle( r3, color1, buf);
	drawRectangle( r4, color2, buf);
	drawRectangle( r5, color1, buf);
	drawRectangle( r6, color2, buf);
	drawRectangle( r7, color2, buf);//2 linha
	drawRectangle( r8, color1, buf);
	drawRectangle( r9, color2, buf);
	drawRectangle(r10, color1, buf);
	drawRectangle(r11, color2, buf);
	drawRectangle(r12, color1, buf);
	drawRectangle(r13, color1, buf);//3 linha
	drawRectangle(r14, color2, buf);
	drawRectangle(r15, color1, buf);
	drawRectangle(r16, color2, buf);
	drawRectangle(r17, color1, buf);
	drawRectangle(r18, color2, buf);
	drawRectangle(r19, color2, buf);//4 linha
	drawRectangle(r20, color1, buf);
	drawRectangle(r21, color2, buf);
	drawRectangle(r22, color1, buf);
	drawRectangle(r23, color2, buf);
	drawRectangle(r24, color1, buf);
	drawRectangle(r25, color1, buf);//5 linha
	drawRectangle(r26, color2, buf);
	drawRectangle(r27, color1, buf);
	drawRectangle(r28, color2, buf);
	drawRectangle(r29, color1, buf);
	drawRectangle(r30, color2, buf);
	drawRectangle(r31, color2, buf);//6 linha
	drawRectangle(r32, color1, buf);
	drawRectangle(r33, color2, buf);
	drawRectangle(r34, color1, buf);
	drawRectangle(r35, color2, buf);
	drawRectangle(r36, color1, buf);
}







