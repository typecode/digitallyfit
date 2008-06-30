#ifndef _DF_PROP
#define _DF_PROP

#define OF_ADDON_USING_OFXOPENCV
#include "ofAddons.h"

class dfProp{
	
public:
	dfProp();
	
	void loadBrush();
	
	ofTexture		brush;
	
};

#endif