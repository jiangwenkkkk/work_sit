set(APP_NAME "Inspect")

set(LOCAL_SRCS main.cpp
        )
include_directories(/usr/local/include)

add_executable(${APP_NAME} ${LOCAL_SRCS})
target_link_libraries(
        ${APP_NAME}
#        PocoUtil
#        PocoFundation
#        mysqlclient
        )