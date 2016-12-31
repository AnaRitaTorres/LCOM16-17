#pragma once

/** @defgroup rtc rtc
 * @{
 * Functions for rtc
 */

#include "i8042.h"

#define RTC_IRQ         8/**< @brief RTC IRQ  */
#define RTC_HOOK        4/**< @brief RTC HOOK  */

#define ADDR_REG        0x70/**< @brief registo de endereco de RTC  */
#define DATA_REG        0x71/**< @brief RTC registo de informacao  */

#define SECONDS         0x0/**< @brief segundos */
#define MINUTES         0x2/**< @brief minutos */
#define HOURS           0x4/**< @brief horas */
#define DAY             0x7/**< @brief dia */
#define MONTH           0x8/**< @brief mes */
#define YEAR            0x9/**< @brief ano */
#define REG_A           0xA/**< @brief registo A */
#define REG_B           0xB/**< @brief registo B */
#define REG_C           0xC/**< @brief registo C */
#define REG_D           0xD/**< @brief registo D */

/* REGISTER_A BITS */
#define RS0_BIT         BIT(0) /**< @brief RS0 - rate selector */
#define RS1_BIT         BIT(1) /**< @brief RS1 - rate selector */
#define RS2_BIT         BIT(2) /**< @brief RS2 - rate selector */
#define RS3_BIT         BIT(3) /**< @brief RS3 - rate selector */
#define DV0_BIT         BIT(4) /**< @brief DV0 - controla o contador da corrente*/
#define DV1_BIT         BIT(5) /**< @brief DV1 - controla o contador da corrente*/
#define DV2_BIT         BIT(6) /**< @brief DV2 - controlo o contador da corrente*/
#define UIP             BIT(7) /**< @brief UIP - atualiza o progresso */


/* REGISTER_B BITS */
#define DSE                 BIT(0)/**< @brief DSE - ativa a guarda de tempo do dia*/
#define MODE       			BIT(1) /**< @brief MODE - 24_12 */
#define DM         	 		BIT(2)/**< @brief DM - binario bcd */
#define SQWE                BIT(3) /**< @brief SQWE - ativa gerador de square-wave */
#define UIE                 BIT(4) /**< @brief UIE - interrompe a fonte  */
#define AIE                 BIT(5) /**< @brief AIE - interrompe a fonte */
#define PIE                 BIT(6)/**< @brief PIE - interrompe a fonte */
#define SET                 BIT(7)/**< @brief SET -  inibe atualizacoes */

/* REGISTER_C BITS */
#define UF          BIT(4)/**< @brief UF - interrupcoes das atualizacoes pendentes */
#define AF          BIT(5)/**< @brief AF - interrupcoes do alarme pendente */
#define PF          BIT(6) /**< @brief PF - interrupcoes periodicas pendentes */
#define IRQF        BIT(7)/**< @brief IRQF - IRQ linha ativa */

/* REGISTER_D BITS */
#define VRT_BIT         BIT(7)/**< @brief VRT -  RAM/tempo valido */



typedef struct {

	unsigned long seconds; //especifica os segundos
	unsigned long minutes;//especifica os minutos
	unsigned long hours;//especifica as horas

	unsigned long day; //especifica o dia
	unsigned long month;//especifica o mes
	unsigned long year;//especifica o ano

} rtc_time_t;

/**
 * @brief subscreve as interrupcoes do RTC
 *
 * @return validacao
 */
int rtc_subscribe();
/**
 * @brief deixa de subscrever as interrupcoes do rtc
 *
 * @return validacao
 */
int rtc_unsubscribe();
/**
 * @brief converte a data de bcd para inteiros
 *
 *@return informacao em inteiro
 */
unsigned long read_bcd(unsigned long date);
/**
 * @brief le a informacao da data do pc em modo bcd
 *
 * @param reg registo a ser lido
 * @param data informacao a ser lida
 */
void rtc_read(unsigned long reg, unsigned long* data);
/**
 * @brief le a data e converte em inteiro
 *
 *@return retorna a data
 */
rtc_time_t rtc_read_date();

