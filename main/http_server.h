/*
 * http_server.h
 *
 *  Created on: 26 lut 2024
 *      Author: Piotr
 */

#ifndef MAIN_HTTP_SERVER_H_
#define MAIN_HTTP_SERVER_H_

typedef enum http_server_message
{
	HTTP_MSG_WIFI_CONNECT_INIT = 0,
	HTTP_MSG_WIFI_CONNECT_SUCCESS,
	HTTP_MSG_WIFI_CONNECT_FAIL,
	HTTP_MSG_OTA_UPDATE_SUCCESSFUL,
	HTTP_MSG_OTA_UPDATE_FAILED,
	HTTP_MSG_OTA_UPDATE_INITIALIZED,

}http_server_message_e;

typedef struct http_server_queue_message
{
	http_server_message_e msgID;
}http_server_queue_message_t;



#endif /* MAIN_HTTP_SERVER_H_ */