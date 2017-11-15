#ifndef ADC_H
#define ADC_H
#include "stm32l432xx.h"

#define MY_ADC ADC1

extern void adcConfig(void);

/*
 * Hint:
 * In RCC ADC is mentioned in AHB2 registers and in CCIPR register.
 */

#endif //ADC_H
