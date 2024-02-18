/*
 * rgb_led.h
 *
 *  Created on: 17 lut 2024
 *      Author: Piotr
 */

#ifndef MAIN_RGB_LED_H_
#define MAIN_RGB_LED_H_

#define RGB_LED_CHANNEL_NUM 3

#define RGB_LED_RED_GPIO 23
#define RGB_LED_GREEN_GPIO 19
#define RGB_LED_BLUE_GPIO 17


typedef struct{
	int channel;
	int gpio;
	int mode;
	int timer_index;

}ledc_info_t;

void rgb_led_pwm_init(void);
void rgb_led_set_color(uint8_t red, uint8_t green, uint8_t blue);
void rgb_led_wifi_app_started(void);
void rgb_led_http_server_started(void);
void rgb_led_wifi_connected(void);


#endif /* MAIN_RGB_LED_H_ */
