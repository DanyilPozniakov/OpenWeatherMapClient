#include <iostream>
#include "weatherclient.hpp"

int main()
{
    WeatherApp::WeatherClient weather;
    auto data = weather.getWeatherResponseString();
    std::cout << data << std::endl;
}
