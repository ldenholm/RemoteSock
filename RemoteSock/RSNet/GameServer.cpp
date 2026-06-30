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
	acceptPlayers();
}

// Overload ostream insertion operator so we can easily log packet bodies.

std::ostream& operator<<(std::ostream& os, const RSNet::Packet& p)
{
	os << "Packet length: " << p.body_length << " body: \n";
	os.write(p.body, p.body_length);
	os << "\n";
	return os;
}

void async_accept_handler(const boost::system::error_code& ec, 
	ip::tcp)
{

}

void RSNet::GameServer::acceptPlayers()
{
	// need this socket to establish tcp connections, 
	// it will be copied into the connected_players map
	// GS owns this socket.
	auto socket = std::make_unique<ip::tcp::socket>(_ctx);

	// socket unique owner ship, we need to call move to capture it in the lambda.
	_acceptor.async_accept(*socket, [this, socket = std::move(socket)](const boost::system::error_code& ec) mutable
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
			std::cout << ec.message() << std::endl;

			acceptPlayers();
		});
}