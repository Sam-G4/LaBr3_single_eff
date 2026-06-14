#ifndef LABR3_CYL_SENSITIVEDETECTOR_HIT_HH
#define LABR3_CYL_SENSITIVEDETECTOR_HIT_HH

#include "G4VHit.hh"
#include "G4THitsCollection.hh"
#include "G4ThreeVector.hh"

class LaBr3_cyl_SensitiveDetector_Hit : public G4VHit {
private:
	G4int fDetectorID;
	G4double fEdep;
	G4ThreeVector fPos;
	G4int fTrackID;

public:
    LaBr3_cyl_SensitiveDetector_Hit();
    virtual ~LaBr3_cyl_SensitiveDetector_Hit();
    
         // Setters and getters
    void SetDetectorID(G4int id);
    G4int GetDetectorID() const;

    void SetPosition(const G4ThreeVector& pos);
    G4ThreeVector GetPosition() const;

    void SetEdep(G4double edep);
    G4double GetEdep() const;
    
    
    void SetTrackID(const G4int trackid);
    G4int GetTrackID() const;

    // Override virtual methods for hit visualization and printing
    void Draw() override;
    void Print() override;
};

//Define the Hits Collection type
typedef G4THitsCollection<LaBr3_cyl_SensitiveDetector_Hit> LaBr3_cyl_HitsCollection;

#endif
