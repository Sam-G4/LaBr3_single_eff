#ifndef LABR3_CYL_EVENTACTION_HH
#define LABR3_CYL_EVENTACTION_HH

#include "G4UserEventAction.hh"
#include "G4Event.hh"
class LaBr3_cyl_EventAction : public G4UserEventAction {

	double Edep;
	G4int nAbs;
	
public:
    LaBr3_cyl_EventAction();
    virtual ~LaBr3_cyl_EventAction();
    virtual void BeginOfEventAction(const G4Event *event);
    virtual void EndOfEventAction(const G4Event *event);
    
     void AddEdep_E(G4double edep);
};

#endif
