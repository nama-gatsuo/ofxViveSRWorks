#include "ofxViveSRWorks.h"
#include "ofGraphics.h"

namespace ofxViveSRWorks {
	Interface::Interface() {
		group.setName("ofxViveSRWorks");
		group.add(seeThrough.getParameters());
		group.add(depth.getParameters());
		group.add(rigidReconstruction.getParameters());

		std::string path = "../../../../../addons/ofxViveSRWorks/shader/";
		meshShader.load(path + "meshShader");
		pointShader.load(path + "pointShader");
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

	void Interface::updateDepthMask(const glm::mat4& eyeTransform) {
		
	}

	void Interface::exit() {
		seeThrough.stop();
		depth.stop();
		rigidReconstruction.stop();

		ofLogNotice(__FUNCTION__) << "Exit.";
	}
	void Interface::drawMesh(ofPolyRenderMode mode) const {
		rigidReconstruction.getMesh().draw(mode);
	}

	void Interface::applyMask() {
		/*
		// Alpha mask by point cloud of real-time sensing
		// This provides very poor acculacy... That's why I comment-outed
		glEnable(GL_POINT_SPRITE);
		glEnable(GL_VERTEX_PROGRAM_POINT_SIZE);
		glEnable(GL_CLIP_DISTANCE0);

		pointShader.begin();
		pointShader.setUniform1f("depthClip", 1.2f);
		rigidReconstruction.getPointCloud().draw();
		pointShader.end();

		glDisable(GL_CLIP_DISTANCE0);
		glDisable(GL_POINT_SPRITE);
		glDisable(GL_VERTEX_PROGRAM_POINT_SIZE);
		*/

		meshShader.begin();
		rigidReconstruction.getMesh().draw();
		meshShader.end();

	}

	

}
