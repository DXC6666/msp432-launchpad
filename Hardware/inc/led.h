#ifndef __LED_H__
#define __LED_H__



typedef enum
{
    led1,
    led2_red,
    led2_green,
    led2_blue
}led_state_t;

void led_Init(void);
void led_on(led_state_t led_state);
void led_toggle(led_state_t led_state);

#endif