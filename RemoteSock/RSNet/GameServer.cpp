#include "RSNet.h"
#include <boost/asio.hpp>
#include <iostream>

using namespace boost::asio;

RSNet::GameServer::GameServer(io_context& ctx, uint16_t listenPort) :
	_ctx(ctx), _acceptor(ctx, ip::tcp::endpoint(ip::tcp::v4(), listenPort)),
	_playerCount(1)
{
	
	// initialize map of players, push async listen work to the
	// io queue.
	accept_players();
}

void RSNet::GameServer::accept_players()
{
	// need this socket to establish tcp connections, 
	// it will be copied into the connected_players map
	// GS owns this socket.
	auto socket = std::make_shared<ip::tcp::socket>(_ctx);

	std::cout << "acceptor open: " << _acceptor.is_open() << '\n';
	// socket unique owner ship, we need to call move to capture it in the lambda.
	_acceptor.async_accept(*socket, [this, socket](const boost::system::error_code& ec) mutable
		{
			// note after the capture clause the auto socket var in outside scope becomes null.
			if (!ec)
			{
				// accept connection, move socket to map.
				// todo: enforce unique IP.
				_connected_players.emplace(_playerCount, std::move(*socket));
				std::cout << "Player: " << _playerCount << " accepted." << std::endl;
				_playerCount++;
			}

			if (ec) { std::cout << ec.message() << std::endl;  }

			accept_players();
		});
}

void RSNet::GameServer::run()
{
	_ctx.run();
}

void RSNet::GameServer::broadcast(std::string&& message)
{
	// make_packet<broadcast>(std::string&& message)
	// create the work to be completed, send a packet
	// to ever member of the connected_players map.
	// push the work to the NetOutQueue.
}


// Overload ostream insertion operator so we can easily log packet bodies.

std::ostream& operator<<(std::ostream& os, const RSNet::Packet& p)
{
	os << "Packet length: " << p.body_length << " body: \n";
	os.write(p.body, p.body_length);
	os << "\n";
	return os;
}