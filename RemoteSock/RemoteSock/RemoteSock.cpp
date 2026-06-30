// RemoteSock.cpp : Defines the entry point for the application.
//

#include "RemoteSock.h"
#include <boost/asio.hpp>
#include <iostream>
#include <thread>
#include "../RSNet/RSNet.h"

using boost::asio::ip::tcp;

int main()
{
	boost::asio::io_context ctx;
	uint16_t port = 20067;
	RSNet::GameServer gs(ctx, port);
	ctx.run();
	while (true)
	{

	}
	return 0;
}
