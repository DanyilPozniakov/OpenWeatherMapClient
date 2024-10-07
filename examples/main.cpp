#include <iostream>
#include "weatherclient.hpp"

int main()
{
    WeatherApp::WeatherClient weather;
    auto data = weather.getWeatherDataMap("Odesa");
    for(const auto& item : data)
    {
        std::cout << item.first << ":\t\t" << item.second << std::endl;
    }
}
