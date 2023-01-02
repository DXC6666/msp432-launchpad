#ifndef __EXTI_H__
#define __EXTI_H__



typedef enum
{
    rising,
    falling

}EXIT_Mode;

void EXTI_Init(uint_fast8_t selectedPort, uint_fast16_t selectedPins, EXIT_Mode mode);
#endif