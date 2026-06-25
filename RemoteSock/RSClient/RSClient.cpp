#include "RSClient.h"
#include <boost/asio.hpp>

#include <iostream>
#include <thread>

using boost::asio::ip::tcp;

int main()
{
	try {
		boost::asio::io_context ctx;
		tcp::socket sckt(ctx);
		sckt.connect(tcp::endpoint(boost::asio::ip::make_address("127.0.0.1"), 20067));
		std::cout << "Connected to server: 127.0.0.1:20067"; // todo parameterize ip + port.
	}
	catch (std::exception& e) {
		std::cout << "Exception establishing connection: " << e.what() << std::endl;
	}

	while (true)
	{

	}
	
	return 0;
}

int RSClient::setup()
{
	return 1;
}