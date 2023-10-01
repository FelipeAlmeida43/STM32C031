/*
 * led.h
 *
 *  Created on: 15.06.2012
 *      Author: jqua
 */

#ifndef LED_H_
#define LED_H_


#include "main.h"
#include "led_definition.h"
extern uint32_t fastTick;
extern uint32_t ultraTick;
extern uint32_t slowTick;
extern uint32_t flashTick;
/*
#define GPIO_LED_0 (uint16_t)0x0080
#define GPIO_LED_1 (uint16_t)0x0100
#define GPIO_LED_2 (uint16_t)0x0200
*/
//#include "system\led_definition.h"
typedef enum LEDnumber{
	GPIO_LED_0  = (uint16_t)0x0008,
	GPIO_LED_1  = (uint16_t)0x0010,
	GPIO_LED_2  = (uint16_t)0x0020

}LEDnumber;
/*
typedef enum GPIOnumber {

	GPIO_ASI_DSR =0,
	GPIO_ASI_PST,
	GPIO_VALVE_1,
	GPIO_VALVE_1_INHIBIT,
	GPIO_VALVE_2,
	GPIO_VALVE_2_INHIBIT,
	GPIO_VALVE_3,
	GPIO_VALVE_3_INHIBIT,
	GPIO_PLC_OUT_0,
	GPIO_PLC_OUT_1,
	GPIO_PLC_OUT_2,
	GPIO_PLC_OUT_4,
	GPIO_PLC_IN_4,
	GPIO_PLC_OUT_5,
	GPIO_PLC_OUT_6,
	GPIO_PLC_OUT_7,
	GPIO_PLC_IN_0,
	GPIO_PLC_IN_1,
	GPIO_PLC_IN_2,
	GPIO_PLC_IN_3,
	GPIO_TEACH_BUTTON,
	GPIO_PLC_OUT_3,					//EXT_SENSOR
	//GPIO_AD_STATUS,
	GPIO_POSITION_FAULT,
	GPIO_FID,						//GPIO_Peripherie_FAULT
	GPIO_INVALID
} GPIOnumber
*/
/** logic for real gpio pins  */
typedef enum IODirection {
       GPIO_NORMAL = 0,
       GPIO_INVERS,
} IODirection;

/*! Structure for mapping valves to real gpio pins */
typedef struct IO_Mapping {
         LEDnumber  gpio;          //!> Number of gpio-Pin
         IODirection direction;     //!< IO-Direction of gpio-Pin
} IO_Mapping;


/*! mapping has to be done by application */
/*! mapping from LED name and gpio-Pin direction to GPIO connection */

//extern IO_Mapping LED_mapping[];

/**
 *  Initilzation of all LED states
 */
void led_init(void);

/**
  * \param
  *	\return
  *
  *	\brief  Refresh physical LED state according to inner state
  *
  *	\details MODUL:       void led_update(void)
  *	\remarks updates Refresh physical LED state according to inner state
  *	<br>
  *
  *	<TABLE>
  *		<tr>
  *    	<th>	VERSION</th>
  *    	<th>	AENDERUNG</th>
  *			<th>	Autor</th>
  *		</tr><tr>
  *     	<td>	1.0</td>
  *     	<td>	Urversion</td>
  *			<th>	J�rg Quas Festo</th>
  *		</tr>
  *		</tr><tr>
  *     	<td>	1.1</td>
  *     	<td>	LED Pin Logic um , invers und normal, erweitert</td>
  *			<th>	Udo Walden Festo</th>
  *		</tr>
  *	</TABLE>
  */
/**
 * Refresh physical LED state according to inner state
 */
void led_update(void);



void led_setON(const LED_Name LED);



void led_setOFF(const LED_Name LED);




void led_setSLOW(const LED_Name LED);




void led_setSLOWalt(const LED_Name LED);





void led_setSLOWalt(const LED_Name LED);





void led_setFAST(const LED_Name LED);





void led_setFASTalt(const LED_Name LED);




void led_setULTRA(const LED_Name LED);




void led_setFLASH(const LED_Name LED);

#endif /* LED_H_ */
