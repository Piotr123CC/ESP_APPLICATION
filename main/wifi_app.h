/*
 * wifi_app.h
 *
 *  Created on: 18 lut 2024
 *      Author: Piotr
 */

#ifndef MAIN_WIFI_APP_H_
#define MAIN_WIFI_APP_H_

#include "esp_netif.h"

//WiFi application settings

#define WIFI_APP_SSID 					"ESP32_AP"
#define WIFI_APP_PASSWORD 				"password"
#define WIFI_APP_CHANNEL 				1
#define WIFI_APP_SSID_HIDDEN 	 		0
#define WIFI_APP_MAX_CONNECTIONS  		5
#define WIFI_APP_BEACON_INTERVAL		100
#define WIFI_APP_IP 					"192.168.0.1"
#define WIFI_APP_GATEWAY 				"192.168.0.1"
#define WIFI_APP_NETMASK 				"255.255.255.0"
#define WIFI_APP_BANDWIDTH				WIFI_BW_HT20
#define WIFI_STA_POWER_SAVE				WIFI_PS_NONE
#define	MAX_SSID_LENGTH					32
#define MAX_PASSWORD_LENGTH				64
#define MAX_CONNECTIONS_RETIRES			5


extern esp_netif_t* esp_netif_sta;
extern esp_netif_t* esp_netif_ap;

typedef enum wifi_app_message
{
	WIFI_APP_MSG_START_HTTP_SERVER = 0,
	WIFI_APP_MSG_CONNECTING_FROM_HTTP_SERVER,
	WIFI_APP_MSG_STA_CONNECTED_GOT_IP

}wifi_app_message_e;

typedef struct wifi_app_queue_message
{
	wifi_app_message_e msgID;
}wifi_app_queue_message_t;


/**
 * sends a message to queue
 * @param msgID message ID from tha wifi_app_message_e enum
 * @return pdTRUE if an item was successfully sent to the queue, otherwise pdFalse
 * @note Expand the parameter list based on your requirements e.g. how you've expanded the wifi_app_queue_message_t
 */
BaseType_t wifi_app_send_message(wifi_app_message_e msgID);

/**
 * Starts the WiFi RTOS task
 */
void wifi_app_start(void);

#endif /* MAIN_WIFI_APP_H_ */
