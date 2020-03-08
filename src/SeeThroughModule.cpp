#include "SeeThroughModule.h"

namespace ofxViveSRWorks {

	SeeThroughModule::SeeThroughModule() : elemCount(0) {
		group.setName("SeeThroughModule");
		group.add(useDistorted.set("useDistorted", false));
		group.add(useUndistorted.set("useUndistorted", false));
	}

	SeeThroughModule::~SeeThroughModule() {
	}

	void SeeThroughModule::start() {

		auto check = [&](int result, const std::string& taskName) {
			if (result != ViveSR::Error::WORK) {
				ofLogError(__FUNCTION__) << taskName << ": " << "Failed! (Code: " << result << ")";
				stop();
			}
		};

		check(
			ViveSR_CreateModule(ViveSR::ModuleType::ENGINE_SEETHROUGH, &moduleID),
			"ViveSR_CreateModule - SEE-THROUGH"
		);

		ViveSR_InitialModule(moduleID);

		check(
			ViveSR_SetParameterBool(moduleID, ViveSR::SeeThrough::Param::DISTORT_GPU_TO_CPU_ENABLE, true),
			"ViveSR_SetParameterBool - SEE-THROUGH - DISTORT_GPU_TO_CPU_ENABLE"
		);
		check(
			ViveSR_SetParameterBool(moduleID, ViveSR::SeeThrough::Param::DEPTH_UNDISTORT_GPU_TO_CPU_ENABLE, true),
			"ViveSR_SetParameterBool - SEE-THROUGH - DEPTH_UNDISTORT_GPU_TO_CPU_ENABLE"
		);

		check(ViveSR_SetParameterBool(moduleID, ViveSR::SeeThrough::Param::VR_INIT, true), "ViveSR_SetParameterBool - SEE-THROUGH - VR_INIT");
		check(ViveSR_SetParameterInt(moduleID, ViveSR::SeeThrough::Param::VR_INIT_TYPE, ViveSR::SeeThrough::InitType::SCENE), "ViveSR_SetParameterInt - SEE-THROUGH - VR_INIT_TYPE");

		check(ViveSR_StartModule(moduleID), "ViveSR_StartModule - SEE-THROUGH");

		// Acquire SRWorks parameters
		for (int i = ViveSR::SeeThrough::CAMERA_Param::CAMERA_FCX_0; i < ViveSR::SeeThrough::CAMERA_Param::CAMERA_PARAMS_MAX; i++) {
			check(
				ViveSR_GetParameterDouble(moduleID, i, &(cameraParamsSeeThrough[i])),
				"ViveSR_GetParameterDouble - SEE-THROUGH " + ofToString(i)
			);
		}

		ViveSR_GetParameterInt(moduleID, ViveSR::SeeThrough::OUTPUT_DISTORTED_WIDTH, &distortedSize.x);
		ViveSR_GetParameterInt(moduleID, ViveSR::SeeThrough::OUTPUT_DISTORTED_HEIGHT, &distortedSize.y);
		ViveSR_GetParameterInt(moduleID, ViveSR::SeeThrough::OUTPUT_DISTORTED_CHANNEL, &distortedChannel);

		ofLogNotice(__FUNCTION__) << "SEE-THROUGH Distorted: " << distortedSize.x << " x " << distortedSize.y << " ( " << distortedChannel << " ch )";

		ViveSR_GetParameterInt(moduleID, ViveSR::SeeThrough::OUTPUT_UNDISTORTED_WIDTH, &undistortedSize.x);
		ViveSR_GetParameterInt(moduleID, ViveSR::SeeThrough::OUTPUT_UNDISTORTED_HEIGHT, &undistortedSize.y);
		ViveSR_GetParameterInt(moduleID, ViveSR::SeeThrough::OUTPUT_UNDISTORTED_CHANNEL, &undistortedChannel);

		ofLogNotice(__FUNCTION__) << "SEE-THROUGH Undistorted: " << undistortedSize.x << " x " << undistortedSize.y << " ( " << undistortedChannel << " ch )";

		for (auto& u : units) {
			u.distortedFrame = std::make_unique<uint8_t[]>(distortedSize.x * distortedSize.x * distortedChannel);
			u.undistortedFrame = std::make_unique<uint8_t[]>(undistortedSize.x * undistortedSize.y * undistortedChannel);
		}

		cameraParams = std::make_unique<int8_t[]>(1032);

		void* seeThroughPtrs[ViveSR::SeeThrough::OutputMask::MAX]{
			units[0].distortedFrame.get(),
			units[1].distortedFrame.get(),
			units[0].undistortedFrame.get(),
			units[1].undistortedFrame.get(),
			&frameSeq,
			&timeStp,
			&(units[0].pose[0][0]),
			&(units[1].pose[0][0]),
			&(units[0].lux),
			&(units[1].lux),
			&(units[0].colorTemperture),
			&(units[1].colorTemperture),
			&(units[0].exposureTime),
			&(units[1].exposureTime),
			&(units[0].analogGain),
			&(units[1].analogGain),
			&(units[0].digitalGain),
			&(units[1].digitalGain),
			cameraParams.get()
		};

		elements.resize(ViveSR::SeeThrough::OutputMask::MAX);

		for (int i = 0; i < ViveSR::SeeThrough::OutputMask::MAX; ++i) {
			if (seeThroughPtrs[i]) {
				elements[elemCount].mask = i;
				elements[elemCount].ptr = seeThroughPtrs[i];
				elemCount++;
			}
		}

		// allocate ofTexture
		GLint glInternalFormat = undistortedChannel == 3 ? GL_RGB8 : GL_RGBA8;
		undistortedTex[0].allocate(undistortedSize.x, undistortedSize.y, glInternalFormat);
		undistortedTex[1].allocate(undistortedSize.x, undistortedSize.y, glInternalFormat);

		glInternalFormat = distortedChannel == 3 ? GL_RGB8 : GL_RGBA8;
		distortedTex[0].allocate(distortedSize.x, distortedSize.y, glInternalFormat);
		distortedTex[1].allocate(distortedSize.x, distortedSize.y, glInternalFormat);

		// createParams();
	}

	void SeeThroughModule::update() {

		int res = ViveSR::Error::FAILED;
		res = ViveSR_GetModuleData(moduleID, elements.data(), elemCount);
		if (res == ViveSR::Error::WORK) {
			if (useUndistorted) {
				GLint glFormat = distortedChannel == 3 ? GL_RGB : GL_RGBA;
				undistortedTex[0].loadData(units[0].undistortedFrame.get(), undistortedSize.x, undistortedSize.y, glFormat);
				undistortedTex[1].loadData(units[1].undistortedFrame.get(), undistortedSize.x, undistortedSize.y, glFormat);
			}
			if (useDistorted) {
				GLint glFormat = distortedChannel == 3 ? GL_RGB : GL_RGBA;
				distortedTex[0].loadData(units[0].distortedFrame.get(), distortedSize.x, distortedSize.y, glFormat);
				distortedTex[1].loadData(units[1].distortedFrame.get(), distortedSize.x, distortedSize.y, glFormat);
			}

		}

	}

	void SeeThroughModule::stop() {
		auto check = [&](int result, const std::string& taskName) {
			if (result != ViveSR::Error::WORK) {
				ofLogError(__FUNCTION__) << taskName << ": " << "Failed! (Code: " << result << ")";
			}
		};
		check(ViveSR_StopModule(moduleID), "ViveSR_StopModule - SEE-THROUGH");
		// check(ViveSR_ReleaseModule(moduleID), "ViveSR_ReleaseModule - SEE-THROUGH");

	}

}