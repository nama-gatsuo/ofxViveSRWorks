#pragma once
#include "ofLog.h"
#include "ofTexture.h"
#include "ofUtils.h"
#include <array>
#include "ofVectorMath.h"
#include "ofParameter.h"

#include "ViveSR_Enums.h"
#include "ViveSR_API_Enums.h"
#include "ViveSR_Client.h"
#include "ViveSR_Structs.h"
#include "ViveSR_DepthEnums.h"
//#include "ViveSR_SeeThroughEnums.h"

namespace ofxViveSRWorks {
	class DepthModule {
	public:
		DepthModule();
		~DepthModule();

		void start();
		void update();
		void stop();

		int getModuleID() const { return moduleID; }
		ofParameterGroup& getParameters() { return group; }
		const ofTexture& getDepthTexture() const { return depthTex; }
		const ofTexture& getColorTexture() const { return colorTex; }

	private:
		int moduleID;
		struct Unit {
			std::unique_ptr<uint8_t[]> colorFrame;
			std::unique_ptr<float[]> depthFrame;
			glm::mat4 pose;
			int lux;
			int colorTemperature;
			int exposureTime;
			int analogGain;
			int digitalGain;
		} unit;

		glm::ivec2 size;
		int depthChannel, colorChannel;

		unsigned int frameSeq;
		unsigned int timeStp;
		std::unique_ptr<int8_t[]> cameraParams;

		int elemCount;
		std::vector<ViveSR::MemoryElement> elements;

		ofParameterGroup group;
		ofParameter<bool> useDepth;
		ofParameter<bool> useColor;
		ofParameter<int> denoiseMedianFilter;
		ofParameter<int> denoiseGuidedFilter;

		ofTexture colorTex;
		ofTexture depthTex;
	};
}