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
	//auto socket = std::make_unique<ip::tcp::socket>(_ctx);
	auto connection = std::make_unique<Connection>(_ctx);
	auto& socket = connection->socket();

	std::cout << "socket open: " << socket.is_open() << '\n';

	std::cout << "acceptor open: " << _acceptor.is_open() << '\n';
	// socket unique owner ship, we need to call move to capture it in the lambda.
	_acceptor.async_accept(socket, [this, connection = std::move(connection)](const boost::system::error_code& ec) mutable
		{
			// note after the capture clause the outside scope socket ptr becomes null.
			if (!ec)
			{
				// accept connection, move socket to map.
				// todo: enforce unique IP.
				
				_connected_players.emplace(_playerCount, std::move(connection));
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

//void RSNet::GameServer::broadcast(const std::string& message)
//{
	// make_packet<broadcast>(std::string&& message)
	// create the work to be completed, send a packet
	// to ever member of the connected_players map.
	// push the work to the NetOutQueue.

	//Packet bc_packet = make_packet<MESSAGE_TYPE::BROADCAST>(message);
	//for (auto & [playerid, playersocket] : _connected_players)
	//{
		// we push <ip::tcp::socket*, Packet*> to net out queue buffer.
		// dont do this here, simply dispatch broadcast event to net out queue.
	//}
//}


// Overload ostream insertion operator so we can easily log packet bodies.

std::ostream& operator<<(std::ostream& os, const RSNet::Packet& p)
{
	os << "Packet length: " << p.body_len_bytes << " body: \n";
	os.write(p.body, p.body_len_bytes);
	os << "\n";
	return os;
}