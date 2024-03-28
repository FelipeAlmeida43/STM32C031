# STM32 RGB LED Control and Sensor Reading

![STM32 Logo](https://img.shields.io/badge/STM32-Development-brightgreen.svg)
![License](https://img.shields.io/badge/license-MIT-blue.svg)

This project showcases an STM32 microcontroller-based application that controls RGB LEDs and interacts with various peripherals, including buttons, timers, and DMA for analog sensor reading.

## Features

- RGB LED Control: The project controls RGB LEDs connected to Pins PB5 (Red), PB4 (Green), and PB3 (Blue), allowing you to create various colors and lighting effects.

- Button with Interrupt: A push button connected to PC13 is configured to trigger an interrupt when pressed, enabling user interaction.

- Timer for LED Toggle: A timer (Timer 1) generates an interrupt every 100 ms, toggling a status LED connected to Pin PA5.

- DMA-Based Potentiometer Reading: The project reads analog data from a potentiometer connected to Pin PA0 using Direct Memory Access (DMA) for efficient data transfer.

## Hardware Requirements

- STM32 Development Board (e.g., STM32F4 Discovery)
- RGB LEDs and Current Limiting Resistors
- Push Button
- Potentiometer
- Jumper Wires

## Software Requirements

- STM32CubeIDE or STM32CubeMX for project development
- STM32 Standard Peripheral Library (SPL) or STM32 HAL Library
- STM32CubeMX for hardware initialization and pin configuration

## Getting Started

1. Clone the repository:
   ```shell
   git clone https://github.com/FelipeAlmeida43/STM32C031.git
