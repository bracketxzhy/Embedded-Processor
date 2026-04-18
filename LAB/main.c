#include "stm32l476xx.h"
#include "SysClock.h"
#include "UART.h"
#include <string.h>
#include <stdio.h>

#define LED_PIN 5
#define BUTTON_PIN 13

void demo_of_printf_scanf()
{
  char rxByte;
  printf("Are you enrolled in ECE 202 (Y or N ):\r\n");
  scanf("%c", &rxByte);
  if (rxByte == 'N' || rxByte == 'n')
  {
    printf("You should not be here!!!\r\n\r\n");
  }
  else if (rxByte == 'Y' || rxByte == 'y')
  {
    printf("Welcome!!! \n\r\n\r\n");
  }
}

int main(void)
{

  System_Clock_Init();
  UART2_Init();

  RCC->AHB2ENR &= ~(0x00000005);
  RCC->AHB2ENR |= (0x00000005);

  GPIOA->MODER &= ~(0x00000C00);
  GPIOA->MODER |= (0x00000400);

  GPIOA->OTYPER &= ~(0x00000020);
  GPIOA->OTYPER |= (0x00000000);

  GPIOA->PUPDR &= ~(0x00000C00);
  GPIOA->PUPDR |= (0x00000000);

  GPIOC->MODER &= ~(0x0C000000);
  GPIOC->MODER |= (0x00000000);

  GPIOC->PUPDR &= ~(0x0C000000);
  GPIOC->PUPDR |= (0x00000000);

  GPIOA->ODR &= ~(1 << LED_PIN);

  while (1)
  {

    if ((GPIOC->IDR & (1 << BUTTON_PIN)) == 0)
    {
      GPIOA->ODR ^= (1 << LED_PIN);

      for (volatile int i = 0; i < 200000; i++)
        ;
    }
  }
}