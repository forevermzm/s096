#include <nbody/constants.h>
#include <nbody/System.h>
#include <nbody/Vector3.h>

#include <fstream>
#include <stdexcept>
#include <iostream>
#include <iomanip>

namespace nbody {

  void System::initRandomState() {
    // TODO: make a plausible random state
  }

  inline void System::interactBodies( size_t i, size_t j, float softFactor, Vector3f &acc ) const {
    Vector3f r = _body[j].position() - _body[i].position();
    float distance = r.norm() + softFactor;
    //std::cout << "distance: " << distance << "\n";
    float invDist = 1.0f / distance;
    float invDistCubed = cube( invDist );
    acc = acc + NEWTON_G * _body[j].mass() * invDistCubed * r;
  }

  void System::computeGravitation() {
    for( size_t i = 0; i < _nBodies; ++i ) {
      Vector3f acc{ 0.0f, 0.0f, 0.0f };
      for( size_t j = 0; j < _nBodies; ++j ) {
        if( i != j ) {
          //std::cout << "iact " << i << " vs. " << j << "\n";
          interactBodies( i, j, _softFactor, acc );
        }
      }
      _body[i].force() = acc;
    }
  }

  void System::integrateSystem( float dt ) {
    Vector3f r, v, a;
    for( size_t i = 0; i < _nBodies; ++i ) {
      r = _body[i].position();
      v = _body[i].velocity();
      a = _body[i].force();// / _body[i].mass();

      v = v + ( a * dt );
      v = v * _dampingFactor;
      //std::cout << "INTEGRATE:\n";
      //std::cout << "\tdv: " << v * dt <<"\n";
     // std::cout << "\tBEFORE: " << r <<"\n";
      r = r + v * dt;
    //  std::cout << "\tAFTER: " << r <<"\n";

      _body[i].position() = r;
      _body[i].velocity() = v;
    }
  }

  void System::update( float dt ) {
    computeGravitation();
    integrateSystem( dt );
  }

  void System::readState( std::string filename ) {
    std::ifstream input{filename};
    readState( input );
    input.close();
  }

  void System::readState( std::istream &input ) {
    input >> _nBodies;
    if( _nBodies > MAX_BODIES_RECOMMENDED ) {
      throw std::runtime_error( "Too many input bodies" );
    }
    _body = new Body[_nBodies];
    for( size_t i = 0; i < _nBodies; ++i ) {
      input >> _body[i];
    }
  }

  void System::writeState( std::string filename ) const {
    std::ofstream output{filename};
    writeState( output );
    output.close();
  }

  void System::writeState( std::ostream &output ) const {
    output << _nBodies << "\n";
    for( size_t i = 0; i < _nBodies; ++i ) {
      if( i == 1 ) {
        std::cout << "Body[" << i << "]:\n";
        std::cout << std::scientific;
        std::cout << "\tvelocity = " << _body[i].velocity().norm() << "\n";
        std::cout << "\t\t" << _body[i].velocity() << "\n";
        std::cout << "\tposition = " << _body[i].position().norm() << "\n";
        std::cout << "\t\t" << _body[i].position() << "\n";
        //logfile << _body[i].position() << " ";
        //logfile << _body[i-1].position() << "\n";
      }
      output << _body[i] << "\n";
    }
  }

} // namespace nbody
