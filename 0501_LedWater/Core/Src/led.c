#include "led.h"
#include "mycode.h"

#define LED_PORT          GPIOF
#define LED_ON_LEVEL      GPIO_PIN_RESET   
#define LED_OFF_LEVEL     GPIO_PIN_SET
#define LED_STEP_MS       200             
#define LED_COUNT  (sizeof(led_pins) / sizeof(led_pins[0]))
	

static const uint16_t led_pins[] = {
    GPIO_PIN_0, GPIO_PIN_1, GPIO_PIN_2, GPIO_PIN_3,
    GPIO_PIN_4, GPIO_PIN_5, GPIO_PIN_6, GPIO_PIN_7,
};
 void LedWater_Run(void)
{
    for (uint8_t i = 0; i < LED_COUNT; i++)
    {
        HAL_GPIO_WritePin(LED_PORT, led_pins[i], LED_ON_LEVEL);
        HAL_Delay(LED_STEP_MS);
        HAL_GPIO_WritePin(LED_PORT, led_pins[i], LED_OFF_LEVEL);
        HAL_Delay(LED_STEP_MS);
    }
}
//static void LedWater_Task(void)
//{
//    static uint32_t last_tick = 0;
//    static uint8_t  index     = 0;
//    static uint8_t  on     = 0;

//    if (HAL_GetTick() - last_tick < LED_STEP_MS)
//    {
//        return;                       
//    }
//    last_tick = HAL_GetTick();

//    if (on)
//    {
//        Led_Off(index);
//        index = (index + 1) % LED_COUNT;
//        on = 0;
//    }
//    else
//    {
//        Led_On(index);
//        on = 1;
//    }
//}