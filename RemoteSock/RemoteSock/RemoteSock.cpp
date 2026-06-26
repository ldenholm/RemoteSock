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
	// todo: use async accept
	tcp::acceptor acceptor(ctx, tcp::endpoint(tcp::v4(), 20067));
	tcp::socket sckt(ctx);
	std::cout << "Server halt until client accepted..." << std::endl;
	acceptor.accept(sckt); 
	std::cout << "Connection accepted from:" << std::endl;
	while (true)
	{

	}

	RSNet::Packet p{
		.header = "hi header",
		.body = "hello body"
	};
	return 0;
}
