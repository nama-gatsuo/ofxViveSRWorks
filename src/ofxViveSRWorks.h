#pragma once

#include "SeeThroughModule.h"
#include "DepthModule.h"

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

		ofParameterGroup& getParameters() { return group; }
	private:
		
		SeeThroughModule seeThrough;
		DepthModule depth;
		ofParameterGroup group;

	};


}