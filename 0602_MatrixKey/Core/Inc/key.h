#ifndef __KEY_H__
#define __KEY_H__

#include "main.h"

#define KEY_ROW_NUM     3
#define KEY_COL_NUM     4
#define KEY_NONE        0

void    Key_Init(void);
uint8_t Key_Scan(void);

#endif
