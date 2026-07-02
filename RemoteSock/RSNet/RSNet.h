/*
* Okay I need to rethink how this is all connected. The dedicated global NetIn/NetOut
* queues was a cute idea but its not quite going to work because passing around the sockets
* like I just tried is messy. I think I need a session style class per socket so its
* responsible for all read/write actions on the sockets and encapsulates a connection,
* that way GS can simply have a map of connection objects and then push broadcasts and
* requests to the connection which in turn will process it.

*/

#pragma once

#ifndef WINVER
#define WINVER 0x0A00
#endif

#ifndef _WIN32_WINNT
#define _WIN32_WINNT 0x0A00
#endif

#include <cstdint>
#include <iostream>
#include <boost/asio.hpp>
#include <limits>
#include <queue>


namespace RSNet
{
	enum class MESSAGE_TYPE : uint8_t
	{
		DEFAULT,
		BROADCAST,
		KICK,
		BAN,
		PLAYERUPDATE,
		GAMEUPDATE
	};

	struct Packet
	{
		static constexpr std::size_t MAX_SIZE_BODY = 1024;

		uint8_t header;
		// guaranteed 1024 bytes
		char body[1024];
		uint16_t body_len_bytes;
		// so we can track what we've actually used, it will be easier when tx, rx.
		
		/*
		* We want 2 overloaded operators.
		* packet1 << "some string". Packs string into body.
		* std::cout << packet1. Outputs packet1 like: "header: body".
		* 
		* 
		* 
		* A nice to have would be a third operator:
		* packet1 << MESSAGE_TYPE. Packs message type enum into header.
		*/ 

		Packet& operator<<(const std::string& contents) 
		{ 

			if (contents.size() >= sizeof(body))
			{
				throw std::runtime_error("Body exceeds buffer.");
			}
			// guaranteed now after the check above.
			this->body_len_bytes = static_cast<uint16_t>(contents.size());

			// note: std::string.data() guarantees null terminator {for >= c++17, which ive set}
			std::memcpy(body, contents.data(), contents.size());
			header = static_cast<uint8_t>(MESSAGE_TYPE::DEFAULT);
			return *this;
		}

		friend std::ostream& operator<<(std::ostream& os, const RSNet::Packet& p);
		
		// make sure compiler picks up on a different body size.
		static_assert(Packet::MAX_SIZE_BODY <= std::numeric_limits<uint16_t>::max());
	};

	template<MESSAGE_TYPE T> 
	Packet make_packet(const std::string& message)
	{
		if (message.size() > Packet::MAX_SIZE_BODY)
		{
			throw std::runtime_error("Message too large for a single packet, split!");
		}

		auto len = static_cast<uint16_t>(message.size());
		Packet p{};
		p.header = static_cast<uint8_t>(T);
		std::memcpy(p.body, message.data(), len);
		p.body_len_bytes = len;
		return p;
	}

	class Connection
	{
	public:
		Connection(boost::asio::io_context& ctx);

		Connection() = delete;

		Connection(Connection&& c) = delete;

		Connection& operator=(Connection&& c) = delete;

		boost::asio::ip::tcp::socket& socket();

		void send();

		void read();

	private:
		boost::asio::ip::tcp::socket _socket;
		bool _writing;
	};

	class GameServer
	{
	public:
		GameServer(boost::asio::io_context& ctx, uint16_t listenPort);

		// Delete default, move ctors.
		GameServer() = delete;

		GameServer(GameServer&& gs) = delete;

		// delete move assignment operator.
		GameServer& operator=(GameServer&& gs) = delete;

		void run();

		//void broadcast(const std::string& message);
	private:
		boost::asio::io_context& _ctx;
		boost::asio::ip::tcp::acceptor _acceptor;
		std::unordered_map<uint16_t, std::unique_ptr<Connection>> _connected_players;
		uint16_t _playerCount;


		void accept_players();
	};

}