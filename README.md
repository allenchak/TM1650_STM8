What is it?
===========

**TM1650_STM8** is a library for the [Arduino](http://arduino.cc/) to interface with Seven Segment Display based on the
TM1650 controller or compatibles (FD650B). This library support for STM8s under I2C interface.
Due to the Flash memory size limitation, it does **NOT** support input features (keypress scan).

This is a modified version of the [Mozz_TM1650 library](https://github.com/mozgy/Mozz_TM1650) written by [Mario Mikočević](https://github.com/mozgy). 
It is ported from C++ to C syntax and is meant to be used with the sduino environment for the STM8.

This library is meant to have a minimal memory footprint. 

![FD650_Front.jpg](https://raw.githubusercontent.com/allenchak/TM1650_STM8/master/images/FD650_Front.jpg)

![FD650_Back.jpg](https://raw.githubusercontent.com/allenchak/TM1650_STM8/master/images/FD650_Back.jpg)

Installation
============

Download the zip file. Then extract and copy to **Sketch Location** (You could check it from **Arduino Preferences**), usaually could be: **Documents\Arduino\hardware\sduino\stm8\libraries**

![Arduino IDE](https://raw.githubusercontent.com/allenchak/TM1650_STM8/master/images/screenshot-01.png)

How it Works
============

To use this library, you must first connect your Display to the proper pins on the STM8s.
The connections would be the following:

Display Pin  | STM8 Pin
-------------|------------
V / VCC      | +3.3V Pin / +5V
C / SCL      | PD4
D / SDA      | PB5
G / GND      | Ground Pin


Demo video
============
[![TM1650 / FD650B](https://img.youtube.com/vi/BmOw3vWxCEU/0.jpg)](https://www.youtube.com/watch?v=BmOw3vWxCEU "TM1650 / FD650B")


Others
==============

The library allows to reduce the extra 67 bytes sketch size, defined by an macro variable `TM1650_MEMORY_SAVER` in file `TM1650_STM8.h`.
