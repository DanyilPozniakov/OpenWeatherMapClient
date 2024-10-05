
find_package(OpenSSL REQUIRED)
find_package(Boost REQUIRED)
add_library(OpenWeatherMapClient STATIC weatherclient.cpp httpclient.cpp)
target_include_directories(OpenWeatherMapClient PUBLIC ../include)
target_link_libraries(OpenWeatherMapClient PUBLIC
        Boost::boost
        OpenSSL::SSL
        OpenSSL::Crypto
)


