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

```cpp
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <Servo.h>
