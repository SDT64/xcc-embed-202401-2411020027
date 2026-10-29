#ifndef __LED_H__
#define __LED_H__

#include "main.h"

#define LED_NUM     8

void Led_On(uint8_t index);
void Led_Off(uint8_t index);
void Led_Toggle(uint8_t index);
void Led_All_On(void);
void Led_All_Off(void);
void LedWater_Run(void);

#endif
