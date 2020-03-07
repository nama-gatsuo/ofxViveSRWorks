#include "ofApp.h"

void ofApp::setup() {
	vive.init();

	panel.setup();
	panel.add(vive.getParameters());
}

void ofApp::update() {
	vive.update();
}

void ofApp::draw() {
	ofDisableAlphaBlending();
	
	auto& depth = vive.getDepthTexture();
	depth.draw(0, 0, depth.getWidth() / 2, depth.getHeight() / 2);
	float h = depth.getHeight() / 2;

	for (int i = 0; i < 2; i++) {
		auto& undistorted = vive.getUndistortedTexture(i);
		undistorted.draw(i * undistorted.getWidth() / 2, h, undistorted.getWidth() / 2, undistorted.getHeight() / 2);
	}

	ofEnableAlphaBlending();
	ofDrawBitmapString("FPS: " + ofToString(ofGetFrameRate()), 12, 16);

	panel.draw();
}

void ofApp::exit() {
	vive.exit();
}
