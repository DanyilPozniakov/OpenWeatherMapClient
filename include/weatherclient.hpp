#ifndef WEATHERCLIENT_H
#define WEATHERCLIENT_H
#include <string>
#include <set>
#include "httpclient.hpp"


namespace WeatherApp
{
class WeatherClient
{
    std::unique_ptr<WeatherApp::NetWork::HttpClient> HttpClient;

    std::unordered_map<std::string,std::string> parse_response(const std::string& answer);
    std::string get_weather_response_string(const std::string& city);

public:
    WeatherClient();

    std::unordered_map<std::string, std::string> getWeatherDataMap(const std::string& city);

};


} //namespace WeatherApp

#endif // WEATHERCLIENT_H
