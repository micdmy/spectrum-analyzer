#ifndef USER_H
#define USER_H
#include "stm32l4xx.h"
#include "DNucleoL432KC.h"

/*
 * Enables and configurates GPIOA PIN 8 for MCO.
 */
extern void mcoOutputPinEnable(void);

extern void ledGreenConfig(void);

extern void ledGreen(char onOff);

extern void ledGreenToggle(void);

#endif //USER_H
