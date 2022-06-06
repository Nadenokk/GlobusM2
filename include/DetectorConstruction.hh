#ifndef DetectorConstruction_h
#define DetectorConstruction_h 1

#include <atomic>
#include "G4VUserDetectorConstruction.hh"
#include "G4GlobalMagFieldMessenger.hh"
#include "globals.hh"
#include "SensitiveDetector.hh"
#include <vector>
#include "list"

class G4VPhysicalVolume;
class G4LogicalVolume;
class G4GlobalMagFieldMessenger;

/// Detector construction class to define materials and geometry.

class DetectorConstruction : public G4VUserDetectorConstruction
{
  public:
    DetectorConstruction();
    ~DetectorConstruction();

    virtual G4VPhysicalVolume* Construct();
    std::list<G4LogicalVolume*> GetScoringVolume() const { return fScoringVolume; }
    virtual void ConstructSDandField();

  protected:
    std::list<G4LogicalVolume*>  fScoringVolume;

  private:
    SensitiveDetector *detector1;
    SensitiveDetector *detector2;
    static G4ThreadLocal G4GlobalMagFieldMessenger*  fMagFieldMessenger;
    G4double pi = 3.1415926535897932384626433832795;

};

#endif

