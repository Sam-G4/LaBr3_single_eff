#ifndef LABR3_CYL_USERPHYSICSLIST_HH
#define LABR3_CYL_USERPHYSICSLIST_HH

#include "G4VUserPhysicsList.hh"

class LaBr3_cyl_UserPhysicsList : public G4VUserPhysicsList {
public:
    LaBr3_cyl_UserPhysicsList();
    virtual ~LaBr3_cyl_UserPhysicsList();
    virtual void ConstructParticle(); 
    virtual void ConstructProcess(); 
};

#endif
