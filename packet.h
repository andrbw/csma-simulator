#pragma once
#include <functional>
#include <memory>

class Packet 
{
public:
  Packet (double arrivalTime, double serviceTime);
  double GetArrivalTime ();
  double GetServiceTime ();
  void SetRxOkCallback (std::function <void (std::shared_ptr<Packet>)> callback);
  void SetRxErrCallback (std::function <void (std::shared_ptr<Packet>)> callback);
  std::function <void (std::shared_ptr<Packet>)> GetRxOkCallback ();
  std::function <void (std::shared_ptr<Packet>)> GetRxErrCallback (); 

private:
  double m_arrivalTime;
  double m_serviceTime;
  std::function <void (std::shared_ptr<Packet>)> m_rxOkCallback;
  std::function <void (std::shared_ptr<Packet>)> m_rxErrCallback;
};
