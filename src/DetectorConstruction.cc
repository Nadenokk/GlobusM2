#include "DetectorConstruction.hh"

#include "G4RunManager.hh"
#include "G4NistManager.hh"
#include "G4LogicalVolume.hh"
#include "G4VPVParameterisation.hh"
#include "G4PVPlacement.hh"
#include "G4SystemOfUnits.hh"
#include "SensitiveDetector.hh"
#include "G4SDManager.hh"
#include "G4GlobalMagFieldMessenger.hh"
#include "G4GDMLParser.hh"

#include <iostream>

using namespace std;

DetectorConstruction::DetectorConstruction()
        : G4VUserDetectorConstruction(), fScoringVolume(0) {
}

DetectorConstruction::~DetectorConstruction() {
    time_t now = time(0);
    string tm = ctime(&now);
    ofstream out("output.txt", ios::app);
    out << " time:" << tm.erase(tm.size() - 1) << " SUMMA CONTS:" << detector1->getSummaCounts()
        << " " << detector2->getSummaCounts() << G4endl;
    out.close();
    //G4cout <<"Destroy DetectorConstruction "<< G4endl;
}

G4VPhysicalVolume *DetectorConstruction::Construct() {

    G4NistManager *nist = G4NistManager::Instance();

    G4bool checkOverlaps = true;

    G4ThreeVector pos = G4ThreeVector(0 * cm, 0 * cm, 0 * cm);
    //G4Material* env_mat = nist->FindOrBuildMaterial("G4_Galactic");
    G4Material *env_mat = nist->FindOrBuildMaterial("G4_AIR");

    G4GDMLParser parser;
    parser.SetOverlapCheck(true);
    parser.Read("GDML/world.gdml");

    G4LogicalVolume *logicEnv = parser.GetVolume("world_volume");
    logicEnv->SetMaterial(env_mat);
    G4VPhysicalVolume *physWorld = parser.GetWorldVolume("world_volume");


    //Zal
    G4GDMLParser parserGround;
    parserGround.SetOverlapCheck(true);
    parserGround.Read("GDML/Ground.gdml");
    G4LogicalVolume *logiclGround = parserGround.GetVolume("Ground");
    new G4PVPlacement(0, G4ThreeVector(), "Ground", logiclGround, physWorld, false, 0, checkOverlaps);

    G4GDMLParser parserConcrete;
    parserConcrete.SetOverlapCheck(true);
    parserConcrete.Read("GDML/Zal_Concrete.gdml");
    G4LogicalVolume *logiclConcrete = parserConcrete.GetVolume("Zal_Concrete");
    G4VPhysicalVolume *physConcrete = new G4PVPlacement(0, G4ThreeVector(), "Zal_Concrete", logiclConcrete, physWorld,
                                                        false, 0, checkOverlaps);


    G4GDMLParser parserCeramicBrick;
    parserCeramicBrick.SetOverlapCheck(true);
    parserCeramicBrick.Read("GDML/Zal_CeramicBrick.gdml");
    G4LogicalVolume *logicalCeramicBrick = parserCeramicBrick.GetVolume("Zal_CeramicBrick");
    G4VPhysicalVolume *physCeramicBrick = new G4PVPlacement(0, G4ThreeVector(), "Zal_CeramicBrick", logicalCeramicBrick,
                                                            physWorld, false, 0, checkOverlaps);

    G4GDMLParser parserZalQ235;
    parserZalQ235.SetOverlapCheck(true);
    parserZalQ235.Read("GDML/Zal_Q235.gdml");
    G4LogicalVolume *logicalZalQ235 = parserZalQ235.GetVolume("Zal_Q235");
    new G4PVPlacement(0, pos, "Zal_Q235", logicalZalQ235,
                      physWorld, false, 0, checkOverlaps);

    G4GDMLParser parserZalGlass;
    parserZalGlass.SetOverlapCheck(true);
    parserZalGlass.Read("GDML/Zal_Glass.gdml");
    G4LogicalVolume *logicalZalGlass = parserZalGlass.GetVolume("Zal_Glass");
    new G4PVPlacement(0, pos, "Zal_Glass", logicalZalGlass,
                      physWorld, false, 0, checkOverlaps);

    G4GDMLParser parserZalMineralSlabs;
    parserZalMineralSlabs.SetOverlapCheck(true);
    parserZalMineralSlabs.Read("GDML/Zal_MineralSlabs.gdml");
    G4LogicalVolume *logocalZalMineralSlabs = parserZalMineralSlabs.GetVolume("Zal_MineralSlabs");
    new G4PVPlacement(0, pos, "Zal_MineralSlabs", logocalZalMineralSlabs,
                      physWorld, false, 0, checkOverlaps);

    G4GDMLParser parserZalRoofingFelt;
    parserZalRoofingFelt.SetOverlapCheck(true);
    parserZalRoofingFelt.Read("GDML/Zal_RoofingFelt.gdml");
    G4LogicalVolume *logicalZalRoofingFelt = parserZalRoofingFelt.GetVolume("Zal_RoofingFelt");
    new G4PVPlacement(0, pos, "Zal_RoofingFelt", logicalZalRoofingFelt,
                      physWorld, false, 0, checkOverlaps);


    //Tokamak
    G4GDMLParser parserQ235;
    parserQ235.SetOverlapCheck(true);
    parserQ235.Read("GDML/Tokamak_Q235.gdml");
    G4LogicalVolume *logicalTokamakQ235 = parserQ235.GetVolume("Tokamak_Q235");
    G4VPhysicalVolume *physTokamakQ235 = new G4PVPlacement(0, pos, "Tokamak_Q235", logicalTokamakQ235,
                                                           physWorld, false, 0, checkOverlaps);

    G4GDMLParser parserWood;
    parserWood.SetOverlapCheck(true);
    parserWood.Read("GDML/Tokamak_Wood.gdml");
    G4LogicalVolume *logicalTokamakWood = parserWood.GetVolume("Tokamak_Wood");
    new G4PVPlacement(0, pos, "Tokamak_Wood", logicalTokamakWood,
                      physWorld, false, 0, checkOverlaps);

    G4GDMLParser parserCopper;
    parserCopper.SetOverlapCheck(true);
    parserCopper.Read("GDML/Tokamak_Copper.gdml");
    G4LogicalVolume *logicalTokamakCopper = parserCopper.GetVolume("Tokamak_Copper");
    new G4PVPlacement(0, pos, "Tokamak_Copper", logicalTokamakCopper,
                      physWorld, false, 0, checkOverlaps);

    G4GDMLParser parserGraphite;
    parserGraphite.SetOverlapCheck(true);
    parserGraphite.Read("GDML/Tokamak_Graphite.gdml");
    G4LogicalVolume *logicalGraphite = parserGraphite.GetVolume("Tokamak_Graphite");
    new G4PVPlacement(0, pos, "Tokamak_Graphite", logicalGraphite,
                      physWorld, false, 0, checkOverlaps);


    G4ThreeVector pos1 = G4ThreeVector(-4812 + 7990, -2660 + 16060, 1056 + 3144);
    //G4ThreeVector pos1 = G4ThreeVector(-4812 + 7990, -2660 +16060 , 850 + 3000);

    G4ThreeVector pos2 = G4ThreeVector(2077 + 7990, -12610 + 16060, 1056 + 3144);
    // G4ThreeVector pos2 = G4ThreeVector(677.50 + 7990, -2760 +16060 , 850 + 3000);

    G4GDMLParser parserDetector1;
    parserDetector1.SetOverlapCheck(true);
    parserDetector1.Read("GDML/schetchik-Detector1.gdml");
    G4LogicalVolume *logicalDetector1 = parserDetector1.GetVolume("Detector1");
    logicalDetector1->SetMaterial(nist->FindOrBuildMaterial("G4_AIR"));
    G4VPhysicalVolume *physDetector1 = new G4PVPlacement(0, pos1, "Detector", logicalDetector1,
                                                         physWorld, false, 0, checkOverlaps);

    G4GDMLParser parserDetector2;
    parserDetector2.SetOverlapCheck(true);
    parserDetector2.Read("GDML/schetchik-Detector2.gdml");
    G4LogicalVolume *logicalDetector2 = parserDetector2.GetVolume("Detector2");
    logicalDetector2->SetMaterial(nist->FindOrBuildMaterial("G4_AIR"));
    G4VPhysicalVolume *physDetector2 = new G4PVPlacement(0, pos2, "Detector2", logicalDetector2,
                                                         physWorld, false, 0, checkOverlaps);

    G4GDMLParser parserSchetPolietilen;
    parserSchetPolietilen.SetOverlapCheck(true);
    parserSchetPolietilen.Read("GDML/schetchik-Polietilen.gdml");
    G4GDMLParser parserSchetSilicon;
    parserSchetSilicon.SetOverlapCheck(true);
    parserSchetSilicon.Read("GDML/schetchik-Silicon.gdml");

    G4LogicalVolume *logicalSchetPolietilen = parserSchetPolietilen.GetVolume("schetchik-Polietilen");
    logicalSchetPolietilen->SetMaterial(nist->FindOrBuildMaterial("G4_POLYETHYLENE"));
    new G4PVPlacement(0, pos1, "schetchik_Polietilen", logicalSchetPolietilen,
                      physWorld, false, 0, checkOverlaps);

    G4LogicalVolume *logicalSchetSilicon = parserSchetSilicon.GetVolume("schetchik-Silicon");
    new G4PVPlacement(0, pos1, "schetchik-Silicon", logicalSchetSilicon,
                      physWorld, false, 0, checkOverlaps);

    G4GDMLParser parserSchetPolietilen2;
    parserSchetPolietilen2.SetOverlapCheck(true);
    parserSchetPolietilen2.Read("GDML/schetchik-Polietilen2.gdml");
    G4GDMLParser parserSchetSilicon2;
    parserSchetSilicon2.SetOverlapCheck(true);
    parserSchetSilicon2.Read("GDML/schetchik-Silicon2.gdml");

    G4LogicalVolume *logicalSchetPolietilen2 = parserSchetPolietilen2.GetVolume("schetchik-Polietilen2");
    logicalSchetPolietilen2->SetMaterial(nist->FindOrBuildMaterial("G4_POLYETHYLENE"));
    new G4PVPlacement(0, pos2, "schetchik_Polietilen2", logicalSchetPolietilen2,
                      physWorld, false, 0, checkOverlaps);

    G4LogicalVolume *logicalSchetSilicon2 = parserSchetSilicon2.GetVolume("schetchik-Silicon2");
    new G4PVPlacement(0, pos2, "schetchik-Silicon2", logicalSchetSilicon2,
                      physWorld, false, 0, checkOverlaps);

    fScoringVolume.insert(fScoringVolume.end(), logicalDetector1);
    fScoringVolume.insert(fScoringVolume.end(), logicalDetector2);

    return physWorld;
}

void DetectorConstruction::ConstructSDandField() {
    detector1 = new SensitiveDetector("Detector1");
    G4SDManager::GetSDMpointer()->AddNewDetector(detector1);
    SetSensitiveDetector("Detector1", detector1, true);

    detector2 = new SensitiveDetector("Detector2");
    G4SDManager::GetSDMpointer()->AddNewDetector(detector2);
    SetSensitiveDetector("Detector2", detector2, true);

}
