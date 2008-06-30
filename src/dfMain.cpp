#include "dfMain.h"
#include <iostream>


//--------------------------------------------------------------
void dfMain::setup(){

	//utility stuff
	universText.loadFont("LTe50144.ttf",12,false,true);
	universDisplay.loadFont("UNICBQBI.TTF",64,true,true);
	frameCount = 0;

	#ifdef _USE_LIVE_VIDEO
        sourceVideoGrabber.setVerbose(true);
        sourceVideoGrabber.initGrabber(320,240);
	#else
        sourceVideo.loadMovie("fingers.mov");
        sourceVideo.play();
	#endif
	
	sourceVideoMonitor.allocate(320,240);
	sourceVideoTexture.allocate(320,240,GL_RGBA);
	
	//displacement things
	displacementMap.allocate(320,240);
	displacementMap.set(0);
	drawingIntoDisplacement = false;
	displacedImage.allocate(320,240, GL_RGB);
	
	outputTexture.allocate(320,240,GL_RGBA);

}

//--------------------------------------------------------------
void dfMain::update(){
	//utility stuff
	ofBackground(100,100,100);
	frameCount++;
    
    bool bNewFrame = false;
	
	#ifdef _USE_LIVE_VIDEO
		sourceVideoGrabber.grabFrame();
		bNewFrame = sourceVideoGrabber.isFrameNew();
    #else
        sourceVideo.idleMovie();
        bNewFrame = sourceVideo.isFrameNew();
	#endif
	
	if (bNewFrame){
		
		#ifdef _USE_LIVE_VIDEO
            sourceVideoMonitor.setFromPixels(sourceVideoGrabber.getPixels(), 320,240);
			sourceVideoTexture.loadData(sourceVideoGrabber.getPixels(), 320,240, GL_RGB):
	    #else
            sourceVideoMonitor.setFromPixels(sourceVideo.getPixels(), 320,240);
		sourceVideoTexture.loadData(sourceVideo.getPixels(), 320,240, GL_RGB);
        #endif
		
		displacementMap.applyDisplaceMap(sourceVideoMonitor,displacedImage,0.3,0.3);
		outputTexture.loadData(sourceVideoMonitor.getPixels(),320,240,GL_RGB);

	}
	
	if(frameCount%1 == 0){
		displacementMap.fadeBy(1);
	}
	
	

	printf("%f \n", ofGetFrameRate());
}

//--------------------------------------------------------------
void dfMain::draw(){
	
	//utility things
	ofSetColor(0xffff00);
	ofRect(0, 0, 380, 90);
	ofSetColor(0xffffff);
	universDisplay.drawString("digitallyFit",15,64);

	// draw the incoming, the grayscale, the bg and the thresholded difference
	ofSetColor(0xffffff);
	sourceVideoMonitor.draw(0,85);
	universText.drawString("source",5, 100);
	displacementMap.draw(320, 85);
	if(drawingIntoDisplacement == true){
		ofSetColor(0xFF0000);
	}
	universText.drawString("displacementMap", 325, 100);
	
	ofSetColor(0xffffff);
	displacedImage.draw(320,425);
	universText.drawString("displacedImage", 325, 440);
	outputTexture.draw(640,425);
	universText.drawString("output", 645, 440);
	
	outputTexture.draw(1024,0,1024,768);
}


//--------------------------------------------------------------
void dfMain::keyPressed  (int key){ 
	
	switch (key){

	}
}

//--------------------------------------------------------------
void dfMain::mouseMoved(int x, int y ){
	int diff_x = x - last_x;
	cout <<"diff_x " << diff_x << "\r\n";
	int diff_y = y - last_y;
	cout <<"diff_y " << diff_y << "\r\n";
	if(x > 320 && x < 640 && y > 85 && y < (85 + 240)){
		drawingIntoDisplacement = true;
		displacementMap.drawIntoMeWithAtFrom(1,(x-320),(y-85), diff_x, diff_y);

	} else {
		drawingIntoDisplacement = false;
	}
	
	last_x = x;
	last_y = y;
}	

//--------------------------------------------------------------
void dfMain::mouseDragged(int x, int y, int button){
	
}

//--------------------------------------------------------------
void dfMain::mousePressed(int x, int y, int button){
}

//--------------------------------------------------------------
void dfMain::mouseReleased(){

}
