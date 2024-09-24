
find_package(Boost REQUIRED)
add_library(OpenWeatherMapClient STATIC WeatherClient.cpp)
target_link_libraries(OpenWeatherMapClient PUBLIC Boost::boost)


