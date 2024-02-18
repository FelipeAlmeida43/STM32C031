/*---------------------------------------------------------------------*
 * @section License
 * <b>(C) Copyright 2012 Festo AG & CO.KG., http://www.Festo.com</b>
 ***********************************************************************
 *                                                                     *
 *       project: VSK_AS3                                      *
 *   module name: led_definition.h                                         *
 *        author: J�rg Quas                                            *
 *          date: 19.10.2012                                              *
 *                                                                     *
 */
/*! \file
 *  \brief  header file for led_definition.c
 *
 */
/*                                                                     *
 *---------------------------------------------------------------------*/
#ifndef LED_DEFINITION_H_
#define LED_DEFINITION_H_

/*! LED names and symbolic addresses */
typedef enum LED_Name {
         LED_GREEN = 0,
		 LED_RED,
         LED_YELLOW
         //LED_undefined
} LED_Name;
#define LED_undefined 3
#endif /* LED_DEFINITION_H_ */
