#ifndef _NBODY_SIMULATION_H
#define _NBODY_SIMULATION_H

#include <nbody/constants.h>
#include <nbody/System.h>

#include <iosfwd>
#include <string>

namespace nbody {

  class NBODY_API Simulation {
    System *_system;
    std::string _name;
    Simulation( const Simulation& sim ) = delete;
    Simulation& operator=( const Simulation& sim ) = delete;
    std::string generateName();
  public:
    Simulation() : _system{nullptr}, _name{ generateName() } {}
    Simulation( std::istream &input ) : _system{new System(input)}, _name{ generateName() } {}
    Simulation( const std::string &filename ) : _system{nullptr}, _name{ generateName() } {
      attachSystem( filename );
    }
    void attachSystem( const std::string &filename );
    void attachSystem( std::istream &input );
    void evolveSystem( int nSteps, float dt );
    void saveRun() const;
  };

} // namespace nbody

#endif // _NBODY_SIMULATION_H
