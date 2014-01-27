#include <cmath>
#include <vector>
#include <iosfwd>
#include <stdexcept>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <iomanip>
#include <chrono>

const size_t MAX_BODIES_RECOMMENDED = 10000;
const float NEWTON_G = 6.67e-11f;

template<typename T>
class Vector3 {
  T _x, _y, _z;
public:
  Vector3() : _x{}, _y{}, _z{} {}
  Vector3( T x_, T y_, T z_ ) : _x{x_}, _y{y_}, _z{z_} {}
  inline T x() const { return _x; }
  inline T y() const { return _y; }
  inline T z() const { return _z; }
  T norm() const;
  T normsq() const;
  friend std::istream& operator>>( std::istream &is, Vector3<T> &vec ) {
    std::string lbracket, comma1, comma2, rbracket;
    is >> lbracket >> vec._x >> comma1 >> vec._y >> comma2 >> vec._z >> rbracket;
    return is;
  }
};

template<typename T>
inline T Vector3<T>::normsq() const {
  return _x * _x + _y * _y + _z * _z;
}

template<typename T>
inline T Vector3<T>::norm() const {
  return sqrt( normsq() );
}

template<>
inline float Vector3<float>::norm() const {
  return sqrtf( normsq() );
}

template<typename T>
inline const Vector3<T> operator+( const Vector3<T> &a, const Vector3<T> &b ) {
  return Vector3<T>{ a.x() + b.x(), a.y() + b.y(), a.z() + b.z() };
}

template<typename T>
inline const Vector3<T> operator-( const Vector3<T> &a, const Vector3<T> &b ) {
  return Vector3<T>{ a.x() - b.x(), a.y() - b.y(), a.z() - b.z() };
}

// Vector * scalar
template<typename T>
inline const Vector3<T> operator*( const Vector3<T> &a, T b ) {
  return Vector3<T>{ a.x() * b, a.y() * b, a.z() * b };
}

// scalar * Vector
template<typename T>
inline const Vector3<T> operator*( T a, const Vector3<T> &b ) {
  return Vector3<T>{ a * b.x(), a * b.y(), a * b.z() };
}

// Vector / scalar
template<typename T>
inline const Vector3<T> operator/( const Vector3<T> &a, T b ) {
  return Vector3<T>{ a.x() / b, a.y() / b, a.z() / b };
}

// Other useful math
template<typename T>
inline T dot( const Vector3<T> &a, const Vector3<T> &b ) {
  return a.x() * b.x() + a.y() * b.y() + a.z() * b.z();
}

template<typename T>
inline Vector3<T> cross( const Vector3<T> &a, const Vector3<T> &b ) {
  return Vector3<T>{ a.y() * b.z() - a.z() * b.y(),
                     a.z() * b.x() - a.x() * b.z(),
                     a.x() * b.y() - a.y() * b.x() };
}

template<typename T>
inline T cube( T x ) {
  return x * x * x;
}

template<typename T>
std::ostream& operator<<( std::ostream &os, const Vector3<T> &vec ) {
  os << "< " << vec.x() << " , " << vec.y() << " , " << vec.z() << " >";
  return os;
}

typedef Vector3<float> Vector3f;
typedef Vector3<double> Vector3d;

class Body {
  Vector3f _position;
  Vector3f _velocity;
  Vector3f _force;
  float _mass;
public:
  inline Vector3f position() const { return _position; }
  inline Vector3f& position() { return _position; }
  inline Vector3f velocity() const { return _velocity; }
  inline Vector3f& velocity() { return _velocity; }
  inline Vector3f force() const { return _force; }
  inline Vector3f& force() { return _force; }
  inline float mass() const { return _mass; }
  friend std::istream& operator>>( std::istream &is, Body &body );
  friend std::ostream& operator<<( std::ostream &os, const Body &body );
};

std::istream& operator>>( std::istream &is, Body &body ) {
  is >> body._position >> body._velocity >> body._force >> body._mass;
  return is;
}
std::ostream& operator<<( std::ostream &os, const Body &body ) {
  os << std::scientific;
  os << std::setprecision( 8 );
  os << body._position << " " << body._velocity << " ";
  os << body._force << " " <<  body._mass;
  return os;
}

class System {
  size_t _nBodies;
  Body *_body;
  float _softFactor = 1e-9f;
  float _dampingFactor = 1.0f;
  System() = delete;
  System( const System &sys ) = delete;
  System& operator=( const System &sys ) = delete;
public:
  System( size_t N ) : _nBodies{N}, _body{ new Body[N] } { initRandomState(); }
  System( std::istream &input ) : _nBodies{}, _body{nullptr} { readState( input ); }
  System( std::string filename ) : _nBodies{}, _body{nullptr} { readState( filename ); }
  ~System() { delete [] _body; }
  void interactBodies( size_t i, size_t j, float softFactor, Vector3f &acc ) const;
  void computeGravitation();
  void integrateSystem( float dt );
  void readState( std::istream &input );
  void readState( std::string filename );
  void writeState( std::ostream &output ) const;
  void writeState( std::string filename ) const;
  void initRandomState();
  void update( float dt );
  void setSoftening( float soft ) { _softFactor = soft; }
  void setDamping( float damp ) { _dampingFactor = damp; }
};

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
    output << _body[i] << "\n";
  }
}

class Simulation {
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

std::string Simulation::generateName() {
  using std::chrono::system_clock;
  using namespace std::chrono;
  std::tm timeinfo = std::tm();
  timeinfo.tm_year = 114;   // year: 2014
  timeinfo.tm_mon = 0;      // month: january
  timeinfo.tm_mday = 27;     // day: 27th
  std::time_t tt = std::mktime( &timeinfo );

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

int main() {
  try {
    Simulation sim{"simple.txt"};
    sim.evolveSystem( 1e6, 1.0 );
    sim.saveRun();
    return 0;
  } catch( const std::exception &e ) {
    std::cerr << "Error: " << e.what() << "\n";
    return 1;
  }
}
