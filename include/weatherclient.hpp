#ifndef WEATHERCLIENT_H
#define WEATHERCLIENT_H
#include <string>
#include "httpclient.hpp"


namespace WeatherApp
{
class WeatherClient
{
    std::unique_ptr<WeatherApp::NetWork::HttpClient> HttpClient;

public:
    WeatherClient();
    std::string getWeatherResponseString();

};


}

#endif // WEATHERCLIENT_H
