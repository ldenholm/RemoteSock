#include "RSNet.h"
#include <boost/asio.hpp>

using boost::asio;

RSNet::GameServer(io_context& ctx) : _ctx(ctx), _listenPort(listenPort)
{
	_acceptor = ip::tcp::endpoint(ip::tcp::v4(), listenPort));
	// initialize map of players, push async listen work to the
	// io queue.

}