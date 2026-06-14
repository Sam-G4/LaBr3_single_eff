#ifndef LABR3_CYL_DETECTORCONSTRUCTION_HH
#define LABR3_CYL_DETECTORCONSTRUCTION_HH

#include "G4VUserDetectorConstruction.hh"

class LaBr3_cyl_DetectorConstruction : public G4VUserDetectorConstruction {
public:
    LaBr3_cyl_DetectorConstruction();
    virtual ~LaBr3_cyl_DetectorConstruction();

    virtual G4VPhysicalVolume* Construct();
};

#endif
