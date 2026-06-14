#ifndef LABR3_CYL_PRIMARYGENERATORACTION_HH
#define LABR3_CYL_PRIMARYGENERATORACTION_HH

#include "G4VUserPrimaryGeneratorAction.hh"
#include "G4ParticleGun.hh"

class LaBr3_cyl_PrimaryGeneratorAction : public G4VUserPrimaryGeneratorAction {
public:
    LaBr3_cyl_PrimaryGeneratorAction();
    virtual ~LaBr3_cyl_PrimaryGeneratorAction();

    virtual void GeneratePrimaries(G4Event* anEvent);
public:
    G4ParticleGun *fParticleGun;
};

#endif
