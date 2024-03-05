#include <stdio.h>
#include <stdbool.h>
#include <unistd.h>
#include "driver/ledc.h"
#include "rgb_led.h"
#include "nvs_flash.h"
#include "wifi_app.h"
#include "nvs.h"
#include "driver/uart.h"
#include "driver/gpio.h"
void rgb_led_rainbow(void);

void app_main(void)
{
//	rgb_led_pwm_init();
	esp_err_t ret = nvs_flash_init();

	if (ret == ESP_ERR_NVS_NO_FREE_PAGES || ret == ESP_ERR_NVS_NEW_VERSION_FOUND )
	{
		ESP_ERROR_CHECK(nvs_flash_erase());
		ret = nvs_flash_init();
	}
	ESP_ERROR_CHECK(ret);
    wifi_app_start();
}



void rgb_led_rainbow(void)
{

	rgb_led_set_color(148, 0, 211);
	for(int i=0;i<9999999;i++);

	rgb_led_set_color(75, 0, 130);
	for(int i=0;i<9999999;i++);


	rgb_led_set_color(0, 0, 255);
	for(int i=0;i<9999999;i++);


	rgb_led_set_color(0, 255, 0);
	for(int i=0;i<9999999;i++);

	rgb_led_set_color(255, 255, 0);
	for(int i=0;i<9999999;i++);

	rgb_led_set_color(255, 127, 0);
	for(int i=0;i<9999999;i++);

	rgb_led_set_color(255, 0 , 0);
	for(int i=0;i<9999999;i++);
}








