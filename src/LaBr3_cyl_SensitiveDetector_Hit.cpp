#include "LaBr3_cyl_SensitiveDetector_Hit.h"
#include "G4VVisManager.hh"
#include "G4Colour.hh"
#include "G4Circle.hh"
#include "G4VisAttributes.hh"
#include "G4UnitsTable.hh"

LaBr3_cyl_SensitiveDetector_Hit::LaBr3_cyl_SensitiveDetector_Hit():fDetectorID(-1), G4VHit(), fEdep(0.), fPos(G4ThreeVector()), fTrackID(-1)  {
}

LaBr3_cyl_SensitiveDetector_Hit::~LaBr3_cyl_SensitiveDetector_Hit() {}

//Setters and Getters
void LaBr3_cyl_SensitiveDetector_Hit::SetDetectorID(G4int id) {
    fDetectorID = id;
}

G4int LaBr3_cyl_SensitiveDetector_Hit::GetDetectorID() const {
    return fDetectorID;
}

void LaBr3_cyl_SensitiveDetector_Hit::SetEdep(G4double edep) {
    fEdep = edep;
}

G4double LaBr3_cyl_SensitiveDetector_Hit::GetEdep() const {
    return fEdep;
}
void LaBr3_cyl_SensitiveDetector_Hit::SetPosition(const G4ThreeVector& pos) {
    fPos = pos;
}

G4ThreeVector LaBr3_cyl_SensitiveDetector_Hit::GetPosition() const {
    return fPos;
}


void LaBr3_cyl_SensitiveDetector_Hit::SetTrackID(G4int trackid) {
    fTrackID = trackid;
}

G4int LaBr3_cyl_SensitiveDetector_Hit::GetTrackID() const {
    return fTrackID;
}

//Visualization
void LaBr3_cyl_SensitiveDetector_Hit::Draw() {
G4VVisManager* visManager = G4VVisManager::GetConcreteInstance();
    if (!visManager) return;

    G4Circle circle(fPos);
    circle.SetScreenSize(4.0);
    circle.SetFillStyle(G4Circle::filled);
    G4Colour colour(0.0, 1.0, 0.0); // red
    G4VisAttributes attribs(colour);
    circle.SetVisAttributes(attribs);

    visManager->Draw(circle);
    }
    
 void LaBr3_cyl_SensitiveDetector_Hit::Print() {
   G4cout << "Hit: " 
           << "Detector ID = " << fDetectorID
           << ", Energy = " << G4BestUnit(fEdep,"Energy")
          // << ", Position = " << fPos
           << G4endl;
           //G4cout << "Hello from print in SD_hit"<<G4endl;//Prints this line every time in any step where dep. E = non zero: as we wrote hit->Print inside our ProcessHits() fn.
           
}   
