#include "RSNet.h"
#include <boost/asio.hpp>
#include <iostream>
#include <queue>

using namespace boost::asio;

RSNet::Connection::Connection(io_context& ctx) : _socket(ctx), _writing(false)
{
	// Connection is the owner of its socket.
}

boost::asio::ip::tcp::socket& RSNet::Connection::socket()
{
	return _socket;
}