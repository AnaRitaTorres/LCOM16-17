#pragma once

/** @defgroup rectangle rectangle
 * @{
 * Functions for rectangle manipulation
 */

typedef struct {
	int x; // especifica a posicao x do canto esquerdo superior
	int y; // especifica a posicao y do canto esquerdo superior
	int w; // especifica o comprimento
	int h; // especifica a altura
} Rectangle;


/**
 * @brief Cria um novo retangulo
 *
 * @param x posicao x
 * @param y posicao y
 * @param w valor do comprimento
 * @param h valor da altura
 * @return apontador nao null para o retangulo
 */
Rectangle* newRectangle(int x, int y, int w, int h);

/**
 * @brief Apaga um retangulo
 *
 * @param rectangle apontador para o retangulo
 */
void deleteRectangle(Rectangle * rectangle);

/**
 * @brief faz set da posicao do retangulo
 *
 * @param rectangle apontador para o retangulo
 * @param x nova posicao do x
 * @param y nova posicao do y
 */
void setRecLocation(Rectangle * rectangle, int x, int y);

/**
 * @brief move o retangulo
 *
 * @param rectangle apontador do retangulo
 * @param x variacao de x
 * @param y variacao de y
 */
void moveRectangle(Rectangle* rectangle, int x, int y);

/**
 * @brief desenha um retangulo
 *
 * @param rectangle apontador para o retangulo
 * @param color cor do retangulo
 * @param buf buffer no qual o retangulo vai ser desenhado
 */
void drawRectangle(Rectangle* rectangle, int color, char* buf);
