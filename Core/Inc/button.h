/*
 * button.h
 *
 *  Created on: Sep 30, 2023
 *      Author: Felipe
 */

#ifndef INC_BUTTON_H_
#define INC_BUTTON_H_
#include <stdbool.h>
#include "main.h"
#define HIGH 1
#define LOW 0
enum INPUT_CHANNELS{
  ID_0,
  ID_1,
  ID_2,
  NUMBER_OF_INPUT_CHANNELS
};



struct DigitalChannels {

  const unsigned int pin;
  volatile long  count;
  volatile long  debounce;
  volatile long  debounce_target;
  volatile bool last_state;
  volatile bool current_state;
  void* id;

};
extern struct DigitalChannels Channel_0;
extern struct DigitalChannels Channel_1;

#endif /* INC_BUTTON_H_ */
