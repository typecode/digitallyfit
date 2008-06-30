#ifndef _DF_PROP_MANAGER
#define _DF_PROP_MANAGER

#define OF_ADDON_USING_OFXOPENCV
#include "ofAddons.h"

#include "dfProp.h"
#include "ofFiducialFinder.h"

class dfPropManager{
	
public:
	dfPropManager();
	
	int					numberOfProps;
	vector<dfProp> 		props;
	
	//fiducial stuff
	ofFiducialFinder	fiducialFinder;
	
};

#endif