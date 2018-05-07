#pragma once
#include <Arduino.h>

int16_t getIntegerPart(float number);
uint16_t getDecimalPart(float number, uint8_t precision);
uint8_t getNumberLength(int16_t number);
uint8_t getNumberLength(float number, uint8_t precision);