#pragma once

#include <boost/asio.hpp>


/*
* RSNet Network I/O Queue Implementations
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
	private:
		boost::asio::io_context& _ctx;
	};
}