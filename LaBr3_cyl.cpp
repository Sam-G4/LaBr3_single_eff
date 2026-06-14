#include "G4RunManager.hh"
#include "G4UImanager.hh"
#include "QGSP_BERT.hh"
#include "G4EmStandardPhysics_option4.hh" 
#include "G4VisExecutive.hh"
#include "G4UIExecutive.hh"

#include "LaBr3_cyl_DetectorConstruction.h"
#include "LaBr3_cyl_PrimaryGeneratorAction.h"
#include "LaBr3_cyl_EventAction.h"
#include "LaBr3_cyl_RunAction.h"

int main(int argc, char** argv) {
    G4UIExecutive* ui = nullptr;
    if (argc == 1) {
        ui = new G4UIExecutive(argc, argv);
    }

    G4RunManager* runManager = new G4RunManager;
    runManager->SetUserInitialization(new LaBr3_cyl_DetectorConstruction());
    runManager->SetUserInitialization(new QGSP_BERT);
  // G4VModularPhysicsList* physicsList = new QGSP_BERT;
//physicsList->ReplacePhysics(new G4EmStandardPhysics_option4());
//runManager->SetUserInitialization(physicsList);
    runManager->SetUserAction(new LaBr3_cyl_PrimaryGeneratorAction());
    runManager->SetUserAction(new LaBr3_cyl_EventAction());
    runManager->SetUserAction(new LaBr3_cyl_RunAction());
        
    G4VisManager* visManager = new G4VisExecutive();
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
    UImanager->ApplyCommand("/control/execute vis.mac");
    ui->SessionStart();
    delete ui;
  }

    delete visManager;
    delete runManager;

    return 0;
}
