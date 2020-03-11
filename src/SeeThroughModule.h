#pragma once

#include "ofLog.h"
#include "ofTexture.h"
#include "ofUtils.h"
#include <array>
#include "ofVectorMath.h"
#include "ofParameter.h"
#include "ofShader.h"
#include "ofVboMesh.h"

#include "ViveSR_Enums.h"
#include "ViveSR_API_Enums.h"
#include "ViveSR_Client.h"
#include "ViveSR_Structs.h"
#include "ViveSR_SeeThroughEnums.h"

namespace ofxViveSRWorks {
	class SeeThroughModule {
	public:
		SeeThroughModule();
		~SeeThroughModule();

		void start();
		void update();
		void stop();

		int getModuleID() const { return moduleID; }
		ofParameterGroup& getParameters() { return group; }
		const ofTexture& getUndistortedTexture(int i) const { return undistortedTex[i]; }
		const ofTexture& getDistortedTexture(int i) const { return distortedTex[i]; }
		const glm::mat4& getTransform(int i) const { return units[i].pose; }
		void draw(int i);
	private:

		void checkCameraParams();
		void check(int result, const std::string& taskName);

		int moduleID;
		double cameraParamsSeeThrough[ViveSR::SeeThrough::CAMERA_Param::CAMERA_PARAMS_MAX];
		bool b4kImageReady;
		glm::ivec2 distortedSize, undistortedSize;
		int distortedChannel, undistortedChannel;
		double fps;

		struct Unit {
			std::unique_ptr<uint8_t[]> distortedFrame;
			std::unique_ptr<uint8_t[]> undistortedFrame;
			glm::mat4 pose;
			int lux;
			int colorTemperture;
			int exposureTime;
			int analogGain;
			int digitalGain;
		};
		unsigned int frameSeq;
		unsigned int timeStp;
		std::unique_ptr<int8_t[]> cameraParams;

		int elemCount;
		std::vector<ViveSR::MemoryElement> elements;

		std::array<Unit, 2> units;
		std::array<ofTexture, 2> undistortedTex;
		std::array<ofTexture, 2> distortedTex;
		std::array<glm::vec3, 2> offset;
		std::array<double, 2> foculLength;
		std::array<glm::vec2, 2> undistortedC;
		std::array<glm::vec2, 2> distortedC;
		ofVboMesh renderRect;

		ofParameterGroup group;
		ofParameter<bool> useUndistorted;
		ofParameter<bool> useDistorted;

		ofShader texShader;
	};

}