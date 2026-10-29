#include "key.h"

#define KEY_PORT           GPIOE
#define KEY_ROW_PINS       (GPIO_PIN_4 | GPIO_PIN_5 | GPIO_PIN_6)
#define KEY_DEBOUNCE_MS    20

static const uint16_t key_row_pins[KEY_ROW_NUM] = {
    GPIO_PIN_4, GPIO_PIN_5, GPIO_PIN_6,
};

static const uint16_t key_col_pins[KEY_COL_NUM] = {
    GPIO_PIN_0, GPIO_PIN_1, GPIO_PIN_2, GPIO_PIN_3,
};

void Key_Init(void)
{
    GPIO_InitTypeDef GPIO_InitStruct = {0};

    __HAL_RCC_GPIOE_CLK_ENABLE();

    /* 行：推挽输出，默认全拉高 */
    HAL_GPIO_WritePin(KEY_PORT, KEY_ROW_PINS, GPIO_PIN_SET);
    GPIO_InitStruct.Pin   = KEY_ROW_PINS;
    GPIO_InitStruct.Mode  = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull  = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    HAL_GPIO_Init(KEY_PORT, &GPIO_InitStruct);

    /* 列：上拉输入，没按键读高，按下被行拉低 */
    GPIO_InitStruct.Pin  = GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3;
    GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
    GPIO_InitStruct.Pull = GPIO_PULLUP;
    HAL_GPIO_Init(KEY_PORT, &GPIO_InitStruct);
}


static uint8_t Key_RawScan(void)
{
    uint8_t key = KEY_NONE;
    uint8_t r, c;

    for (r = 0; r < KEY_ROW_NUM; r++)
    {
        
        HAL_GPIO_WritePin(KEY_PORT, KEY_ROW_PINS, GPIO_PIN_SET);
        HAL_GPIO_WritePin(KEY_PORT, key_row_pins[r], GPIO_PIN_RESET);

        for (c = 0; c < KEY_COL_NUM; c++)
        {
            if (HAL_GPIO_ReadPin(KEY_PORT, key_col_pins[c]) == GPIO_PIN_RESET)
            {
                key = (uint8_t)(r * KEY_COL_NUM + c + 1);
            }
        }
    }

    HAL_GPIO_WritePin(KEY_PORT, KEY_ROW_PINS, GPIO_PIN_SET);
    return key;
}


uint8_t Key_Scan(void)
{
    static uint8_t last_key = KEY_NONE;
    uint8_t key = Key_RawScan();

    if (key != KEY_NONE)
    {
        HAL_Delay(KEY_DEBOUNCE_MS);
        if (Key_RawScan() != key)
        {
            key = KEY_NONE;     
        }
    }

    if (key != last_key)
    {
        last_key = key;
        return key;
    }
    return KEY_NONE;
}
