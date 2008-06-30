#ifndef _DF_MAIN
#define _DF_MAIN

#include "ofMain.h"

#define OF_ADDON_USING_OFXOPENCV
#include "ofAddons.h"


//custom classes
#include "dfDisplacementMap.h"
#include "dfPropManager.h"

//#define _USE_LIVE_VIDEO		// uncomment this to use a live camera
								// otherwise, we'll use a movie file


class dfMain : public ofSimpleApp{

	public:

		void setup();
		void update();
		void draw();

		void keyPressed  (int key);
		void mouseMoved(int x, int y );
		//last mouse positions
		int				last_x, last_y;
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased();
	
		//utility things, ie fonts and logos etc
		ofTrueTypeFont			universText;
		ofTrueTypeFont			universDisplay;
		int						frameCount;
	
        #ifdef _USE_LIVE_VIDEO
			ofVideoGrabber		sourceVideoGrabber;
		#else
			ofVideoPlayer 		sourceVideo;
		#endif
	
		ofxCvColorImage			sourceVideoMonitor;
		ofTexture				sourceVideoTexture;
	
		ofFiducialFinder		fiducialFinder;
	
		//displacement map stuff
		dfDisplacementMap		displacementMap;
		bool					drawingIntoDisplacement;
	
		//output stuff
		ofTexture				displacedImage;
		ofTexture				outputTexture;
		
};

#endif
