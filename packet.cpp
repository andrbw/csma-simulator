#include "packet.h"

Packet::Packet (double arrivalTime, double serviceTime)
{
  m_arrivalTime = arrivalTime;
  m_serviceTime = serviceTime;
}

double
Packet::GetArrivalTime ()
{
  return m_arrivalTime;
}

double
Packet::GetServiceTime ()
{
  return m_serviceTime;
}

std::function <void (std::shared_ptr<Packet>)>
Packet::GetRxOkCallback ()
{
  return m_rxOkCallback;
}

std::function <void (std::shared_ptr<Packet>)> 
Packet::GetRxErrCallback ()
{
  return m_rxErrCallback;
}

void
Packet::SetRxOkCallback (std::function <void (std::shared_ptr<Packet>)> callback)
{
  m_rxOkCallback = callback;
}

void
Packet::SetRxErrCallback (std::function <void (std::shared_ptr<Packet>)> callback)
{
  m_rxErrCallback = callback;
} 
