#pragma once

#include "queue.h"
#include <memory>

class Server 
{
public:
  Server ();
  void AddPacket (std::shared_ptr<Packet> packet);
  bool IsBusy ();
  
private:
  Queue m_queue;
  double m_propDelay;
};
