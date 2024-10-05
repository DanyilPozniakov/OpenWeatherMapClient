CMAKE_MINIMUM_REQUIRED(VERSION 3.29)
project(OpenWeatherMapClient)
set(CMAKE_CXX_STANDARD 23)
include(FetchContent)

add_subdirectory(src libs)
add_subdirectory(examples)



set(CONFIG_FILES
    "config.json"
)
foreach (CONFIG_file ${CONFIG_FILES})
    file(COPY ${CMAKE_SOURCE_DIR}/${CONFIG_file}
            DESTINATION "${CMAKE_BINARY_DIR}/examples"
    )
endforeach ()


