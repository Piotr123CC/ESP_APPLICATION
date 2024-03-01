/*
 * http_server.c
 *
 *  Created on: 26 lut 2024
 *      Author: Piotr
 */


#include "esp_http_server.h"
#include "esp_log.h"
#include "esp_wifi.h"

#include "http_server.h"
#include "tasks_common.h"
#include "wifi_app.h"
static const char TAG[] = "http_server";

static httpd_handle_t http_server_handle = NULL;

extern const uint8_t jquery_3_3_1_min_js_start[]	asm("_binary_jquery_3_3_1_min_js_start");
extern const uint8_t jquery_3_3_1_min_js_end[]		asm("_binary_jquery_3_3_1_min_js_end");
extern const uint8_t index_html_start[]				asm("_binary_index_html_start");
extern const uint8_t index_html_end[]				asm("_binary_index_html_end");
extern const uint8_t app_css_start[]				asm("_binary_app_css_start");
extern const uint8_t app_css_end[]					asm("_binary_app_css_end");
extern const uint8_t app_js_start[]					asm("_binary_app_js_start");
extern const uint8_t app_js_end[]					asm("_binary_app_js_end");
extern const uint8_t favicon_ico_start[]			asm("_binary_favicon_ico_start");
extern const uint8_t favicon_ico_end[]				asm("_binary_favicon_ico_end");

/**
 * Jquery get handler equest when accesing the web page.
 * @param req HTTP request for which the uri needs to be handled
 * @return ESP_OK
*/
static esp_err_t http_server_jquery_handler(httpd_req_t *req)
{
    ESP_LOGI(TAG, "Jquery requested");

    httpd_resp_set_type(req, "appliaction/javascript");
    httpd_resp_send(req, (const char*)jquery_3_3_1_min_js_start, jquery_3_3_1_min_js_end-jquery_3_3_1_min_js_start);
    return ESP_OK;
}


/**
 * sends the index.html page.
 * @param req HTTP request for which the uri needs to be handled
 * @return ESP_OK
*/
static esp_err_t http_server_index_html_handler(httpd_req_t *req)
{
    ESP_LOGI(TAG, "index.html requested");

    httpd_resp_set_type(req, "text/html");
    httpd_resp_send(req, (const char*)index_html_start, index_html_end-index_html_start);
    return ESP_OK;
}


/**
 * app.js get handler equest when accesing the web page.
 * @param req HTTP request for which the uri needs to be handled
 * @return ESP_OK
*/
static esp_err_t http_server_app_js_handler(httpd_req_t *req)
{
    ESP_LOGI(TAG, "app.js requested");

    httpd_resp_set_type(req, "appliaction/javascript");
    httpd_resp_send(req, (const char*)app_js_start, app_js_end - app_js_start);
    return ESP_OK;
}


/**
 * app.css get handler equest when accesing the web page.
 * @param req HTTP request for which the uri needs to be handled
 * @return ESP_OK
*/
static esp_err_t http_server_app_css_handler(httpd_req_t *req)
{
    ESP_LOGI(TAG, "app.css requested");

    httpd_resp_set_type(req, "text/css");
    httpd_resp_send(req, (const char*)app_css_start, app_css_end - app_css_start);
    return ESP_OK;
}


/**
 * sends the .ico (icon) file when accessing the web page.
 * @param req HTTP request for which the uri needs to be handled
 * @return ESP_OK
*/
static esp_err_t http_server_favicon_ico_handler(httpd_req_t *req)
{
    ESP_LOGI(TAG, "Jquery requested");

    httpd_resp_set_type(req, "appliaction/javascript");
    httpd_resp_send(req, (const char*)favicon_ico_start, favicon_ico_end - favicon_ico_start);
    return ESP_OK;
}


static httpd_handle_t http_server_configure(void)
{
    httpd_config_t config = HTTPD_DEFAULT_CONFIG();

    //create http monitor task
    // create message queue

    config.core_id = HTTP_SERVER_TASK_CORE_ID;

    config.task_priority = HTTP_SERVER_TASK_PRIORITY;

    config.stack_size = HTTP_SERVER_TASK_STACK_SIZE;

    config.max_uri_handlers = 20;

    config.recv_wait_timeout = 10;
    config.send_wait_timeout = 10;

    ESP_LOGI(TAG,
            "http_server_configure: Starting server on port: '%d' with task priority '%d'",
            config.server_port,
            config.task_priority);

    if (httpd_start(&http_server_handle, &config) == ESP_OK)
    {
        ESP_LOGI(TAG,"http_server_configure: Registering URI handlers");

        httpd_uri_t jquery_js = {
            .uri ="/jquery-3.3.1.min.js",
            .method = HTTP_GET,
            .handler = http_server_jquery_handler,
            .user_ctx = NULL
        };
        httpd_register_uri_handler(http_server_handle, &jquery_js);

        httpd_uri_t index_html = {
            .uri ="/",
            .method = HTTP_GET,
            .handler = http_server_index_html_handler,
            .user_ctx = NULL
        };
        httpd_register_uri_handler(http_server_handle, &index_html);

        httpd_uri_t app_js = {
            .uri ="/app.js",
            .method = HTTP_GET,
            .handler = http_server_app_js_handler,
            .user_ctx = NULL
        };
        httpd_register_uri_handler(http_server_handle, &app_js);

        httpd_uri_t app_css = {
            .uri ="/app.css",
            .method = HTTP_GET,
            .handler = http_server_app_css_handler,
            .user_ctx = NULL
        };
        httpd_register_uri_handler(http_server_handle, &app_css);

        httpd_uri_t favicon_ico = {
            .uri ="/favicon.ico",
            .method = HTTP_GET,
            .handler = http_server_favicon_ico_handler,
            .user_ctx = NULL
        };
        httpd_register_uri_handler(http_server_handle, &favicon_ico);

        return http_server_handle;
    } 


    return NULL;
}

void http_server_start(void)
{
    if (http_server_handle == NULL)
    {
        http_server_handle = http_server_configure();
    }
}

void http_server_stop(void)
{
    if (http_server_handle)
    {
        httpd_stop(http_server_handle);
        ESP_LOGI(TAG, "http_server_stop: stopping HTTP server");
        http_server_handle = NULL;
    }
}