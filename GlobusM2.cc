#include "DetectorConstruction.hh"
#include "ActionInitialization.hh"

#ifdef G4MULTITHREADED
#include "G4MTRunManager.hh"
#else
#include "G4RunManager.hh"
#endif

#include "G4UImanager.hh"
#include "QBBC.hh"
#include "QGSP_BIC.hh"
#include "QGSP_BIC_HP.hh"

#include <CLHEP/Units/SystemOfUnits.h>
#include "globals.hh"
#include "G4VModularPhysicsList.hh"
#include "CompileTimeConstraints.hh"

#include "G4VisExecutive.hh"
#include "G4UIExecutive.hh"
#include <vector>
#include "time.h"

int main(int argc,char** argv)
{

  G4UIExecutive* ui = 0;
  if ( argc == 1 ) {
    ui = new G4UIExecutive(argc, argv);
  }

  //  G4long seed = time(NULL);
  //  CLHEP::HepRandom::setTheSeed(seed);

#ifdef G4MULTITHREADED
  auto runManager = new G4MTRunManager;
  G4int nThreads = G4Threading::G4GetNumberOfCores();
  runManager->SetNumberOfThreads(nThreads - 2);
#else
  auto runManager = new G4RunManager;
#endif

  // Detector construction
  runManager->SetUserInitialization(new DetectorConstruction());

  // Physics list

  //G4VModularPhysicsList* physicsList = new QGSP_BIC_HP();
  //G4VModularPhysicsList* physicsList = new QGSP_BIC;
  G4VModularPhysicsList* physicsList = new QBBC();
  physicsList->SetVerboseLevel(1);
  runManager->SetUserInitialization(physicsList);

  // User action initialization
  runManager->SetUserInitialization(new ActionInitialization());

  G4VisManager* visManager = new G4VisExecutive;
  visManager->Initialize();

  G4UImanager* UImanager = G4UImanager::GetUIpointer();

  if ( ! ui ) { 
    // batch mode
    G4String command = "/control/execute ";
    G4String fileName = argv[1];
    UImanager->ApplyCommand(command+fileName);
  }
  else { 
    // interactive mode
    UImanager->ApplyCommand("/control/execute init_vis.mac");
    ui->SessionStart();
    delete ui;
  }
  
  delete visManager;
  delete runManager;
}
