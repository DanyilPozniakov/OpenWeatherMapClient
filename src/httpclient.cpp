#include <iostream>
#include <exception>
#include <boost/property_tree/json_parser.hpp>
#include <boost/property_tree/ptree.hpp>
#include "httpclient.hpp"

//temp
#include <filesystem>

//if one of the parameters is empty, it returns false
bool WeatherApp::NetWork::ConnectionSetting::isValid() const noexcept
{
    return !(key.empty() || host.empty() || port.empty());
}


void WeatherApp::NetWork::HttpClient::read_config()
{
    try
    {
        boost::property_tree::ptree pt;
        boost::property_tree::read_json("config.json",pt);
        if(pt.empty())
        {
            throw boost::property_tree::ptree_error("!!!");
        }
        _connectionSetting.key     = pt.get<std::string>("key");
        _connectionSetting.host    = pt.get<std::string>("host");
        _connectionSetting.port    = pt.get<std::string>("port");
    }

    catch(const boost::property_tree::json_parser_error& ex)
    {
        std::cerr << "Error reading the configuration file: " << ex.what() << std::endl;
    }
    catch(const boost::property_tree::ptree_error& ex)
    {
        std::cerr << "Error processing the property tree" << ex.what() << std::endl;
    }
    catch (const std::exception& ex)
    {
        std::cerr << "An unexpected error occurred: " << ex.what() << std::endl;
    }
    catch (...)
    {
        std::cerr << "unknown exception!" << std::endl;
    }
}


WeatherApp::NetWork::HttpClient::HttpClient() :
    _ssl_context(ssl::context::sslv23),
    _ssl_socket(_io_service,_ssl_context),
    _resolver(_io_service)
{
    read_config();
}


void WeatherApp::NetWork::HttpClient::connect()
{
    if(!_connectionSetting.isValid())
    {
        std::cerr << "Invalid connection setting." << std::endl;
        return;
    }
    try
    {
        //connection
        boost::asio::ip::tcp::resolver::query query(_connectionSetting.host, _connectionSetting.port);
        boost::asio::ip::tcp::resolver::iterator endpoint  = _resolver.resolve(query);
        boost::asio::connect(_ssl_socket.lowest_layer(),endpoint);
        _ssl_socket.handshake(boost::asio::ssl::stream_base::client);

        //log
        std::cout << "Successfully connected to " << _connectionSetting.host
                  << ": " << _connectionSetting.port << std::endl;

    }
    catch(const boost::system::system_error& ex)
    {
        std::cerr << "Connection error: " << ex.what() << std::endl;
    }
}

void WeatherApp::NetWork::HttpClient::create_request(const std::string& city, const std::string& token)
{
    std::string request_string = "/data/2.5/weather?q=" + city + "&appid="+ token + "&units=metric";
    boost::beast::http::request<boost::beast::http::string_body> request (boost::beast::http::verb::get,
                                                                          request_string,
                                                                          11);
    request.set(boost::beast::http::field::host, _connectionSetting.host);
    request.set(boost::beast::http::field::user_agent, BOOST_BEAST_VERSION_STRING);
    send_request(request);
}

void WeatherApp::NetWork::HttpClient::send_request(const http::request<http::string_body> &request)
{
    try
    {
        boost::beast::http::write(_ssl_socket,request);

    }
    catch (const boost::system::system_error& ex)
    {
        std::cerr << "Error sending request" << ex.what() << std::endl;
    }
}

boost::beast::http::response<boost::beast::http::dynamic_body> WeatherApp::NetWork::HttpClient::receive_response()
{
    boost::beast::flat_buffer buffer;
    boost::beast::http::response<boost::beast::http::dynamic_body> response;
    boost::beast::http::read(_ssl_socket,buffer,response);
    return response;
}

std::string WeatherApp::NetWork::HttpClient::fetch_weather_data(const std::string city)
{
    try
    {
        connect();
        create_request(city,_connectionSetting.key);
        auto response = receive_response();
        return boost::beast::buffers_to_string(response.body().data());
    }
    catch (const std::exception& ex)
    {
        std::cerr << "Error fetching weather data: " << ex.what() << std::endl;
        return {};
    }

}


