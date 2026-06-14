#include "LaBr3_cyl_DetectorConstruction.h"
#include "G4Box.hh"
#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"
#include "G4NistManager.hh"
#include "LaBr3_cyl_SensitiveDetector.h"
#include "G4SDManager.hh"
#include "G4SystemOfUnits.hh"

#include "G4Tubs.hh"
#include "G4Material.hh"
#include "G4Element.hh"

LaBr3_cyl_DetectorConstruction::LaBr3_cyl_DetectorConstruction() {}

LaBr3_cyl_DetectorConstruction::~LaBr3_cyl_DetectorConstruction() {}

G4VPhysicalVolume* LaBr3_cyl_DetectorConstruction::Construct() {
    G4NistManager* nist = G4NistManager::Instance();
    
    // --- Materials ---
    G4Material* worldMat = nist->FindOrBuildMaterial("G4_AIR");
    G4Material* ssMat    = nist->FindOrBuildMaterial("G4_STAINLESS-STEEL");
    
    G4Element* La = nist->FindOrBuildElement("La");
    G4Element* Br = nist->FindOrBuildElement("Br");

    G4double density = 5.29 * g/cm3; 
    G4Material* LaBr3Ce = new G4Material("LaBr3Ce", density, 2);
    LaBr3Ce->AddElement(La, 1);
    LaBr3Ce->AddElement(Br, 3);
    
    // --- World Volume ---
    G4Box* solidWorld = new G4Box("World", 0.5*m, 0.5*m, 0.5*m);
    G4LogicalVolume* logicWorld = new G4LogicalVolume(solidWorld, worldMat, "World");
    G4VPhysicalVolume* physWorld = new G4PVPlacement(nullptr, G4ThreeVector(), logicWorld, "World", nullptr, false, 0);
    
    // --- Dimensions ---
    G4double crystalRadius     = 3.81 * cm;       // 3" diameter -> 1.5" radius
    G4double crystalHalfLength = (15.24 / 2.0) * cm; // 6" length
    G4double housingThickness  = 0.3 * cm;        // 3 mm Stainless Steel
    
    // Distance from source (0,0,0) to the FRONT face of the SS housing = 16.5 cm
    G4double targetDistanceToHousingFace = 16.5 * cm;
    
    // Center of the housing and crystal along Z-axis
    G4double housingZCenter = targetDistanceToHousingFace + crystalHalfLength + housingThickness;
    G4double crystalZCenter = housingZCenter; // Aligned perfectly inside

    // --- 1. Stainless Steel Housing ---
    // Make it wide enough to wrap the radius, and long enough to cover the front/back faces
    G4double housingOuterRadius = crystalRadius + housingThickness;
    G4double housingOuterHalfLength = crystalHalfLength + housingThickness;

    G4Tubs* solidHousing = new G4Tubs("SS_Housing", 0., housingOuterRadius, housingOuterHalfLength, 0., 360.*deg);
    G4LogicalVolume* logicHousing = new G4LogicalVolume(solidHousing, ssMat, "Logic_Housing");
    
    new G4PVPlacement(nullptr, G4ThreeVector(0, 0, housingZCenter), logicHousing, "Phy_Housing", logicWorld, false, 0, true);

    // --- 2. LaBr3:Ce Crystal (Placed INSIDE the Housing) ---
    G4Tubs* solidLaBr3_cyl = new G4Tubs("LaBr3_cyl", 0., crystalRadius, crystalHalfLength, 0., 360.*deg);
    G4LogicalVolume* logicLaBr3_cyl = new G4LogicalVolume(solidLaBr3_cyl, LaBr3Ce, "Logic_cyl");
    
    // Placed relative to the mother volume (logicHousing), so local center is (0,0,0)
    new G4PVPlacement(nullptr, G4ThreeVector(0, 0, 0), logicLaBr3_cyl, "PhyLaBr3_cyl", logicHousing, false, 0, true);

    // --- Sensitive Detector Setup ---
    LaBr3_cyl_SensitiveDetector* detector = new LaBr3_cyl_SensitiveDetector("SensitiveDetector");
    G4SDManager::GetSDMpointer()->AddNewDetector(detector);
    logicLaBr3_cyl->SetSensitiveDetector(detector);

    return physWorld;
}
