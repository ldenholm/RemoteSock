#pragma once

#include <cstdint>
#include <iostream>
#include <boost/asio.hpp>

namespace RSNet
{
	enum class MESSAGE_TYPE 
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
		uint8_t header;
		// guaranteed 1024 bytes
		char body[1024];
		uint16_t body_length;
		// so we can track what we've actually used, it will be easier when tx, rx.
		
		/*void printBody()
		{
			std::cout << static_cast()
		}*/
		
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
			this->body_length = static_cast<uint16_t>(contents.size());

			// note: std::string.data() guarantees null terminator {for >= c++17, which ive set}
			std::memcpy(body, contents.data(), contents.size());
			header = static_cast<uint8_t>(MESSAGE_TYPE::DEFAULT);
			return *this;
		}

		friend std::ostream& operator<<(std::ostream& os, const RSNet::Packet& p);
		
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
	private:
		boost::asio::io_context& _ctx;
		boost::asio::ip::tcp::acceptor _acceptor;
		std::unordered_map<uint8_t, boost::asio::ip::tcp::socket> connected_players;
	};
}