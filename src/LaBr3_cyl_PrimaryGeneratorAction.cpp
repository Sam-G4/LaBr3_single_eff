#include "LaBr3_cyl_PrimaryGeneratorAction.h"
#include "G4ParticleGun.hh"
#include "G4ParticleTable.hh"
#include "G4SystemOfUnits.hh"
#include "G4SystemOfUnits.hh"
#include "G4RandomTools.hh"

LaBr3_cyl_PrimaryGeneratorAction::LaBr3_cyl_PrimaryGeneratorAction() {
    G4int n_particle = 1;
    fParticleGun = new G4ParticleGun(n_particle);

       G4ParticleDefinition* particle = G4ParticleTable::GetParticleTable()->FindParticle("gamma");
    fParticleGun->SetParticleDefinition(particle);
    fParticleGun->SetParticlePosition(G4ThreeVector(0,0,0));
    fParticleGun->SetParticleEnergy(20* MeV);
    
    
    // TODO : Add your desired particles
}

LaBr3_cyl_PrimaryGeneratorAction::~LaBr3_cyl_PrimaryGeneratorAction() {
    delete fParticleGun;
}


void LaBr3_cyl_PrimaryGeneratorAction::GeneratePrimaries(G4Event* anEvent) {

    
    //TODO :  Logic to change the particle position for each event
    	G4ThreeVector randomDir = G4RandomDirection();
    fParticleGun->SetParticleMomentumDirection(randomDir);  
  
    fParticleGun->GeneratePrimaryVertex(anEvent);
}
