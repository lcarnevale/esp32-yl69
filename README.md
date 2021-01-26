# ESP32 Soil Moisture Sensor YL-69 or HL-69 Driver

This project containes the ESP-IDF driver both for the YL-69 and HL-69 soil moisture sensor. This sensor outputs voltage value that changes accordingly to water content in the soil. Specifically, when the soil is:
- **wet** the output voltage decreases;
- **dry** the output voltage increases.


## How to Use it
There are few steps to follow for running this component. Take a look at the list below.

1. First of all, clone this repository or download latest release [here]()

2. Set up the esp32-yl69 component into the *requires* of your *CMakeLists.txt*
```C
//CMakeLists.txt
...
set(COMPONENT_REQUIRES esp32-yl69)
...
```

3. Include the header file within your main application
```C
//main.c
...
#include "yl69.h"
...
```

4. Initialize the driver with the following function
```C
//main.c
void setup() {
    yl69_setup(ADC_CHANNEL_6);
}
```

5. And run the task as follow
```C
//main.c
static void yl69_task(void *arg) {
    char yl69_buffer[1024];

    while(is_running) {
        uint32_t adc_reading = yl69_read();
        uint32_t adc_percentage = yl69_normalization(adc_reading);
        snprintf(yl69_buffer, sizeof(yl69_buffer), "{\"soil_mosture\": %d}", adc_percentage);
        printf("%s\n", yl69_buffer);

        vTaskDelay(1000 / portTICK_PERIOD_MS);
    }
    
    vTaskDelete(NULL); 
}

void loop() {
    xTaskCreate(yl69_task, "yl69_task", 4*1024, NULL, 1, NULL);
}
```