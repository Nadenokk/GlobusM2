#ifndef PrimaryGeneratorAction_h
#define PrimaryGeneratorAction_h 1

#include "G4VUserPrimaryGeneratorAction.hh"
#include "G4ParticleGun.hh"
#include "globals.hh"
#include "FrequencyFunction.hh"
#include <vector>
class G4ParticleGun;
class G4Event;
class G4Box;

/// The primary generator action class with particle gun.

class PrimaryGeneratorAction : public G4VUserPrimaryGeneratorAction
{
  public:
    PrimaryGeneratorAction();
    virtual ~PrimaryGeneratorAction();

    virtual void GeneratePrimaries(G4Event*);         

    const G4ParticleGun* GetParticleGun() const { return fParticleGun; }

  private:
    G4double* GetRandomPosition();
    std::vector<std::vector<G4double> > position;
    std::vector<G4double> probability;
    std::vector<G4double> probabilitySumm;

    G4ParticleGun*  fParticleGun;
    G4Box* fEnvelopeBox;
};

#endif
