/*
 * ESP32 Soil Moisture Sensor YL-69 or HL-69 Driver
 * Copyright 2021, Lorenzo Carnevale <lcarnevale@unime.it>
 */

#include "yl69.h"

#include "driver/gpio.h"
#include "driver/adc.h"

#include "esp_adc_cal.h"


static adc1_channel_t channel;
static esp_adc_cal_characteristics_t *adc_chars;

static const adc_unit_t unit = ADC_UNIT_1;
static const adc_atten_t attenuation = ADC_ATTEN_DB_11;


void yl69_setup(adc1_channel_t _channel) {
    channel = _channel;
    //Configure ADC
    adc1_config_width(ADC_WIDTH_BIT_12);
    adc1_config_channel_atten(channel, attenuation);
    //Characterize ADC
    adc_chars = calloc(1, sizeof(esp_adc_cal_characteristics_t));
    esp_adc_cal_characterize(unit, attenuation, ADC_WIDTH_BIT_12, DEFAULT_VREF, adc_chars);
}

uint32_t yl69_read() {
    uint32_t adc_reading = 0;
    //Multisampling
    for (int i = 0; i < NO_OF_SAMPLES; i++) {
        adc_reading += adc1_get_raw((adc1_channel_t)channel);
    }
    adc_reading /= NO_OF_SAMPLES;
    //Convert adc_reading to voltage in mV
    // uint32_t voltage = esp_adc_cal_raw_to_voltage(adc_reading, adc_chars);
    return adc_reading;
}

uint32_t yl69_normalization(uint32_t value_t) {
    return (value_t * 100) / VALUE_MAX;
}