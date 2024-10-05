
#include <iostream>
#include <exception>
#include "../include/weatherclient.hpp"

WeatherApp::WeatherClient::WeatherClient()
{
    HttpClient = std::make_unique<WeatherApp::NetWork::HttpClient>();
}


std::string WeatherApp::WeatherClient::getWeatherResponseString()
{
    return HttpClient->fetch_weather_data("Odesa");
}
