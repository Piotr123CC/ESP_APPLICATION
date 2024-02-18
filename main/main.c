#include <stdio.h>
#include <stdbool.h>
#include <unistd.h>
#include "driver/ledc.h"
#include "rgb_led.h"


void rgb_led_rainbow(void);

void app_main(void)
{
//	rgb_led_pwm_init();
	rgb_led_pwm_init();
	uint8_t red = 0, green = 0, blue = 0;
	printf("r: %u, g: %u, b: %u\n",red, green, blue);
    while (true) {
//      printf("Hello TROK!\n");
//        rgb_led_set_color(red, green, blue);
//        red += 5;
////        green += 10;
//        blue += 15;
//        printf("r: %u, g: %u, b: %u\n",red, green, blue);
//
//        for(int i=0;i<999999;i++);
    	rgb_led_rainbow();

    }
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








