#include "dfDisplacementMap.h"

dfDisplacementMap::dfDisplacementMap(){
	width = 320;
	height = 240;
	brush_angle = 0;
}

dfDisplacementMap::dfDisplacementMap(int w, int h){
	width = w;
	height = h;
	brush_angle = 0;
}

void dfDisplacementMap::drawIntoMeWithAtFrom(int brushType, int x, int y, int diff_x, int diff_y){
	//determine angle of stroke
	float angle = (atan2(diff_x,diff_y))*180/PI;
	brush_angle = angle;
	
	char _r = (CLAMP(-diff_x, -32, 32) / 2);
	char _g = 127;
	char _b = (CLAMP(-diff_y, -32, 32) / 2);
	
	unsigned char * _rgbPixels = new unsigned char [width * height * 3];
	_rgbPixels = this->getPixels();
	for(int i = 0; i < width; i++){
		for(int j = 0; j < height; j++){
			float dist = sqrt(((x-i)*(x-i)) + ((y-j)*(y-j)));
			switch (brushType){
				case 1:
				default:
				if(dist < 32){
					unsigned char _newR = CLAMP(_rgbPixels[(j*width+i)*3 + 0] + (_r), 0, 255);
					unsigned char _newG = _g;
					unsigned char _newB = CLAMP(_rgbPixels[(j*width+i)*3 + 2] + (_b), 0, 255);
					_rgbPixels[(j*width+i)*3 + 0] = _newR;
					_rgbPixels[(j*width+i)*3 + 1] = _newG;
					_rgbPixels[(j*width+i)*3 + 2] = _newB;
				}
				break;
			}
		}
	}
	this->setFromPixels(_rgbPixels, width, height);	
}

void dfDisplacementMap::fadeBy(int amount){
	unsigned char * _rgbPixels = new unsigned char [width * height * 3];
	_rgbPixels = this->getPixels();
	for(int i = 0; i < width*height*3; i++){
		if(_rgbPixels[i] > 127){
			_rgbPixels[i] = MAX(0,_rgbPixels[i] - amount);	
		} else {
			_rgbPixels[i] = MAX(0,_rgbPixels[i] + amount);
		}
		
	}
	this->setFromPixels(_rgbPixels, width, height);
}

void dfDisplacementMap::applyDisplaceMap(ofxCvColorImage& sourceImage,ofTexture& destTexture,float hscale=0.3, float vscale=0.3){
    //apply displacement
    unsigned char * displacePixels  = this->getPixels();
    unsigned char * pixels          = sourceImage.getPixels();
    int displace,hdisplace,vdisplace;
    int totalPixels=height*width*3;
    unsigned char * videoDisplaced     = new unsigned char[totalPixels];
    for (int i = 0; i < totalPixels;i+=3){
        hdisplace = (int)((displacePixels[i] - 127)*hscale); //x coord
        vdisplace = (int)((displacePixels[i+2] - 127) *vscale); //y coord
        if( i%(320*3)+hdisplace*3 >0 && i%(320*3)+hdisplace*3<320*3){
            displace=hdisplace+vdisplace*320;
        }else{
            displace = 0;
        }
        displace*= 3;
        if(i+displace>0 && i+displace<totalPixels){
            videoDisplaced[i]   = pixels[i+displace];
            videoDisplaced[i+1] = pixels[i+displace+1];
            videoDisplaced[i+2] = pixels[i+displace+2];
        }
    }
    destTexture.loadData(videoDisplaced,width,height, GL_RGB);
    delete videoDisplaced;
}
