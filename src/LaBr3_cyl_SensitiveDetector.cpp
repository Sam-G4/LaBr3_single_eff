#include "LaBr3_cyl_SensitiveDetector.h"
#include "LaBr3_cyl_SensitiveDetector_Hit.h"
#include "G4Step.hh"
#include "G4Track.hh"
#include "G4SystemOfUnits.hh"
#include "G4AnalysisManager.hh"
#include "G4SDManager.hh"
#include "G4UnitsTable.hh"
#include "Randomize.hh"
#include "LaBr3_cyl_PrimaryGeneratorAction.h"
#include "G4RunManager.hh"     // Fixes: ‘G4RunManager’ has not been declared
#include "G4MTRunManager.hh"   // Fixes: ‘G4MTRunManager’ has not been declared
#include "G4Event.hh"

// Global counters for efficiency calculation
G4int nAbs = 0;      // Counter for events with interactions
//G4int nEntered = 0;  // Counter for primary gammas entering the crystal
G4int nPhotopeak = 0;

LaBr3_cyl_SensitiveDetector::LaBr3_cyl_SensitiveDetector(const G4String& name) 
    : G4VSensitiveDetector(name), fHitsCollection(nullptr) { 
    collectionName.insert("LaBr3_cyl_HitsCollection");
}

LaBr3_cyl_SensitiveDetector::~LaBr3_cyl_SensitiveDetector() {}

void LaBr3_cyl_SensitiveDetector::Initialize(G4HCofThisEvent* hce) {
    fHitsCollection = new LaBr3_cyl_HitsCollection(SensitiveDetectorName, collectionName[0]);
    static G4int hcID = -1;
    if (hcID < 0) {
        hcID = G4SDManager::GetSDMpointer()->GetCollectionID(fHitsCollection);
    }
    hce->AddHitsCollection(hcID, fHitsCollection);
}

G4bool LaBr3_cyl_SensitiveDetector::ProcessHits(G4Step* step,
                                                G4TouchableHistory*)
{
    G4double edep = step->GetTotalEnergyDeposit();

    if (edep <= 0.) return false;

    LaBr3_cyl_SensitiveDetector_Hit* hit =
        new LaBr3_cyl_SensitiveDetector_Hit();

    G4StepPoint* prePoint = step->GetPreStepPoint();

    hit->SetEdep(edep);
    hit->SetPosition(prePoint->GetPosition());
    hit->SetTrackID(step->GetTrack()->GetTrackID());
    hit->SetDetectorID(prePoint->GetTouchableHandle()->GetCopyNumber());

    fHitsCollection->insert(hit);

    return true;
}
void LaBr3_cyl_SensitiveDetector::EndOfEvent(G4HCofThisEvent*)
{
    G4int nHits = fHitsCollection->entries();
    G4double totalEdep = 0.0;
    auto analysisManager = G4AnalysisManager::Instance();

    // Sum energy deposited in this event
    for (G4int i = 0; i < nHits; ++i) {
        LaBr3_cyl_SensitiveDetector_Hit* hit = (*fHitsCollection)[i];
        totalEdep += hit->GetEdep();
    }

    // Energy resolution smearing
    G4double smearedEdep = 0.0;
    G4double sigma = 0.0;
    G4double Egamma = 0.0;

    if (totalEdep > 0.) {
        G4double a = 0.0648;
        G4double b = 0.0063;

        G4double E_MeV = totalEdep / MeV;
        G4double resolution = a + b/std::sqrt(E_MeV);

        sigma = resolution * totalEdep / 2.355;
        smearedEdep = G4RandGauss::shoot(totalEdep, sigma);
 ///debug       G4cout << "sigma = " << sigma << G4endl;
    }

    // Detection threshold
  // Detection threshold
    G4double threshold = 100.0 * keV;

    if (smearedEdep > threshold) {
        // Count ONE detected event (Absolute interaction)
        nAbs++;
        analysisManager->FillH1(0, smearedEdep);

        // Fill hit positions
        for (G4int i = 0; i < nHits; ++i) {
            LaBr3_cyl_SensitiveDetector_Hit* hit = (*fHitsCollection)[i];
            G4ThreeVector pos = hit->GetPosition();
            analysisManager->FillH2(0, pos.x(), pos.y());
            analysisManager->FillH3(0, pos.x(), pos.y(), pos.z());
        }

        // --- FIXED PHOTOPEAK LOGIC BLOCK ---
      
        
        // 1. Fetch the incident particle energy dynamically from the current event
        const G4Event* currentEvent = G4RunManager::GetRunManager()->GetCurrentEvent();
        if (!currentEvent) {
            currentEvent = G4MTRunManager::GetMasterRunManager()->GetCurrentEvent();
        }

        if (currentEvent && currentEvent->GetNumberOfPrimaryVertex() > 0) {
            G4PrimaryVertex* vertex = currentEvent->GetPrimaryVertex(0);
            if (vertex && vertex->GetNumberOfParticle() > 0) {
                G4PrimaryParticle* primary = vertex->GetPrimary(0);
                if (primary) {
                    Egamma = primary->GetKineticEnergy();
                }
            }
        }

        // 2. Define your window bounds (Using a safe 3-sigma gate for floating-point smearing)
        G4double lowerBound = Egamma - (1.0 * sigma);
        G4double upperBound = Egamma + (1.0 * sigma);
  //debug G4cout << "Egamma = " << Egamma << "lower boound = " << lowerBound<< "Up_bnd = " << upperBound << G4endl;
         //debug  G4cout << "sigma2 = " << sigma << G4endl;
        // 3. Evaluate the conditional check using logical AND (&&)
        if (smearedEdep >= lowerBound && smearedEdep <= upperBound) {
            nPhotopeak++; // Successfully captured a full-energy peak event!
        }
    }
    }
