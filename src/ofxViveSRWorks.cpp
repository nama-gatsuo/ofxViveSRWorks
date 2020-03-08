#include "ofxViveSRWorks.h"
#include "ofGraphics.h"

namespace ofxViveSRWorks {
	Interface::Interface() {
		group.setName("ofxViveSRWorks");
		group.add(seeThrough.getParameters());
		group.add(depth.getParameters());
		group.add(rigidReconstruction.getParameters());
	}

	void Interface::init() {

		auto check = [&](int result, const std::string& taskName) {
			if (result != ViveSR::Error::WORK) {
				ofLogError("ofxViveSRWorks::Interface::init") << taskName << ": " << "Failed! (Code: " << result << ")";
			}
		};

		if (ViveSR_GetContextInfo(NULL) != ViveSR::Error::WORK) {
			check(ViveSR_CreateContext("", 0), "ViveSR_CreateContext");
		}
		char* buf = new char[16];
		ViveSR_GetVersion(&buf);
		ofLogNotice(__FUNCTION__) << buf;

		seeThrough.start();
		depth.start();
		rigidReconstruction.start();

		check(ViveSR_LinkModule(seeThrough.getModuleID(), depth.getModuleID(), ViveSR::LinkType::ACTIVE), "ViveSR_LinkModule");
		check(ViveSR_LinkModule(depth.getModuleID(), rigidReconstruction.getModuleID(), ViveSR::LinkType::ACTIVE), "ViveSR_LinkModule");

	}

	void Interface::update() {
		seeThrough.update();
		depth.update();
		rigidReconstruction.update();
	}

	void Interface::exit() {

		seeThrough.stop();
		depth.stop();
		rigidReconstruction.stop();

		ofLogNotice(__FUNCTION__) << "Exit.";
	}
	void Interface::drawMesh() const {
		ofPushMatrix();
		rigidReconstruction.getMesh().draw(OF_MESH_WIREFRAME);
		ofPopMatrix();
	}
}
