/*
 * ESP32 Soil Moisture Sensor YL-69 or HL-69 API
 * Copyright (c) 2021, Lorenzo Carnevale <lcarnevale@unime.it>
 */

#include "freertos/FreeRTOS.h"

#define DEFAULT_VREF 1100 //Use adc2_vref_to_gpio() to obtain a better estimate
#define NO_OF_SAMPLES 64 //Multisampling

void yl69_setup();
uint32_t yl69_read();