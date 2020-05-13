#pragma once

#include "simulator.h"
#include "server.h"
#include "packet.h"
#include <memory>

class PacketGeneratorBase {};

template <typename ArrivalDistribution, typename ServiceDistribution>
class PacketGenerator : public PacketGeneratorBase
{
  using ArrivalParamType = typename ArrivalDistribution::param_type;
  using ServiceParamType = typename ServiceDistribution::param_type;
public:
  PacketGenerator (const ArrivalParamType&, const ServiceParamType&);
  void SetServer (std::shared_ptr<Server> server);
  void Start ();
  void NewPacket ();
  void PacketServed ();
  
  void NotifyRxOk (std::shared_ptr<Packet>);
  void NotifyRxErr (std::shared_ptr<Packet>);

  ~PacketGenerator ();

private:
  ArrivalDistribution m_arrivalGen;
  ServiceDistribution m_serviceGen;
  std::shared_ptr<Server> m_server;
  std::uniform_real_distribution<double> m_random; 
  int m_numOk; 
};

template <typename ArrivalDistribution, typename ServiceDistribution>
PacketGenerator<ArrivalDistribution, ServiceDistribution>::PacketGenerator (const ArrivalParamType& arrivalParams, const ServiceParamType& serviceParams)
: m_arrivalGen (arrivalParams),
  m_serviceGen (serviceParams),
  m_random (0.0, 1.0)
{
  m_numOk = 0;
}

template <typename ArrivalDistribution, typename ServiceDistribution>
PacketGenerator<ArrivalDistribution, ServiceDistribution>::~PacketGenerator ()
{
  std::cout << (double)m_numOk / (double)Simulator::Now() << std::endl;
}

template <typename ArrivalDistribution, typename ServiceDistribution>
void
PacketGenerator<ArrivalDistribution, ServiceDistribution>::SetServer (std::shared_ptr<Server> server)
{
  m_server = server;
}

template <typename ArrivalDistribution, typename ServiceDistribution>
void
PacketGenerator<ArrivalDistribution, ServiceDistribution>::Start ()
{
  std::function <void ()> callback = std::bind (&PacketGenerator<ArrivalDistribution, ServiceDistribution>::NewPacket, this); 
  Simulator::Schedule (m_arrivalGen (Simulator::Engine ()), callback);
}

template <typename ArrivalDistribution, typename ServiceDistribution>
void
PacketGenerator<ArrivalDistribution, ServiceDistribution>::NewPacket ()
{
  if (m_server->IsBusy ())
  {
    std::function <void ()> callback = std::bind (&PacketGenerator<ArrivalDistribution, ServiceDistribution>::NewPacket, this);
    double delay = m_random (Simulator::Engine());
    //std::cout << "Server busy, wait" << std::endl;
    Simulator::Schedule (delay, callback);
    return;
  }
  std::shared_ptr<Packet> p (new Packet (Simulator::Now (), m_serviceGen (Simulator::Engine ())));
  std::function <void (std::shared_ptr<Packet>)> rxOkCallback = std::bind (&PacketGenerator<ArrivalDistribution, ServiceDistribution>::NotifyRxOk, this, std::placeholders::_1);
  std::function <void (std::shared_ptr<Packet>)> rxErrCallback = std::bind (&PacketGenerator<ArrivalDistribution, ServiceDistribution>::NotifyRxErr, this, std::placeholders::_1);
  p->SetRxOkCallback (rxOkCallback);
  p->SetRxErrCallback (rxErrCallback);
  m_server->AddPacket (p);
  std::function <void ()> callback = std::bind (&PacketGenerator<ArrivalDistribution, ServiceDistribution>::NewPacket, this); 
  Simulator::Schedule (m_arrivalGen (Simulator::Engine ()), callback);
}

template <typename ArrivalDistribution, typename ServiceDistribution>
void
PacketGenerator<ArrivalDistribution, ServiceDistribution>::NotifyRxOk (std::shared_ptr<Packet> p)
{
  m_numOk++;
}

template <typename ArrivalDistribution, typename ServiceDistribution>
void
PacketGenerator<ArrivalDistribution, ServiceDistribution>::NotifyRxErr (std::shared_ptr<Packet> p)
{
  //std::cout << "ERR" << std::endl;
}

