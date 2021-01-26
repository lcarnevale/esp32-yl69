/*
 * ESP32 Soil Moisture Sensor YL-69 or HL-69 Driver
 * Copyright 2021, Lorenzo Carnevale <lcarnevale@unime.it>
 */

#include "freertos/FreeRTOS.h"

#define DEFAULT_VREF 1100 //Use adc2_vref_to_gpio() to obtain a better estimate
#define NO_OF_SAMPLES 64 //Multisampling

#define VALUE_MAX 4095 // Max ADV value of soil mosture

void yl69_setup();
uint32_t yl69_read();
uint32_t yl69_normalization(uint32_t value_t);