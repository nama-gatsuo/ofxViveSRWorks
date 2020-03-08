#pragma once

#pragma once
#include "SeeThroughModule.h"
#include "DepthModule.h"
#include "RigidReconstructionModule.h"

namespace ofxViveSRWorks {

	class Interface {
	public:
		Interface();
		~Interface() {}

		void init();
		void update();
		void exit();

		const ofTexture& getDistortedTexture(int i) const { return seeThrough.getDistortedTexture(i); }
		const ofTexture& getUndistortedTexture(int i) const { return seeThrough.getUndistortedTexture(i); }
		const ofTexture& getDepthTexture() const { return depth.getDepthTexture(); }
		const ofVboMesh& getMesh() const { return rigidReconstruction.getMesh(); }
		const glm::mat4& getTransform(int i) const { return seeThrough.getTransform(i); }

		void drawMesh() const;
		void drawSeeThrough(int i) { seeThrough.draw(i); }

		ofParameterGroup& getParameters() { return group; }
	private:

		SeeThroughModule seeThrough;
		DepthModule depth;
		RigidReconstructionModule rigidReconstruction;
		ofParameterGroup group;

	};


}