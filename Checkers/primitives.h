#pragma once

/** @defgroup
 * @{
 * Functions for primitives manipulation
 */

typedef struct {
	int x; // especifica a posicao x do canto esquerdo superior
	int y; // especifica a posicao y do canto esquerdo superior
	int l; // especifica o comprimento do lado do quadrado
} Square;


/**
 * @brief Cria um novo quadrado
 *
 * @param x posicao x
 * @param y posicao y
 * @param w valor do comprimento
 * @param h valor da altura
 * @return apontador nao null para o quadrado
 */
Square* newSquare(int x, int y, int l);

/**
 * @brief Apaga um quadrado
 *
 * @param square apontador para o quadrado
 */
void deleteSquare(Square * Square);

/**
 * @brief faz set da posicao do quadrado
 *
 * @param square apontador para o quadrado
 * @param x nova posicao do x
 * @param y nova posicao do y
 */
void setSquareLocation(Square * Square, int x, int y);

/**
 * @brief move o quadrado
 *
 * @param square apontador do quadrado
 * @param x variacao de x
 * @param y variacao de y
 */
void moveSquare(Square* square, int x, int y);

/**
 * @brief desenha um quadrado
 *
 * @param square apontador para o quadrado
 * @param color cor do quadrado
 * @param buf buffer no qual o quadrado vai ser desenhado
 */
void drawSquare(Square* square, int color, char* buf);
