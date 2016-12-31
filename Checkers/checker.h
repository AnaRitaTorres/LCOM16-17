#pragma once

/** @defgroup checker checker
 * @{
 * Functions for checker
 */


typedef struct
{
	int x; //especifica a posicao x da dama no tabuleiro
	int y; //especifica a posicao y da dama no tabuleiro
	int color; //especifica a cor da dama
} Checker; //criacao do objeto do tipo Checker


/**
 * @brief Cria um objeto do tipo Checker
 *
 * @param x posicao x inicial da dama criada
 * @param y posicao y inicial da dama criada
 * @param color cor da dama criada
 *
 * @return um apontador para a nova dama criada
 */

Checker* createChecker(int x, int y, int color);
/**
 * @brief Desenho as damas no tabuleiro nas posicoes inicias
 *
 * @param  buf buffer para onde as damas sao desenhadas
 * @param  board apontador para o tabuleiro onde as damas tao representadas
 *
 */
void drawCheckers(int board[][6], char* buf);
/**
 * @brief Elimina um objeto do tipo Checker libertando a memória por ele ocupado
 *
 * @param  c apontador para um objeto do tipo Checker
 *
 */
void deleteChecker(Checker* c);
/**
 * @brief muda a posicao das dama c para a posicao x e y recebidas como argumento
 *
 * @param  c apontador para um objeto do tipo c
 * @param  x posicao no tabuleiro
 * @param  y posicao no tabuleiro
 *
 */

void setCheckerLocation(Checker* c, int x, int y);
/**
 * @brief move a dama no tabuleiro para uma nova posicao dependendo do scancode recebido
 *
 * @param  board pointer do board
 * @param  x posicao no tabuleiro
 * @param  y posicao no tabuleiro
 * @param  scancode recebida pelo teclado~
 *
 * @return inteiro se for 0 significa que nao se pode mexer, se for 1 ou 2 representa o proximo jogador a jogar
 * se retornar -1 significa que o jogador tentou premir uma tecla nao possivel para se mexer
 */
int moveChecker(int board[][6], int x, int y, unsigned long scancode);
/**
 * @brief muda a cor da dama para azul quando escolhida pelo rato
 *
 * @param  xChecker a posicao x da dama
 * @param  yChecker a posicao y da dama
 * @param  buf buffer para o qual se desenha esta novo circulo de uma nova cor
 *
 */
void highlightChecker(int xChecker, int yChecker, char* buf);
