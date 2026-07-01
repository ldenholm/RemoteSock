#include "RSNetQueue.h"
#include <boost/asio.hpp>

RSNet::Queue::NetInQueue::NetInQueue(boost::asio::io_context& ctx) : _ctx(ctx)
{

}


RSNet::Queue::NetOutQueue::NetOutQueue(boost::asio::io_context& ctx) : _ctx(ctx)
{

}