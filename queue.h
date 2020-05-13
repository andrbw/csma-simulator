#pragma once

#include "packet.h"
#include "simulator.h"
#include <memory>
#include <vector>

class Queue 
{
public:
  Queue ();
  int GetQueueSize ();
  void AddPacket (std::shared_ptr<Packet>);
  void RemovePacket (std::shared_ptr<Packet>);
  ~Queue ();

private:
  std::vector<std::shared_ptr<Packet>> m_queue;
  std::uniform_int_distribution<> m_random;
  std::map<std::shared_ptr<Packet>, bool> m_broken;
};
