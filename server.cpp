#include "server.h"
#include <iostream>

Server::Server ()
{
  m_propDelay = 0.001;
}

void
Server::AddPacket (std::shared_ptr<Packet> p)
{
  //std::cout << Simulator::Now () << ": server add packet" << std::endl;
  std::function <void (std::shared_ptr<Packet>)> callback = std::bind (&Queue::AddPacket, &m_queue, std::placeholders::_1);
  Simulator::Schedule (m_propDelay, callback, p);
}

bool
Server::IsBusy ()
{
  return (m_queue.GetQueueSize ());
}
