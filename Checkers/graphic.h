#ifndef _GRAPHIC_H_
#define _GRAPHIC_H_
#include "rtc.h"

/** @defgroup graphic graphic
 * @{
 * Functions for graphic
 */




/**
 * @brief desenha o numero de damas que o player 1 tem durante o jogo
 *
 * @param  playercheckers1 que representa o numero de damas que o jogador 1 tem
 *
 */
void drawnrcheckersplayer1 (int playercheckers1);
/**
 * @brief desenha o numero de damas que o player 2 tem durante o jogo
 *
 * @param  playercheckers2 que representa o numero de damas que o jogador 1 tem
 *
 */
void drawnrcheckersplayer2 (int playercheckers2);
/**
 * @brief desenha uma mensagem a dizer que jogador ganhou se o P1 ou o P2
 *
 * @param  playercheckers1 que representa o numero de damas que o jogador 1 tem
 *
 */
void winnerPlayer(int playercheckers1);
/**
 * @brief desenha o nome do player a beira do tabuleiro
 *
 * @param  player que representa o jogador
 *
 */
void drawplayer(int player);
/**
 * @brief desenha a data em que esta a ser realizada o jogo e a respetiva hora
 *
 * @param  t do objeto do tipo rtc_time_t
 *
 */
void drawDate(rtc_time_t t);
/**
 * @brief desenha o tempo que cada jogador ainda tem para efetuar uma jogada
 *
 * @param  counter representa o tempo que o jogador ainda tem
 *
 */
void drawCounter(int counter);




#endif

