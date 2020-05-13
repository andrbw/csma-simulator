#include <iostream>
#include <memory>
#include "packet-generator.h"
#include "simulator.h"

int main(int argc, char** argv)
{
  if (argc < 5) 
  {
    std::cout << "Usage: ./scenario seed lambda mu simTime nodes" << std::endl;
    return -1;
  }
  int seed = atoi (argv[1]);
  double lambda = atof (argv[2]);
  double mu = atof (argv[3]);
  time_t simTime = atof (argv[4]);
  int nodes = atoi(argv[5]);

  Simulator sim;
  sim.SetStop (simTime);
  sim.SetSeed (seed);

  std::shared_ptr<Server> server (new Server ());

  std::vector <std::shared_ptr<PacketGeneratorBase>> packetGens;
  for (int i = 0; i < nodes; i++)
  {
    std::exponential_distribution<double>::param_type params1 (lambda);
    std::uniform_int_distribution<>::param_type params2 (mu, mu);
    //std::exponential_distribution<double>::param_type params2 (mu);
    auto *packetGen = new PacketGenerator<std::exponential_distribution<double>, std::uniform_int_distribution<>>(params1, params2);
    packetGen->SetServer (server);
    packetGen->Start ();
    packetGens.push_back(std::shared_ptr<PacketGeneratorBase> (packetGen));
  }

  sim.Run ();
}
