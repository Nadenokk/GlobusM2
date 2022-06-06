#ifndef SteppingAction_h
#define SteppingAction_h 1

#include "G4UserSteppingAction.hh"
#include "globals.hh"
#include "list"

class EventAction;
class G4LogicalVolume;

class SteppingAction : public G4UserSteppingAction
{
  public:
    SteppingAction(EventAction* eventAction);
    virtual ~SteppingAction();

    virtual void UserSteppingAction(const G4Step*);

  private:
    EventAction*  fEventAction;
    std::list<G4LogicalVolume*> fScoringVolume;
};
#endif
