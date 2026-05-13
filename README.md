# Automatic Solar Tracking System

This project is an Arduino Mega 2560 solar tracking system made for a Microprocessors final project. It uses two LDR sensors to compare light levels and moves a servo motor so the solar panel can point toward the stronger light source.

## Hardware Used

- Arduino Mega 2560
- Two LDR sensors
- Servo motor
- LCD 16x2 I2C
- Solar panel
- Resistors and breadboard

## Features

- Automatic light tracking
- Servo movement based on LDR readings
- Solar panel voltage monitoring
- Irradiance estimation
- Real-time LCD display

## Main Libraries

- Wire.h
- LiquidCrystal_I2C.h
- Servo.h

## Code Overview

The code starts by initializing the LCD, servo motor, and Serial Monitor.

When the system turns on, the LDR sensors are calibrated. The program reads both LDRs several times and calculates an adjustment so both sensors are closer in value under the same light.

In the main loop, the Arduino reads LDR1, LDR2, and the solar panel voltage using A0, A1, and A2.

The panel voltage is calculated from the Arduino ADC reading. The code also estimates light level from the average LDR reading and then calculates irradiance using lux / 120.

The program compares both LDR readings. If one side has more light than the other, the servo moves slowly toward that side. If both readings are close for 10 seconds, the servo returns to the center position.

The LCD shows the panel voltage, irradiance, and servo position.

## Repository Contents

- Automatic_Solar_Tracking_System.ino → Main Arduino source code

## Authors

Omar Ramos, Victor Blanco, and Edgar Colón
