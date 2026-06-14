#include "LaBr3_cyl_TrackingAction.h"
#include "G4Step.hh"
#include "G4Track.hh"
#include "G4SystemOfUnits.hh"

LaBr3_cyl_TrackingAction::LaBr3_cyl_TrackingAction()  {
}

LaBr3_cyl_TrackingAction::~LaBr3_cyl_TrackingAction() {}

void LaBr3_cyl_TrackingAction::PreUserTrackingAction(const G4Track *track){
std::cout <<"Tracking Action begin....." << std::endl;
}

void LaBr3_cyl_TrackingAction::PostUserTrackingAction(const G4Track *track){
std::cout <<"Tracking Action ends....." << std::endl;
}

