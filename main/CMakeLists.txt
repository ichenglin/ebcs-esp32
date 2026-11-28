file(GLOB_RECURSE APP_SOURCES "src/*.c")
list(FILTER APP_SOURCES EXCLUDE REGEX "/roles/")

if(CONFIG_BOARD_ROLE_DEVICE)
    list(APPEND APP_SOURCES "src/roles/device.c")
elseif(CONFIG_BOARD_ROLE_STATION)
    list(APPEND APP_SOURCES "src/roles/station.c")
elseif(CONFIG_BOARD_ROLE_SANDBOX)
    list(APPEND APP_SOURCES "src/roles/sandbox.c")
endif()

idf_component_register(
    SRCS ${APP_SOURCES}
    INCLUDE_DIRS "include"
)
