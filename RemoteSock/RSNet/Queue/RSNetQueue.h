#pragma once

#include <boost/asio.hpp>
#include "../RSNet.h"


/*
* RSNet Network I/O Queue Implementations
* 
* Idea:
* 
* So main owns GS and fires it off on its own thread. The network queues should be
* executing in their own thread as well so we can process send/receive in parallel.
* A potential race can occur when GS needs to operate on a player in the socket map
* but the Net IO queues have a lock on them. I will explore the best way to handle
* this and potentially revisit the structure.
*/

namespace RSNet::Queue
{
	// Class to handle receive queue work.
	class NetInQueue
	{
	public:
		NetInQueue(boost::asio::io_context& ctx);

		NetInQueue() = delete;
	private:
		boost::asio::io_context& _ctx;
	};

	// Class to handle transmission queue work.
	class NetOutQueue
	{
	public:
		NetOutQueue(boost::asio::io_context& ctx);

		NetOutQueue() = delete;

		void send_packet_to_socket(const Packet& p, const boost::asio::ip::tcp::socket& socket);
	private:
		boost::asio::io_context& _ctx;
		std::unordered_map<const uint16_t&, const boost::asio::ip::tcp::socket&> _outbuffer;
	};
}