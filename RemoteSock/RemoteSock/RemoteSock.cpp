// RemoteSock.cpp : Defines the entry point for the application.
//

#include "RemoteSock.h"
#include <boost/asio.hpp>
#include <iostream>
#include <thread>

using boost::asio::ip::tcp;

int main()
{
	
	boost::asio::io_context ctx;
	tcp::acceptor acceptor(ctx, tcp::endpoint(tcp::v4(), 20067));
	tcp::socket sckt(ctx);
	std::cout << "Server halt until client accepted..." << std::endl;
	acceptor.accept(sckt); 
	std::cout << "Connection accepted from:" << std::endl;
	while (true)
	{

	}
	return 0;
}
