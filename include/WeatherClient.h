#pragma once
#include <boost/asio.hpp>
#include <boost/asio/ssl.hpp>
#include <string>

using namespace boost::asio;
using namespace boost::asio::ssl;



namespace
{
struct ConnectionSetting
{
    std::string _key;
    std::string _host;
    std::string _port;

    bool isValid() const noexcept;
};


class Client
{
private:
    io_service                      _io_service;
    ssl::context                    _ssl_context;
    ssl::stream<ip::tcp::socket>    _ssl_socket;
    ip::tcp::resolver               _resolver;

    ConnectionSetting _connectionSetting;

    void read_config();
    void connect();

public:
    Client();




};
}



class WeatherClient
{

};
