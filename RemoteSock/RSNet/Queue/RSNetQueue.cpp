#include "RSNetQueue.h"
#include "../RSNet.h"
#include <boost/asio.hpp>

// Network Inbound Queue Implementation

RSNet::Queue::NetInQueue::NetInQueue(boost::asio::io_context& ctx) : _ctx(ctx)
{

}



// Network Inbound Queue Implementation

RSNet::Queue::NetOutQueue::NetOutQueue(boost::asio::io_context& ctx) : _ctx(ctx)
{

}

void RSNet::Queue::NetOutQueue::send_packet_to_socket(const RSNet::Packet& p, const boost::asio::ip::tcp::socket& socket)
{
	// todo implement this.
}