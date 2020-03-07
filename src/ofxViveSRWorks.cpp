#include "ofxViveSRWorks.h"

namespace ofxViveSRWorks {
	Interface::Interface() {
		group.setName("ofxViveSRWorks");
		group.add(seeThrough.getParameters());
		group.add(depth.getParameters());
	}

	void Interface::init() {

		auto check = [&](int result, const std::string& taskName) {
			if (result != ViveSR::Error::WORK) {
				ofLogError(__FUNCTION__) << taskName << ": " << "Failed! (Code: " << result << ")";
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

		check(ViveSR_LinkModule(seeThrough.getModuleID(), depth.getModuleID(), ViveSR::LinkType::ACTIVE), "ViveSR_LinkModule");

	}

	void Interface::update() {
		seeThrough.update();
		depth.update();
	}

	void Interface::exit() {

		seeThrough.stop();
		depth.stop();

		ofLogError(__FUNCTION__) << "Exit.";
	}
}
