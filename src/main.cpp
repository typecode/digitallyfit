#include "ofMain.h"
#include "dfMain.h"

//========================================================================
int main( ){

	ofSetupOpenGL(2048,768, OF_WINDOW);			// <-------- setup the GL context
	
	ofRunApp(new dfMain());
	
}
