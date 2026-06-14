#ifndef LABR3_CYL_TRACKINGACTION_HH
#define LABR3_CYL_TRACKINGACTION_HH

#include "G4UserTrackingAction.hh"
#include "G4Track.hh"

class LaBr3_cyl_TrackingAction : public G4UserTrackingAction {
public:
    LaBr3_cyl_TrackingAction();
    virtual ~LaBr3_cyl_TrackingAction();
    virtual void PreUserTrackingAction(const G4Track *track);
    virtual void PostUserTrackingAction(const G4Track *track);
};

#endif
