
#include <iostream>
#include <exception>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#include "../include/weatherclient.hpp"

WeatherApp::WeatherClient::WeatherClient()
{
    HttpClient = std::make_unique<WeatherApp::NetWork::HttpClient>();
}


std::string WeatherApp::WeatherClient::get_weather_response_string(const std::string& city)
{
    return HttpClient->fetch_weather_data("Odesa");
}


std::unordered_map<std::string, std::string> WeatherApp::WeatherClient::parse_response(const std::string& answerString)
{
    //temp
    std::set<std::string> keys = { "name", "main.temp", "main.feels_like", "wind.speed" };
    try
    {
        std::stringstream ss(answerString);
        boost::property_tree::ptree pt;
        boost::property_tree::read_json(ss,pt);

        if(auto response_cod = pt.get<std::string>("cod"); response_cod != "200")
        {
            throw std::runtime_error("Error: status code -> " + response_cod
            + "Response body: \n" + answerString);
        }

        std::unordered_map<std::string, std::string> response_data;

        for(const auto& key : keys)
        {
            if(auto property = pt.get_optional<std::string>(key))
            {
                response_data[key] = *property;
            }
            else
            {
                std::cerr << "Property: " << key << " is not found!" << std::endl;
            }
        }
        return response_data;
    }
    catch (const boost::property_tree::ptree_error& ex)
    {
        std::cerr << "Error processing the property tree" << ex.what() << std::endl;
    }
    catch (const std::runtime_error& ex)
    {
         // TODO temp
        std::cerr << ex.what() << std::endl;
    }
    catch (const std::exception& ex)
    {
        std::cerr << ex.what() << std::endl;
    }

    return {};
}

std::unordered_map<std::string, std::string> WeatherApp::WeatherClient::getWeatherDataMap(const std::string& city)
{
    auto response_string = get_weather_response_string(city);
    return parse_response(response_string);
}
