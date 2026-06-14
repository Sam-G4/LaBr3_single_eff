#include "LaBr3_cyl_SensitiveDetector.h"
#include "LaBr3_cyl_SensitiveDetector_Hit.h"
#include "G4Step.hh"
#include "G4Track.hh"
#include "G4SystemOfUnits.hh"
#include "G4AnalysisManager.hh"
#include "G4SDManager.hh"
#include "G4UnitsTable.hh"
#include "Randomize.hh"

// Global counters for efficiency calculation
G4int nAbs = 0;      // Counter for events with interactions
G4int nEntered = 0;  // Counter for primary gammas entering the crystal

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

G4bool LaBr3_cyl_SensitiveDetector::ProcessHits(G4Step* step, G4TouchableHistory*) {
    G4Track* track = step->GetTrack();
    
    // --- 1. Track Geometric Entrance ---
    // This MUST run independently of energy deposition.
    if (track->GetTrackID() == 1 && step->IsFirstStepInVolume()) {
        nEntered++;
    }

    G4double edep = step->GetTotalEnergyDeposit();
    
    // --- 2. Track Interaction (Absolute Efficiency) ---
    // If the primary gamma (or its secondary electron/compton scatter) deposits energy, count it!
    if (edep > 0.) {
        // We will increment nAbs on a per-event basis safely using a tracking flag,
        // but let's still save the hit for your ROOT histograms.
        
        LaBr3_cyl_SensitiveDetector_Hit* hit = new LaBr3_cyl_SensitiveDetector_Hit();
        G4StepPoint* prePoint = step->GetPreStepPoint();
        
        hit->SetEdep(edep);
        hit->SetPosition(prePoint->GetPosition());
        hit->SetTrackID(track->GetTrackID());
        hit->SetDetectorID(prePoint->GetTouchableHandle()->GetCopyNumber());
        
        fHitsCollection->insert(hit);
        return true;
    }
    
    return false; 
}

void LaBr3_cyl_SensitiveDetector::EndOfEvent(G4HCofThisEvent*) {
    G4int nHits = fHitsCollection->entries();
    G4double totalEdep = 0.0;
    auto analysisManager = G4AnalysisManager::Instance();
    
    // 1. Accumulate the true physical energy deposited in this event
    for (G4int i = 0; i < nHits; ++i) {
        LaBr3_cyl_SensitiveDetector_Hit* hit = (*fHitsCollection)[i];
        totalEdep += hit->GetEdep();
    }
    
    // 2. Apply Detector Resolution Smearing (4% FWHM at 662 keV)
    G4double smearedEdep = 0.0;
    if (totalEdep > 0.) {
        G4double a = 0.0648;
        G4double b = 0.0063;
        
        G4double E_MeV = totalEdep / MeV; // convert to keV as fitting done in keV
         G4double resolution = a + (b / sqrt(E_MeV));
         //if (resolution_percent < a) resolution_percent = a;
         //G4double resolution = resolution_percent / 100.0;
 	G4double sigma = resolution * totalEdep / 2.355;
 	smearedEdep = G4RandGauss::shoot(totalEdep, sigma);
    }
    
    // 3. Apply the Practical 100 keV Energy Threshold Discriminator
    G4double threshold = 100.0 * keV; 
    
    if (smearedEdep > threshold) {
        nAbs++; // Only counts as an "absorbed/detected" event if it passes the DAQ threshold
        
        // Record Total Smeared Energy Spectrum to H1 Histogram
        analysisManager->FillH1(0, smearedEdep);
        
        // Fill spatial histograms step-by-step for valid events
        for (G4int i = 0; i < nHits; ++i) {
            LaBr3_cyl_SensitiveDetector_Hit* hit = (*fHitsCollection)[i];
            G4ThreeVector pos = hit->GetPosition();
            analysisManager->FillH2(0, pos.x(), pos.y());          // X-Y Plot
            analysisManager->FillH3(0, pos.x(), pos.y(), pos.z()); // X-Y-Z Plot
        }
    }
}
