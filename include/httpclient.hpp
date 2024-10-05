#ifndef CLIENT_H
#define CLIENT_H

#include <boost/asio.hpp>
#include <boost/asio/ssl.hpp>
#include <boost/beast.hpp>
#include <string>

using namespace boost::asio;
using namespace boost::asio::ssl;
namespace http = boost::beast::http;




namespace WeatherApp::NetWork
{

struct ConnectionSetting
{
    std::string key;
    std::string host;
    std::string port;

    bool isValid() const noexcept;
};

class HttpClient
{
private:
    io_service                      _io_service;
    ssl::context                    _ssl_context;
    ssl::stream<ip::tcp::socket>    _ssl_socket;
    ip::tcp::resolver               _resolver;

    ConnectionSetting _connectionSetting;

    void connect();
    void read_config();
    void create_request(const std::string& city, const std::string& token);
    void send_request(const boost::beast::http::request<http::string_body>& request);
    boost::beast::http::response<boost::beast::http::dynamic_body> receive_response();

public:
    HttpClient();
    std::string fetch_weather_data(const std::string city);

};

} // namespace WeatherApp::NetWork
// namespace WeatherApp.



#endif //CLIENT_H
