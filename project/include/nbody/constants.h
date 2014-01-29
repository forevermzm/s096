#ifndef _NBODY_CONSTANTS_H
#define _NBODY_CONSTANTS_H

#include <cstddef> 

#ifdef _WIN32
#ifdef NBODY_EXPORTS
#define NBODY_API __declspec( dllexport )
#else
#define NBODY_API __declspec( dllimport )
#endif
#else
#define NBODY_API 
#endif

namespace nbody {

  extern const size_t MAX_BODIES_RECOMMENDED; // = 10000
  extern const float NEWTON_G; // = 1.0f

} // namespace nbody
#endif // _NBODY_CONSTANTS_H
