/*
 * valve_definition.h
 *
 *  Created on: Aug 25, 2023
 *      Author: Felipe
 */

#include <stdbool.h>
#include <stdint.h>

//#include "system/clock.h"
//#include "system/gpio.h"

#include "assert.h"
//#include "gpio.h"
#include "led.h"
#include "led_definition.h"
#include "main.h"

/** cycle time for ultrafast blinking led 100ms */
#define BLINK_CYCLE_ULTRA      8
#define ONTIME_ULTRA           7

/** cycle time for fast blinking led 200ms */
#define BLINK_CYCLE_FAST        2.6
#define ONTIME_FAST             (BLINK_CYCLE_FAST / 2)

/** cycle time for slow blinking led 1400ms */
#define BLINK_CYCLE_SLOW        18.6
#define ONTIME_SLOW             (BLINK_CYCLE_SLOW / 2)

/** cycle time for flashing led 2000ms */
#define BLINK_CYCLE_FLASH       26.6
#define ONTIME_FLASH			0.5
GPIO_TypeDef* gpio;
typedef enum LED_State {
	LEDstate_OFF = 0,
	LEDstate_ON,
	LEDstate_SLOW,
	LEDstate_FAST,
	LEDstate_SLOW_ALT,
	LEDstate_FAST_ALT,
	LEDstate_ULTRA,
	LEDstate_FLASH,
	LEDstate_undefined
} LED_State;

extern IO_Mapping LED_mapping[LED_undefined];
IO_Mapping LED_mapping[LED_undefined] =
{
                 { GPIO_LED_0, GPIO_NORMAL },
                 { GPIO_LED_1, GPIO_NORMAL },
                 { GPIO_LED_2, GPIO_NORMAL }
};
/* local storage for state of LEDs */
static LED_State LEDs[LED_undefined];

void setGpio(GPIO_TypeDef *GPIOx, uint32_t PinMask)
{
	uint32_t odr = READ_REG(GPIOx->ODR);
	WRITE_REG(GPIOx->BSRR, ((odr & PinMask) << 16u) | (~odr & PinMask));
}

void led_init(void) {
	uint32_t i = 0;

	for (i=0; i< LED_undefined; i++) {
		LEDs[i] = LEDstate_SLOW;
	}

	led_update();
}

