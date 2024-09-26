#include <iostream>
#include <exception>
#include <boost/property_tree/json_parser.hpp>
#include <boost/property_tree/ptree.hpp>
#include "../include/WeatherClient.h"

//if one of the parameters is empty, it returns false
bool ConnectionSetting::isValid() const noexcept
{
    return !(_key.empty() || _host.empty() || _port.empty());
}

void Client::read_config()
{
    try
    {
        boost::property_tree::ptree pt;
        boost::property_tree::read_json("config.json",pt);

        _connectionSetting._key = pt.get<std::string>("key");
        _connectionSetting._key = pt.get<std::string>("host");
        _connectionSetting._key = pt.get<std::string>("port");
    }
    catch(const boost::property_tree::json_parser_error& ex)
    {
        std::cerr << "Error reading the configuration file: " << ex.what() << std::endl;
    }
    catch(const boost::property_tree::ptree_error& ex)
    {
        std::cerr << "Error processing the property tree" << ex.what() << std::endl;
    }
}


Client::Client() :
    _ssl_context(ssl::context::sslv23),
    _ssl_socket(_io_service,_ssl_context),
    _resolver(_io_service)
{
    read_config();
}
void Client::connect()
{

}

