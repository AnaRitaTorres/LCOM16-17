#ifndef __TIMER_H
#define __TIMER_H



typedef struct {
	int counter; // especifica o contador
	int ticked; // especifica se uma interrupcao do timer e "ticked"
} Timer;

/**
 * @brief Cria um novo timer
 *
 * @return apontador nao nulo para o novo timer
 */
Timer* newTimer();
/**
 * @brief Faz reset da flag ticked
 *
 * @param timer apontador para o timer
 */
void resetTimer(Timer* timer);

/**
 * @brief apaga o timer
 *
 * @param timer apontador para o timer
 */
void deleteTimer(Timer* timer);

/**
 * @brief vai buscar o byte respetivo do timer
 *
 * @param byte que se quer ir buscar
 * @return do byte do timer
 */
unsigned long getByte(unsigned long timer);

/**
 * @brief vai buscar a configuraçao de cada byte do timer
 *
 * @param byte que se quer ler a configuraçao
 * @return de um inteiro, 0 se for bem sucedido, 1 se falhar
 */
int timer_get_conf(unsigned long timer, unsigned char *st);

/**
 * @brief Configura um timer para gerar uma onda quadrada (square wave)
 * 
 * nao muda o byte menos significativo(LSB) (BCD/binary) da palavra de controlo do timer.
 * 
 * @param timer timer a configurar (intervalo de 0 ate 2)
 * @param freq frequencia da onde a gerar
 * @return retorna 0 se for bem sucedida, outro numero se nao for bem sucedida
 */
int timer_set_square(unsigned long timer, unsigned long freq);

/**
 * @brief subscreve e ativa as interrupcoes do timer 0
 *
 * @return retorna a ordem do bit numa mascara; negativo se falhar
 */
int timer_subscribe_int();

/**
 * @brief deixa de subscrever as interrupcoes do Timer 0
 *
 * @return retorna 0 se for bem sucedido, caso contrario nao zero
 */
int timer_unsubscribe_int();

/**
 * @brief Timer 0 interrompe o handler
 *
 * incrementa o countador
 */
void timer_handler(Timer* timer);



#endif /* __TIMER_H */