void led_update(void)
{
	uint32_t i = 0;


	/* calculate 3 independet cycle tickers for LED signaling */
	if (fastTick >= ONTIME_FAST) {
		fastTick = 0;
	}
	else
	{
		//fastTick++;
	}
	if (slowTick >= BLINK_CYCLE_SLOW) {
		slowTick = 0;
	} else
	{
		//slowTick++;
	}
	if (ultraTick >= BLINK_CYCLE_ULTRA)
	{
		ultraTick = 0;
    }
	else
    {
        //ultraTick++;
    }
	if (flashTick >= BLINK_CYCLE_FLASH) {
		flashTick = 0;
	} else
	{
		//flashTick++;
	}

	/*
	 * enumerate all LEDs and set controlling IO Pin depending on IO Mapping table
	 * we have to consider IO Direction here (normally setting IO to 1 sets LED on
	 */
	for (i=0; i<LED_undefined; i++)
	{
		switch (LEDs[i])
		{
			/* permanent on */
			case LEDstate_ON:
				if(LED_mapping[i].direction  == GPIO_NORMAL)
				{
					HAL_GPIO_WritePin(GPIOB, LED_mapping[i].gpio, SET);
					//gpio_set(LED_mapping[i].gpio);
				}
				else
				{
					HAL_GPIO_WritePin(GPIOB, LED_mapping[i].gpio, RESET);
				}
				break;
			/* permanent off */
			case LEDstate_OFF:
				if(LED_mapping[i].direction == GPIO_NORMAL)
				{
					HAL_GPIO_WritePin(GPIOB, LED_mapping[i].gpio, RESET);
				}
				else
				{
					HAL_GPIO_WritePin(GPIOB, LED_mapping[i].gpio, SET);
				}
				break;
			/* slow blinking ON/OFF 1:1 1,4s */
			case LEDstate_SLOW:
				/* one half is on the other off */
				if (slowTick < ONTIME_SLOW)
				{
					if (LED_mapping[i].direction == GPIO_NORMAL)
					{

						//gpio->BSRR = LED_mapping[i].gpio;
						HAL_GPIO_WritePin(GPIOB, LED_mapping[i].gpio, SET);
						//HAL_GPIO_WritePin(GPIOB, LED_GRN_Pin, RESET);
					} else
					{
						//uint32_t odr=0;
						//gpio.BSRR = (uint32_t)LED_mapping[i].gpio << 16U;
						//odr = gpio->ODR;

						  /* Set selected pins that were at low level, and reset ones that were high */
						//gpio->BSRR = ((odr & LED_mapping[i].gpio) << 16U) | (~odr & LED_mapping[i].gpio);
						HAL_GPIO_WritePin(GPIOB, LED_mapping[i].gpio, RESET);
						//HAL_GPIO_WritePin(GPIOB, LED_GRN_Pin, SET);
					}
				}
				else
				{
					if (LED_mapping[i].direction == GPIO_NORMAL)
					{
						//gpio->BSRR = (uint32_t)LED_mapping[i].gpio << 16U;
						HAL_GPIO_WritePin(GPIOB, LED_mapping[i].gpio, RESET);
						//HAL_GPIO_WritePin(GPIOB, LED_GRN_Pin, SET);
					}
					else
					{
						//gpio->BSRR = LED_mapping[i].gpio;
						HAL_GPIO_WritePin(GPIOB, LED_mapping[i].gpio, SET);
						//HAL_GPIO_WritePin(GPIOB, LED_GRN_Pin, RESET);
					}
				}
				break;
				/* slow blinking OFF/ON 1:1 1,4s */
			case LEDstate_SLOW_ALT:
				if (slowTick < ONTIME_SLOW)
				{
					if (LED_mapping[i].direction == GPIO_NORMAL)
					{

						HAL_GPIO_WritePin(GPIOB, LED_mapping[i].gpio, RESET);
						//HAL_GPIO_WritePin(GPIOB, LED_GRN_Pin, SET);
					}
					else
					{
						HAL_GPIO_WritePin(GPIOB, LED_mapping[i].gpio, SET);
						//HAL_GPIO_WritePin(GPIOB, LED_GRN_Pin, RESET);
					}
				}
				else
				{
					if (LED_mapping[i].direction == GPIO_NORMAL)
					{
						HAL_GPIO_WritePin(GPIOB, LED_mapping[i].gpio, SET);
						//HAL_GPIO_WritePin(GPIOB, LED_GRN_Pin, RESET);
					}
					else
					{	HAL_GPIO_WritePin(GPIOB, LED_mapping[i].gpio, RESET);
						//HAL_GPIO_WritePin(GPIOB, LED_GRN_Pin, SET);
					}
				}
				break;
			/* fast blinking ON/OFF 1:1 200ms */
			case LEDstate_FAST:
				if (fastTick < ONTIME_FLASH)
				{
					if (LED_mapping[i].direction == GPIO_NORMAL)
					{
						HAL_GPIO_WritePin(GPIOB, LED_mapping[i].gpio, SET);
					}
					else
					{
						HAL_GPIO_WritePin(GPIOB, LED_mapping[i].gpio, RESET);
					}
				}
				else
				{
					if (LED_mapping[i].direction == GPIO_NORMAL)
					{
						HAL_GPIO_WritePin(GPIOB, LED_mapping[i].gpio, RESET);
					}
					else
					{
						HAL_GPIO_WritePin(GPIOB, LED_mapping[i].gpio, SET);
					}
				}
				break;

			/* fast blinking OFF/ON 1:1 200ms */
			case LEDstate_FAST_ALT:
				if (fastTick < ONTIME_FAST)
				{
					if (LED_mapping[i].direction == GPIO_NORMAL)
					{
						HAL_GPIO_WritePin(GPIOB, LED_mapping[i].gpio, SET);
					}
					else
					{
						HAL_GPIO_WritePin(GPIOB, LED_mapping[i].gpio, RESET);
					}
				}
				else
				{
					if (LED_mapping[i].direction == GPIO_NORMAL)
					{
						HAL_GPIO_WritePin(GPIOB, LED_mapping[i].gpio, RESET);
					}
					else
					{
						HAL_GPIO_WritePin(GPIOB, LED_mapping[i].gpio, SET);
					}
				}
				break;
				 /* fast blinking OFF/ON 1:1 200ms */
			case LEDstate_ULTRA:
				if (ultraTick < ONTIME_ULTRA)
				{
				    if (LED_mapping[i].direction == GPIO_NORMAL)
				    {
				    	HAL_GPIO_WritePin(GPIOB, LED_mapping[i].gpio, SET);
				    }
				    else
				    {
				    	HAL_GPIO_WritePin(GPIOB, LED_mapping[i].gpio, RESET);
				    }
				}
				else
				{
				    if (LED_mapping[i].direction == GPIO_NORMAL)
				    {
				    	HAL_GPIO_WritePin(GPIOB, LED_mapping[i].gpio, RESET);
				    }
				    else
				    {
				    	HAL_GPIO_WritePin(GPIOB, LED_mapping[i].gpio, SET);
				    }
				}
				break;
				/* flashing 1:40 2s */
				case LEDstate_FLASH:
					if (flashTick < ONTIME_FLASH)
					{
						if (LED_mapping[i].direction == GPIO_NORMAL)
						{
							HAL_GPIO_WritePin(GPIOB, LED_mapping[i].gpio, SET);
							//LL_GPIO_SetOutputPin(GPIOB, LED_mapping[i].gpio);
							//setGpio(GPIOB, LED_mapping[i].gpio);
						}
						else
						{
							HAL_GPIO_WritePin(GPIOB, LED_mapping[i].gpio, RESET);
						}
					}
					else
					{
						if (LED_mapping[i].direction == GPIO_NORMAL) {
							HAL_GPIO_WritePin(GPIOB, LED_mapping[i].gpio, RESET);
						}
						else
						{
							HAL_GPIO_WritePin(GPIOB, LED_mapping[i].gpio, SET);
						}
					}
					break;
			default:
				//ASSERT(false);
				break;
		}
	}
}

