#ifndef LABR3_CYL_SENSITIVEDETECTOR_HH
#define LABR3_CYL_SENSITIVEDETECTOR_HH

#include "G4VSensitiveDetector.hh"
#include "LaBr3_cyl_SensitiveDetector_Hit.h"
#include "globals.hh"

class G4Step;
class G4TouchableHistory;

class LaBr3_cyl_SensitiveDetector : public G4VSensitiveDetector {
public:
    LaBr3_cyl_SensitiveDetector(const G4String& name);
    virtual ~LaBr3_cyl_SensitiveDetector();

    virtual void Initialize(G4HCofThisEvent* hce) override;
    virtual G4bool ProcessHits(G4Step* step, G4TouchableHistory* history);
    virtual void EndOfEvent(G4HCofThisEvent* hce) override;    

private:
    LaBr3_cyl_HitsCollection* fHitsCollection;
};

	extern G4int nAbs;
#endif
