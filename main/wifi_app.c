/*
 * wifi_app.c
 *
 *  Created on: 18 lut 2024
 *      Author: Piotr
 */

#include "freertos/FreeRTOS.h"
#include "freertos/event_groups.h"
#include "freertos/task.h"

#include "esp_err.h"
#include "esp_log.h"
#include "esp_wifi.h"
#include "lwip/netdb.h"

#include "rgb_led.h"
#include "tasks_common.h"
#include "wifi_app.h"


static const char TAG[] = "wifi_app";

static QueueHandle_t wifi_app_queue_handle;

esp_netif_t* esp_netif_sta = NULL;
esp_netif_t* esp_netif_ap = NULL;

BaseType_t wifi_app_send_message(wifi_app_message_e msgID);

static void wifi_app_task(void *pvParameters)
{
	wifi_app_queue_message_t msg;

	wifi_app_event_handler_init();

	wifi_app_default_wifi_init();

	wifi_app_soft_ap_config();

	ESP_ERROR_CHECK(esp_wifi_start());

	wifi_app_send_message(WIFI_APP_MSG_START_HTTP_SERVER);

	for(;;)
	{
		if (xQueueReceive(wifi_app_queue_handle, &msg, portMAX_DELAY))
		{
			switch(msg.msgID)
			{
				case WIFI_APP_MSG_START_HTTP_SERVER:
					ESP_LOGI(TAG, "WIFI_APP_MSG_START_HTTP_SERVER");
//					http_server_start();

					rgb_led_http_server_started();
					break;

				case WIFI_APP_MSG_CONNECTING_FROM_HTTP_SERVER:
					ESP_LOGI(TAG, "WIFI_APP_MSG_CONNECTING_FROM_HTTP_SERVER");
					break;

				case WIFI_APP_MSG_STA_CONNECTED_GOT_IP:
					ESP_LOGI(TAG, "WIFI_APP_MSG_STA_CONNECTED_GOT_IP");
					rgb_led_wifi_connected();
					break;

				default:
					break;

			}
		}
	}
}



void wifi_app_start(void)
{
	ESP_LOGI(TAG, "STARTING WIFI APPLIACTION");

	rgb_led_wifi_app_started();

	esp_log_level_set("wifi", ESP_LOG_NONE);

	wifi_app_queue_handle = xQueueCreate(3, sizeof(wifi_app_queue_message_t));

	xTaskCreatePinnedToCore(&wifi_app_task, "wifi_app_task", WIFI_APP_TASK_STACK_SIZE, NULL, WIFI_APP_TASK_PRIORITY, NULL, WIFI_APP_TASK_CORE_ID);
}
