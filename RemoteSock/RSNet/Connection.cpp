#include "RSNet.h"
#include <boost/asio.hpp>
#include <iostream>
#include <queue>

using namespace boost::asio;

RSNet::Connection::Connection(ip::tcp::socket socket) : _socket(std::move(socket))
{
	_writing = false;
}