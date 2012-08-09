class Particle;

#ifndef __INCLUDED_PARTICLE_H
#define __INCLUDED_PARTICLE_H

#include "LPD8806.h"

class ParticleVisualizer;

class Particle {
  public:
    /**
     * Age the particle by 'millis' milliseconds.
     *
     * @return TRUE iff the particle is still alive
     */
    virtual bool age(ParticleVisualizer* pv, unsigned int millis)=0;

    virtual void render(LPD8806* strip)=0;
};

#endif

