#include "led.h"
#include "mycode.h"

#define LED_PORT          GPIOF
#define LED_ON_LEVEL      GPIO_PIN_RESET
#define LED_OFF_LEVEL     GPIO_PIN_SET
#define LED_STEP_MS       200
#define LED_ALL_PINS      (GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3 | \
                           GPIO_PIN_4 | GPIO_PIN_5 | GPIO_PIN_6 | GPIO_PIN_7)

static const uint16_t led_pins[LED_NUM] = {
    GPIO_PIN_0, GPIO_PIN_1, GPIO_PIN_2, GPIO_PIN_3,
    GPIO_PIN_4, GPIO_PIN_5, GPIO_PIN_6, GPIO_PIN_7,
};

/* 点亮第 index 个灯，index 从 0 开始，越界直接当没看见 */
void Led_On(uint8_t index)
{
    if (index < LED_NUM)
    {
        HAL_GPIO_WritePin(LED_PORT, led_pins[index], LED_ON_LEVEL);
    }
}

void Led_Off(uint8_t index)
{
    if (index < LED_NUM)
    {
        HAL_GPIO_WritePin(LED_PORT, led_pins[index], LED_OFF_LEVEL);
    }
}

void Led_Toggle(uint8_t index)
{
    if (index < LED_NUM)
    {
        if (HAL_GPIO_ReadPin(LED_PORT, led_pins[index]) == LED_ON_LEVEL)
        {
            HAL_GPIO_WritePin(LED_PORT, led_pins[index], LED_OFF_LEVEL);
        }
        else
        {
            HAL_GPIO_WritePin(LED_PORT, led_pins[index], LED_ON_LEVEL);
        }
    }
}

void Led_All_On(void)
{
    HAL_GPIO_WritePin(LED_PORT, LED_ALL_PINS, LED_ON_LEVEL);
}

void Led_All_Off(void)
{
    HAL_GPIO_WritePin(LED_PORT, LED_ALL_PINS, LED_OFF_LEVEL);
}

void LedWater_Run(void)
{
    uint8_t i;

    for (i = 0; i < LED_NUM; i++)
    {
        Led_On(i);
        HAL_Delay(LED_STEP_MS);
        Led_Off(i);
        HAL_Delay(LED_STEP_MS);
    }
}
