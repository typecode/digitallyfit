#ifndef _DF_DISPLACEMENT_MAP
#define _DF_DISPLACEMENT_MAP

#include "dfDisplacementMap.h"

#define OF_ADDON_USING_OFXOPENCV
#include "ofAddons.h"

//some notes:
//BRUSHES---
//1: softRound
//2: 
//3: 
//4: 


class dfDisplacementMap: public ofxCvColorImage{
	
public:
	dfDisplacementMap();
	dfDisplacementMap(int w, int h);
	
	void drawIntoMeWithAtFrom(int brushType, int x, int y, int diff_x, int diff_y);
	void fadeBy(int amount);
	void applyDisplaceMap(ofxCvColorImage& sourceImage, ofTexture& destTexture, float hscale, float vscale);
	
	int		width;
	int		height;
	float	brush_angle;
};

#endif