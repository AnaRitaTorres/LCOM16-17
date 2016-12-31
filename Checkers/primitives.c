#include "primitives.h"
#include "video_gr.h"


Square* newSquare(int x, int y, int l) {
	Square * square = (Square*) malloc(sizeof(Square));
	square->x = x;
	square->y = y;
	square->l = l;
	return square;
}

void deleteSquare(Square* square) {
	free(square);
}

void setSquareLocation(Square* square, int x, int y) {
	square->x = x;
	square->y = y;
}

void moveSquare(Square* square, int x, int y) {
	square->x += x;
	square->y += y;
}

void drawSquare(Square* square, int color, char* buf) {
	draw_square(square->x,square->y,square->l,color);
}
