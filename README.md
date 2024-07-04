# Digital_Watch
Digital watch using a 7-segment display for time, oled display for date, with standalone microcontroller ATmega328p configuration. 

## Description
This project displays the time on a TM1637 (a driver for 4-digit 7-segment display modules) and the date, along with a logo, on an OLED (SSD1306) display. Two buttons allow you to adjust the minutes and hours. The core of this project is an ATmega328p microcontroller in a stand-alone configuration on a protoboard, programmed with PlatformIO. The serial configuration is managed through a USB-UART FTDI FT232RL adapter. The time is set using an external RTC DS3231. 
The digital watch is powered by 5V through a voltage regulator (LM7805) with input and output filter capacitors.
## Circuit diagram

## Components Used 
- ATmega328p
- TM1637 7-segment display
- OLED I2C display with SSH1106 Chip (128 x 64 resolution)
- RTC DS3231
- USB-UART FTDI FT232RL adapter
- 2 NO (Normally Open) switches (buttons)
- 3 resistors (10K ohms each)
- 2 ceramic capacitors (20 pF each)
- 1 quartz crystal (16 MHz)
- Jumper wires
- Breadboard
- Protoboard
- Pin Header

## Tools Used
- Soldering iron
- Solder
- Bench power supply
- Multimeter
- Wire cutters and strippers

### Possible Upgrades
- Develop a PCB to replace the current protoboard setup for a more reliable and compact solution.
- Software Enhancements additional features such as date modification and a menu system



