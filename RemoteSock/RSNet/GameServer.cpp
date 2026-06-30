#include "RSNet.h"
#include <boost/asio.hpp>
#include <iostream>

using namespace boost::asio;

RSNet::GameServer::GameServer(io_context& ctx, uint16_t listenPort) : 
	_ctx(ctx), _acceptor(ctx, ip::tcp::endpoint(ip::tcp::v4(), listenPort))
{
	
	// initialize map of players, push async listen work to the
	// io queue.

}

// Overload ostream insertion operator so we can easily log packet bodies.

std::ostream& operator<<(std::ostream& os, const RSNet::Packet& p)
{
	os << "Packet length: " << p.body_length << " body: \n";
	os.write(p.body, p.body_length);
	os << "\n";
	return os;
}