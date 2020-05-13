#pragma once

#include <functional>
#include <map>
#include <random>
#include <memory>
#include "packet.h"

class MyFunction 
{
public:
  virtual ~MyFunction(){}
  virtual void operator()() = 0;
};

class MyFunctionVoid : public MyFunction 
{
public:
  MyFunctionVoid(std::function<void()> f) : m_function(f) {} 

  virtual void operator()() 
  {
    m_function ();
  }
private:
  std::function<void()> m_function;
};

class MyFunctionPacket : public MyFunction
{
public:
  MyFunctionPacket(std::function<void(std::shared_ptr<Packet>)> f, std::shared_ptr<Packet> arg1) : m_function(f), m_arg1(arg1) {} 

  virtual void operator()()
  { 
    m_function (m_arg1);
  }
private:
  std::function<void(std::shared_ptr<Packet>)> m_function;
  std::shared_ptr<Packet> m_arg1;
};

class Simulator 
{
public:
  Simulator ();
  static void Schedule (double time, std::function<void ()> handler);
  static void Schedule (double time, std::function<void(std::shared_ptr<Packet>)> packet, std::shared_ptr<Packet> p);

  static double Now ();
  static std::mt19937& Engine ();
  static void Run ();
  static void SetStop (double simTime);
  static void SetSeed (int seed);
};
