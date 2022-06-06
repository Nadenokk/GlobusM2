#include "PrimaryGeneratorAction.hh"

#include "G4Box.hh"
#include "G4RunManager.hh"
#include "G4ParticleGun.hh"
#include "G4ParticleTable.hh"
#include "G4ParticleDefinition.hh"
#include "G4SystemOfUnits.hh"
#include "Randomize.hh"
#include "FrequencyFunction.hh"
#include "GetCsv.hh"

#include <vector>

using namespace std;

PrimaryGeneratorAction::PrimaryGeneratorAction()
: G4VUserPrimaryGeneratorAction(),
  fParticleGun(0), 
  fEnvelopeBox(0)
{

  G4int n_particle = 1;
  fParticleGun  = new G4ParticleGun(n_particle);

  G4ParticleTable* particleTable = G4ParticleTable::GetParticleTable();
  G4String particleName;
  G4ParticleDefinition* particle = particleTable->FindParticle(particleName="neutron");
  fParticleGun->SetParticleDefinition(particle);
  fParticleGun->SetParticleEnergy(2.45*MeV);
  GetCsv *csv = new GetCsv();
  csv->LoadLEMTable(position, probability, probabilitySumm);

}
G4double* PrimaryGeneratorAction::GetRandomPosition(){
    G4double randomNumber = G4UniformRand ();

    G4double* a=new G4double [2];
    int regist=0;
    for(std::vector<G4String>::size_type i = 0 + regist; i < probabilitySumm.size(); i++) {
        if (randomNumber < probabilitySumm[i]) {
            a[0]= position[i][0]*1000;
            a[1]= position[i][1]*1000;
            break;
        }
    }
    G4double* b=new G4double [2];
    b[0]=440;
    b[1]=0;
    //return a;
    return b;
}


PrimaryGeneratorAction::~PrimaryGeneratorAction()
{
    delete fParticleGun;
}

void PrimaryGeneratorAction::GeneratePrimaries(G4Event* anEvent)
{
  auto *getXYZ = new FrequencyFunction;

  fParticleGun->SetParticlePosition(getXYZ->GetPosition(GetRandomPosition()));
  fParticleGun->SetParticleMomentumDirection(getXYZ->GetMomentumDirection());
  fParticleGun->GeneratePrimaryVertex(anEvent);
}