void led_setON(const LED_Name LED) {

	//ASSERT(LED < LED_undefined);
	assert_param(LED<LED_undefined);
	LEDs[LED] = LEDstate_ON;
}

void led_setOFF(const LED_Name LED) {

	//ASSERT(LED < LED_undefined);
	assert_param(LED<LED_undefined);
	LEDs[LED] = LEDstate_OFF;
}

void led_setSLOW(const LED_Name LED) {

	assert_param(LED<LED_undefined);
	//ASSERT(LED < LED_undefined);

	LEDs[LED] = LEDstate_SLOW;
}

void led_setFAST(const LED_Name LED) {

	//ASSERT(LED < LED_undefined);
	assert_param(LED<LED_undefined);
	LEDs[LED] = LEDstate_FAST;
}

void led_setSLOWalt(const LED_Name LED) {

	//ASSERT(LED < LED_undefined);
	assert_param(LED<LED_undefined);
	LEDs[LED] = LEDstate_SLOW_ALT;
}

void led_setFASTalt(const LED_Name LED) {

	//ASSERT(LED < LED_undefined);
	assert_param(LED<LED_undefined);
	LEDs[LED] = LEDstate_FAST_ALT;
}

void led_setULTRA(const LED_Name LED) {

 	//ASSERT(LED < LED_undefined);
	assert_param(LED<LED_undefined);
    LEDs[LED] = LEDstate_ULTRA;
}

void led_setFLASH(const LED_Name LED) {

	//ASSERT(LED < LED_undefined);
	assert_param(LED<LED_undefined);
	LEDs[LED] = LEDstate_FLASH;
}


