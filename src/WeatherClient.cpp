
#include <iostream>
#include <exception>
#include <boost/property_tree/json_parser.hpp>
#include <boost/property_tree/ptree.hpp>
#include "../include/WeatherClient.h"

void TCPClient::read_config()
{
    try
    {
        boost::property_tree::ptree pt;
        boost::property_tree::read_json("config.json",pt);

        _key = pt.get<std::string>("key");
        _host = pt.get<std::string>("host");
        _port = pt.get<std::string>("port");
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

TCPClient::TCPClient() :
    _socket(_io_context),
    _resolver(_io_context)
{
    read_config();
}
