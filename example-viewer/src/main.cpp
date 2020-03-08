#include "ofMain.h"
#include "ofApp.h"

int main() {

	ofGLFWWindowSettings s;
	s.setGLVersion(4, 5);
	s.setSize(1280, 960);
	ofCreateWindow(s);
	ofRunApp(new ofApp());
}
