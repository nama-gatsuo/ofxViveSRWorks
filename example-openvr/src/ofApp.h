#pragma once

#include "ofMain.h"
#include "ofxOpenVrUtil.h"
#include "ofxViveSRWorks.h"
#include "ofxGui.h"

class ofApp : public ofBaseApp{

public:
	void setup();
	void update();
	void draw();
		
	void exit();
	void keyPressed(int key);
		
private:
	void drawGrid();
	void drawScene();

	ofxOpenVrUtil::Interface vr;
	ofxViveSRWorks::Interface vive;
	std::array<ofFbo, 2> eyeFbo;

	ofEasyCam cam;
	ofxPanel panel;
};
