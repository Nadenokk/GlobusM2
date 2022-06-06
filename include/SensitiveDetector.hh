#ifndef T1_SENSITIVEDETECTOR_HH
#define T1_SENSITIVEDETECTOR_HH

#include<G4VSensitiveDetector.hh>
#include "G4Accumulable.hh"
class G4Step;
class G4TouchableHistory;

static std::atomic<G4int> summaCounts{ 0 };

class SensitiveDetector: public G4VSensitiveDetector
{
private:
    G4int count;
    G4String detectorName;

public:
    SensitiveDetector(G4String name);
    ~SensitiveDetector();

    G4bool ProcessHits(G4Step *step, G4TouchableHistory *hist);

    G4int getSummaCounts();
};

#endif
