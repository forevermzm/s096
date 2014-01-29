#include <nbody/Simulation.h>
#include <nbody/System.h>

#include <sstream>
#include <chrono>
#include <stdexcept>
#include <string>
#include <fstream>

namespace nbody {

  std::string Simulation::generateName() {
    using std::chrono::system_clock;
    using namespace std::chrono;
    std::tm timeinfo = std::tm();
    timeinfo.tm_year = 114;   // year: 2014
    timeinfo.tm_mon = 0;      // month: january
    timeinfo.tm_mday = 27;     // day: 27th
    time_t tt = mktime( &timeinfo );

    system_clock::time_point tp = system_clock::from_time_t( tt );
    system_clock::duration d = system_clock::now() - tp;
    std::ostringstream os; os << duration_cast<seconds>( d ).count() << "-sim.txt";
    return os.str();
  }

  void Simulation::attachSystem( const std::string &filename ) {
    if( _system != nullptr ) {
      throw std::runtime_error( "Tried to attach new system to running simulation!" );
    } else {
      std::ifstream input{ filename };
      if( input.is_open() ) {
        _system = new System{input};
      } else {
        throw std::runtime_error( "Could not open file to attach system" );
      }
      input.close();
    }
  }

  void Simulation::attachSystem( std::istream &input ) {
    if( _system != nullptr ) {
      throw std::runtime_error( "Tried to attach new system to running simulation!" );
    } else {
      _system = new System{input};
    }
  }

  void Simulation::evolveSystem( int nSteps, float dt ) {
    if( _system != nullptr ) {
      for( int step = 0; step < nSteps; ++step ) {
        _system->update( dt );
      }
    } else {
      throw std::runtime_error( "Tried to evolve simulation with no system!" );
    }
  }

  void Simulation::saveRun() const {
    std::ofstream output{ _name };
    _system->writeState( output );
  }

} // namespace nbody
