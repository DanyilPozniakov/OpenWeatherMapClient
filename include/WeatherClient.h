#include <boost/asio.hpp>
#include <string>

namespace
{
class HttpClient
{
private:
    boost::asio::io_context         _io_context;
    boost::asio::ip::tcp::socket    _socket;
    boost::asio::ip::tcp::resolver  _resolver;

    std::string _key;
    std::string _host;
    std::string _port;

};
}



class WeatherClient
{

};
