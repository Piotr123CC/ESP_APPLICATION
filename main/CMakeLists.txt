# See the build system documentation in IDF programming guide
# for more information about component CMakeLists.txt files.

idf_component_register(
    SRCS main.c rgb_led.c wifi_app.c http_server.c DHT22.c dht.c  # list the source files of this component
    INCLUDE_DIRS "."        # optional, add here public include directories
	EMBED_FILES webpage/app.js webpage/app.css webpage/favicon.ico webpage/index.html webpage/jquery-3.3.1.min.js
)
