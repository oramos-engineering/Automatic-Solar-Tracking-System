# Automatic Solar Tracking System

Arduino-based automatic solar tracking system using LDR sensors, servo motor control, LCD I2C display, and irradiance estimation.

## Hardware Used

- Arduino Mega 2560
- LDR sensors
- Servo motor
- LCD 16x2 I2C
- Solar panel
- Resistors and breadboard

## Features

- Automatic solar tracking
- Servo positioning based on LDR readings
- Voltage monitoring
- Irradiance estimation
- LCD real-time display

## Main Libraries

- Wire.h
- LiquidCrystal_I2C.h
- Servo.h

## Code Overview

The Arduino code initializes the LCD, servo motor, and serial communication in setup().

At startup, the calibrarLDR() function reads both LDR sensors multiple times and calculates an adjustment value. This helps compensate if one LDR gives a higher reading than the other under the same light.

In loop(), the program reads LDR1, LDR2, and the solar panel voltage using analog input pins A0, A1, and A2.

The code calculates the solar panel voltage using the Arduino ADC reading. It also estimates illuminance from the average LDR reading and then estimates irradiance using lux / 120.

The program compares the difference between both LDR readings. If the difference is greater than the tolerance value, the servo moves slowly toward the stronger light source. If the readings are similar for 10 seconds, the servo returns to the center position.

The LCD displays panel voltage, irradiance, and servo position in real time.

## Repository Contents

- Automatic_Solar_Tracking_System.ino → Main Arduino source code

## Authors

Omar Ramos, Victor Blanco, and Edgar Colón
