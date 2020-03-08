#include "ofApp.h"

void ofApp::setup() {
	vive.init();
	panel.setup();
	panel.add(vive.getParameters());
	cam.disableMouseInput();
	cam.setDistance(0.0001f);
	cam.lookAt(glm::vec3(0, 0, -1), glm::vec3(0, 1, 0));
	cam.setNearClip(0.01f);
	cam.enableMouseInput();

	depthScaler.load("shader/shader");
}

void ofApp::update() {
	vive.update();
}

void ofApp::draw() {
	ofDisableAlphaBlending();
	auto& depth = vive.getDepthTexture();
	depthScaler.begin();
	depth.draw(0, 0, depth.getWidth(), depth.getHeight());
	depthScaler.end();
	ofDrawBitmapStringHighlight("Raw Depth", 0, 12);

	float h = depth.getHeight();

	for (int i = 0; i < 2; i++) {
		auto& undistorted = vive.getUndistortedTexture(i);
		undistorted.draw(i * depth.getWidth(), h, depth.getWidth(), depth.getWidth() / undistorted.getWidth() * undistorted.getHeight());
		ofDrawBitmapStringHighlight("Distorted Eye Camera " + ofToString(i), i * depth.getWidth(), h + 12);
	}
	ofEnableAlphaBlending();

	auto rect = ofRectangle(depth.getWidth(), 0, depth.getWidth(), depth.getHeight());
	vive.getDistortedTexture(0).draw(rect);

	cam.setControlArea(rect);
	ofPushView();
	
	ofViewport(rect.x, rect.y, rect.width, rect.height, true);
	cam.begin();
	ofScale(1, 1, -1);
	ofMultMatrix(glm::inverse(vive.getTransform(0))); // ModelView Projection
	vive.drawMesh();
	cam.end();
	ofPopView();
	ofDrawBitmapStringHighlight("Reconstructed Mesh", depth.getWidth(), 12);
	
	ofDrawBitmapString("FPS: " + ofToString(ofGetFrameRate()), 12, ofGetHeight() - 30);

	panel.draw();
}

void ofApp::exit() {
	vive.exit();
}
