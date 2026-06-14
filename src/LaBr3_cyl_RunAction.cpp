#include "LaBr3_cyl_RunAction.h"
#include "G4Run.hh"
#include "G4AnalysisManager.hh"
#include "G4SystemOfUnits.hh"
#include "LaBr3_cyl_PrimaryGeneratorAction.h"
#include "G4RunManager.hh"
#include <fstream>



// Link global metrics monitored inside the SD
extern G4int nAbs; // This now tracks ONLY full-energy photopeak events!
extern G4int nPhotopeak;

LaBr3_cyl_RunAction::LaBr3_cyl_RunAction() {}
LaBr3_cyl_RunAction::~LaBr3_cyl_RunAction() {}

void LaBr3_cyl_RunAction::BeginOfRunAction(const G4Run*) {
    // Reset performance metrics for the current execution run
    nAbs = 0;
    nPhotopeak = 0;

    G4AnalysisManager *analysisManager = G4AnalysisManager::Instance();
    analysisManager->OpenFile("output.root");
    G4cout << "Opened output.root for writing data." << G4endl;
    
    // H1 Index 0: Spectrum analysis
    analysisManager->CreateH1("Edep_cumulative", "Total energy deposited in LaBr3 det.", 2200, 0., 25 * MeV); 
    
    // H2 Index 0: Transverse interaction coordinates
    analysisManager->CreateH2("X-Y_plot", "Interaction area profile X-Y", 100, -50.*mm, 50.*mm, 100, -50.*mm, 50.*mm);
    
    // H3 Index 0: Comprehensive 3D interaction profile
    analysisManager->CreateH3("XYZ_plot", "3D Interaction Profile", 
                              60, -50.*mm, 50.*mm, 
                              60, -50.*mm, 50.*mm, 
                              100, 160.*mm, 330.*mm);
}

void LaBr3_cyl_RunAction::EndOfRunAction(const G4Run* run) {
    G4long nGenerated = run->GetNumberOfEvent();
    if (nGenerated == 0) return;

    // This is now strictly your PHOTOPEAK efficiency
    G4double photopeakEff = (G4double)nPhotopeak / nGenerated;
    G4double Abseff = (G4double)nAbs / nGenerated;

    // Fetch the active gun energy dynamically from the primary generator
    auto genAction = static_cast<const LaBr3_cyl_PrimaryGeneratorAction*>(
        G4RunManager::GetRunManager()->GetUserPrimaryGeneratorAction());
    
    G4double energy_MeV = genAction->fParticleGun->GetParticleEnergy() / MeV;

    // Append to text file
    std::ofstream outFile("PP_eff.txt", std::ios::app); 
    if (outFile.is_open()) {
        // Format: Energy(MeV)   PhotopeakEff(%)
        outFile << energy_MeV << "\t" 
                << Abseff *100.0 <<"\t"
                << photopeakEff * 100.0 << "\n";
        outFile.close();
        G4cout << ">>> [DEBUG]: Successfully wrote Photopeak data for " << energy_MeV << " MeV to PP_eff.txt" << G4endl;
    } else {
        G4cerr << ">>> [ERROR]: C++ could not open or create PP_eff.txt!" << G4endl;
    }
    
    // Terminal summary printout (Updated to reflect Photopeak Calculation)
   // G4cout << "\n=========================================================" << G4endl;
    //G4cout << "         DETECTOR PHOTOPEAK EFFICIENCY SIMULATION REPORT   " << G4endl;
    //G4cout << "=========================================================" << G4endl;
    //G4cout << " Gammas Transmitted by Gun  (N_gen) : " << nGenerated << G4endl;
   // G4cout << " Gammas In Photopeak Peak   (N_photo): " << nAbs       << G4endl;
   // G4cout << "---------------------------------------------------------" << G4endl;
   // G4cout << " >> Absolute Photopeak Eff  (eps_pp) : " << photopeakEff * 100.0 << " %" << G4endl;
   // G4cout << "=========================================================\n" << G4endl;

    G4AnalysisManager *analysisManager = G4AnalysisManager::Instance();
    analysisManager->Write();
    analysisManager->CloseFile();
    G4cout << "Analysis data successfully saved." << G4endl;
}
