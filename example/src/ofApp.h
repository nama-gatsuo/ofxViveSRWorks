#pragma once

#include "ofMain.h"
#include "ofxViveSRWorks.h"
#include "ofxGui.h"

class ofApp : public ofBaseApp {
public:
	void setup();
	void update();
	void draw();

	void exit();
private:
	ofxViveSRWorks::Interface vive;
	ofxPanel panel;
	ofShader shader;
	ofEasyCam cam;
};
