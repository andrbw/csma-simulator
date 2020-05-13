#include "queue.h"
#include <iostream>
#include <functional>

Queue::Queue ()
: m_random (0, 1) 
{
}

int
Queue::GetQueueSize ()
{
  return m_queue.size ();
}

void
Queue::AddPacket (std::shared_ptr<Packet> packet)
{
  //std::cout << Simulator::Now() << ": add packet with service time = " << packet->GetServiceTime () << std::endl;
  m_queue.push_back (packet);
  std::function <void ()> callback = std::bind (&Queue::RemovePacket, this, packet); 
  Simulator::Schedule (packet->GetServiceTime (), callback);
  if (m_queue.size () > 1)
  {
    for (auto &&p : m_queue)
    {
      m_broken[p] = true;
    }
  }
  else
  {
    m_broken[packet] = false;
  }
}

void
Queue::RemovePacket (std::shared_ptr<Packet> p)
{
  //std::cout << Simulator::Now () << ": remove packet" << std::endl;
  for (auto it = m_queue.begin (); it != m_queue.end (); it++)
  {
    if (*it == p)
    {
      m_queue.erase (it);
      bool broken = m_broken[p];
      m_broken.erase (p);
      if (broken)
      {
        p->GetRxErrCallback () (p);
      }
      else
      {
        p->GetRxOkCallback () (p);
      } 
      break;
    }
  }
}

Queue::~Queue ()
{
  m_queue.clear ();
}
