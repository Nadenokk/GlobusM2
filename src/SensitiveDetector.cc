#include<G4Step.hh>
#include<iostream>
#include"SensitiveDetector.hh"

using namespace std;

SensitiveDetector::SensitiveDetector(G4String name): G4VSensitiveDetector(name)
{
    detectorName = name;
    count=0;
}
G4bool SensitiveDetector::ProcessHits(G4Step *step, G4TouchableHistory *hist)
{

    if(step->GetTrack()->GetDefinition()->GetParticleName() == "neutron" ) {
        count++;
        summaCounts.operator++(1);

        G4cout
        <<" Detector:" << detectorName
        <<" KineticEnergy:"<< step->GetPreStepPoint()->GetKineticEnergy()
        <<G4endl;
    }

    step->GetTrack()->SetTrackStatus(fKillTrackAndSecondaries);
    return true;
}

G4int SensitiveDetector::getSummaCounts(){return  summaCounts;}

SensitiveDetector::~SensitiveDetector()
{
    G4cout <<"Stat number for "<< detectorName <<": " << count
    << G4endl;
}
