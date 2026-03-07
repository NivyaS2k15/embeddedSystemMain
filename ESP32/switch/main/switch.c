#include <stdio.h>
#include "driver/gpio.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#define LED_GPIO     2   // LED pin
#define SWITCH_GPIO  4   // Switch pin (example: GPIO4)

void app_main(void)
{
    // Configure LED pin as output
    gpio_reset_pin(LED_GPIO);
    gpio_set_direction(LED_GPIO, GPIO_MODE_OUTPUT);

    // Configure switch pin as input with pull-up
    gpio_reset_pin(SWITCH_GPIO);
    gpio_set_direction(SWITCH_GPIO, GPIO_MODE_INPUT);
    gpio_set_pull_mode(SWITCH_GPIO, GPIO_PULLUP_ONLY);

    while (1)
    {
        // Read switch state
        int switch_state = gpio_get_level(SWITCH_GPIO);

        if (switch_state == 0) {  
            // Button pressed (active low)
            gpio_set_level(LED_GPIO, 1);  // Turn LED ON
        } else {
            gpio_set_level(LED_GPIO, 0);  // Turn LED OFF
        }

        vTaskDelay(50 / portTICK_PERIOD_MS); // Small debounce delay
    }
}