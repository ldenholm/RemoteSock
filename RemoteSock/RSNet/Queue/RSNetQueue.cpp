#include "RSNetQueue.h"
#include "../RSNet.h"
#include <boost/asio.hpp>

// Network Inbound Queue Implementation

using namespace RSNet::Queue;

NetInQueue::NetInQueue(boost::asio::io_context& ctx, RSNet::GameServer& gs) : 
	_ctx(ctx), _gs(gs)
{

}



// Network Inbound Queue Implementation

NetOutQueue::NetOutQueue(boost::asio::io_context& ctx, RSNet::GameServer& gs) :
	_ctx(ctx), _gs(gs)
{

}

//void NetOutQueue::broadcast(const std::string& message)
//{
//	if (message.size() > RSNet::Packet::MAX_SIZE_BODY)
//	{
//		throw std::runtime_error("Packet body exceeds limit.");
//	}
//
//	//Packet bc_packet = make_packet<MESSAGE_TYPE::BROADCAST>(message);
//	auto ptr_packet = std::make_shared<Packet>(make_packet<MESSAGE_TYPE::BROADCAST>(message));
//	auto& players = _gs.get_connected_players();
//	
//	for (auto& [id, socket] : players)
//	{
//		std::cout << "broadcast to player: " << id << std::endl;
//		boost::asio::async_write(socket, boost::asio::buffer(ptr_packet.get(), sizeof(Packet)), 
//			[ptr_packet, id](const boost::system::error_code ec, std::size_t s) {
//			// note if we dont capture the smart pointer in the lambda capture clause it wont stay alive until operation completes.
//			if (ec)
//			{
//				std::cout << ec.message() << std::endl;
//			}
//
//			std::cout << "sent num bytes = " << s << "to player:" << id << std::endl;
//			});
//}