#ifndef FrequencyFunction_h
#define FrequencyFunction_h 1

#include "globals.hh"
#include "Randomize.hh"
#include "G4VUserPrimaryGeneratorAction.hh"
#include "G4ParticleGun.hh"


class FrequencyFunction
{
  public:
    G4ThreeVector GetPosition(G4double*) const ;
    G4ThreeVector GetMomentumDirection() const ;
  
  private:
    G4double pi = 3.1415926535897932384626433832795;
};

#endif
