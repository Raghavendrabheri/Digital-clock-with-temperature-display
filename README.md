Digital Clock with Keypad Menu and Temperature Display
This project implements a digital clock on an embedded system using the LPC2148 microcontroller. The system features a keypad-based menu to set the time, date, and day. It also includes an ADC module to read the temperature using an LM35 temperature sensor and display it on the LCD.

Features
Real-Time Clock (RTC): Displays current time, date, and day.
Keypad Menu: Allows user to set time, date, and day via a keypad interface.
Temperature Display: Reads and displays temperature from the LM35 sensor.
Interrupts: External interrupt triggers the keypad menu for easy navigation.
Hardware Used
Microcontroller: LPC2148
LCD: 16x2 Character LCD
Keypad: 4x4 Matrix Keypad
Temperature Sensor: LM35 (Analog Temperature Sensor)
External Interrupt: Used to trigger the keypad menu
Software Libraries
LPC21xx.h: Library for LPC2148 microcontroller registers and configuration.
delay.h: Delay functions for controlling the timing of actions.
kpm.h / kpm_defines.h: Keypad matrix scanning.
lcd.h / lcd_defines.h: LCD control functions for displaying time, date, and temperature.
Project Structure
main.c: Main source file where the program logic is implemented, including the display of time, date, day, and temperature.
delay.h: Header file containing delay function declarations.
kpm.h: Header file for keypad interface functions.
lcd.h: Header file containing LCD control functions.
Pin Configuration
ADC Pin: Used to read the temperature from the LM35 sensor.
External Interrupt Pin: Triggers the keypad menu for setting the time, date, and day.
Keypad Menu
The keypad interface allows the user to select options and modify settings. The available options are:

Set Time
Set Date
Set Day
Controls:

+ to navigate up through options.
- to navigate down through options.
1 to set time.
2 to set date.
3 to set the day.
C to exit the menu.
How to Run
Clone the repository to your local machine:
bash
Copy
Edit
git clone https://github.com/yourusername/digital-clock-lpc2148.git
Open the project in your preferred IDE (such as KEIL uVision or MPLAB X).
Compile and flash the firmware to your LPC2148-based development board.
Connect the keypad and temperature sensor to the respective GPIO pins.
Power on the system and interact with the keypad to configure the time, date, and day.
