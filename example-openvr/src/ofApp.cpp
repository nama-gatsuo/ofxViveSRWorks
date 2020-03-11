#include "ofApp.h"

void ofApp::setup() {
	ofSetVerticalSync(false);
	vr.setup();
	vive.init();

	int eyeWidth = vr.getHmd().getEyeWidth();
	int eyeHeight = vr.getHmd().getEyeHeight();

	// Let's prepare fbos to be renderred for each eye
	ofFboSettings s;
	s.width = eyeWidth;   // Actual rendering resolution is higer than display(HMD) spec has,
	s.height = eyeHeight; // because VR system will distort images like barrel distortion and fit them through lens
	s.maxFilter = GL_LINEAR;
	s.minFilter = GL_LINEAR;
	s.numSamples = 4; // MSAA enabled. Anti-Alising is much important for VR experience
	s.textureTarget = GL_TEXTURE_2D; // Can't use GL_TEXTURE_RECTANGLE_ARB which is default in oF
	s.internalformat = GL_RGBA8;
	s.useDepth = true;
	s.useStencil = true;

	for (auto& f : eyeFbo) {
		f.allocate(s);
	}

	panel.setup();
	panel.add(vive.getParameters());

}

void ofApp::update(){
	vr.update();
	vive.update();

	for (int i = 0; i < 2; i++) {
		
		eyeFbo[i].begin();
		ofClear(0);
		vr.applyEyeStencil(vr::Hmd_Eye(i));
		
		vr.beginEye(vr::Hmd_Eye(i));
		{
			vive.drawSeeThrough(i);
			drawScene();	
		}		
		vr.endEye();
		eyeFbo[i].end();

		// Submit texture to VR!
		vr.submit(eyeFbo[i].getTexture(), vr::EVREye(i));
	}

}

void ofApp::draw(){
	

	cam.begin();
	ofEnableDepthTest();
	ofScale(200.f);
	ofTranslate(0, -1.f, 0);
	{
		drawScene();
		//vive.drawSeeThrough(0);
		//vive.drawSeeThrough(1);
		vr.debugDraw();
	}
	ofDisableDepthTest();
	cam.end();

	int w = vr.getHmd().getEyeWidth() / 8.f;
	int h = vr.getHmd().getEyeHeight() / 8.f;

	ofPushMatrix();
	ofTranslate(0, h);
	ofScale(1, -1); // Flipping
	eyeFbo[vr::Eye_Left].draw(0, 0, w, h);
	eyeFbo[vr::Eye_Right].draw(w, 0, w, h);
	ofPopMatrix();

	panel.draw();
	ofDrawBitmapString("fps: " + ofToString(ofGetFrameRate()), 12, 16);
	
}

void ofApp::drawScene() {

	drawGrid();
	vive.drawMesh();

	for (auto& c : vr.getControllers()) {
		c.second->draw();
	}

}


void ofApp::exit() {
	vr.exit();
	vive.exit();
}

void ofApp::keyPressed(int key) {}

void ofApp::drawGrid() {
	ofPushStyle();
	{
		ofSetColor(100);
		for (float x = -1.5f; x <= 1.5f; x += 1.f) {
			ofDrawLine(x, 0, -2.f, x, 0, 2.f);
		}
		for (float y = -1.5f; y <= 1.5f; y += 1.f) {
			ofDrawLine(-2.f, 0, y, 2.f, 0, y);
		}
	}
	{
		ofSetColor(196);
		for (float x = -2.f; x <= 2.f; x += 1.f) {
			if (x != 0.f) ofDrawLine(x, 0, -2.f, x, 0, 2.f);
		}
		for (float y = -2.f; y <= 2.f; y += 1.f) {
			if (y != 0.f) ofDrawLine(-2.f, 0, y, 2.f, 0, y);
		}
	}

	ofSetColor(255, 0, 128);
	ofDrawLine(-2.f, 0, 0, 2.f, 0, 0);
	ofDrawLine(0, 0, -2.f, 0, 0, 2.f);

	ofPopStyle();
}


