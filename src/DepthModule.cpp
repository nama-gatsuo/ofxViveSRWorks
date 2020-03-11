#include "DepthModule.h"
#include "ofPixels.h"


namespace ofxViveSRWorks {
	DepthModule::DepthModule() : elemCount(0) {
		group.setName("DepthModule");
		group.add(useDepth.set("useDepth", false));
		group.add(useColor.set("useColor", false));
		createParams();
	}
	DepthModule::~DepthModule() {
	}
	void DepthModule::start() {
		auto check = [&](int result, const std::string& taskName) {
			if (result != ViveSR::Error::WORK) {
				ofLogError("DepthModule::Start") << taskName << ": " << "Failed! (Code: " << result << ")";
				stop();
			}
		};

		check(
			ViveSR_CreateModule(ViveSR::ModuleType::ENGINE_DEPTH, &moduleID),
			"ViveSR_CreateModule - DEPTH"
		);
		
		ViveSR_InitialModule(moduleID);

		check(ViveSR_StartModule(moduleID), "ViveSR_StartModule - DEPTH");

		ViveSR_GetParameterInt(moduleID, ViveSR::Depth::OUTPUT_WIDTH, &size.x);
		ViveSR_GetParameterInt(moduleID, ViveSR::Depth::OUTPUT_HEIGHT, &size.y);
		ViveSR_GetParameterInt(moduleID, ViveSR::Depth::OUTPUT_CHAANEL_1, &depthChannel);
		ViveSR_GetParameterInt(moduleID, ViveSR::Depth::OUTPUT_CHAANEL_0, &colorChannel);

		ofLogNotice(__FUNCTION__) << "DEPTH: " << size.x << " x " << size.y << " ( depth - " << depthChannel << " ch, color - " << colorChannel << "ch )";

		unit.depthFrame = std::make_unique<float[]>(size.x * size.y * depthChannel);
		unit.colorFrame = std::make_unique<uint8_t[]>(size.x * size.y * colorChannel);
		cameraParams = std::make_unique<int8_t[]>(1032);
		
		void* depth_ptrs[ViveSR::Depth::OutputMask::OUTPUT_MASK_MAX]{
			unit.colorFrame.get(),
			unit.depthFrame.get(),
			&frameSeq,
			&timeStp,
			&(unit.pose[0][0]),
			&unit.lux,
			&unit.colorTemperature,
			&unit.exposureTime,
			&unit.analogGain,
			&unit.digitalGain,
			cameraParams.get(),
		};
		
		elements.resize(ViveSR::Depth::OutputMask::OUTPUT_MASK_MAX);

		for (int i = 0; i < ViveSR::Depth::OutputMask::OUTPUT_MASK_MAX; ++i) {
			if (depth_ptrs[i]) {
				elements[elemCount].mask = i;
				elements[elemCount].ptr = depth_ptrs[i];
				elemCount++;
			}
		}

		// allocate ofTexture
		colorTex.allocate(size.x, size.y, colorChannel == 3 ? GL_RGB8 : GL_RGBA8);
		depthTex.allocate(size.x, size.y, GL_R32F);
		depthTex.setRGToRGBASwizzles(true);

	}

	void DepthModule::update() {
		int res = ViveSR::Error::FAILED;
		res = ViveSR_GetModuleData(moduleID, elements.data(), elemCount);
		if (res == ViveSR::Error::WORK) {
			if (useColor) {
				colorTex.loadData(unit.colorFrame.get(), size.x, size.y, colorChannel == 3 ? GL_RGB : GL_RGBA);
			}
			if (useDepth) {
				depthTex.loadData(unit.depthFrame.get(), size.x, size.y, GL_RED);
			}
		}
	}
	void DepthModule::stop() {
		auto check = [&](int result, const std::string& taskName) {
			if (result != ViveSR::Error::WORK) {
				ofLogError(__FUNCTION__) << taskName << ": " << "Failed! (Code: " << result << ")";
			}
		};
		check(ViveSR_StopModule(moduleID), "ViveSR_StopModule - DEPTH");
		// check(ViveSR_ReleaseModule(moduleID), "ViveSR_ReleaseModule - DEPTH");
	}

	
	void DepthModule::createParams() {
		group.add(denoiseMedianFilter.set("DenoiseMedianFilter", 5, 1, 5));
		e0 = denoiseMedianFilter.newListener([&](int&) {
			ViveSR_SetParameterInt(moduleID, ViveSR::Depth::Param::DENOISE_MEDIAN_FILTER, denoiseMedianFilter);
		});

		
		group.add(denoiseGuidedFilter.set("DenoiseGuidedFilter", 3, 1, 7));
		e1 = denoiseMedianFilter.newListener([&](int&) {
			ViveSR_SetParameterInt(moduleID, ViveSR::Depth::Param::DENOISE_GUIDED_FILTER, denoiseGuidedFilter);
		});
		
		group.add(confidenceThres.set("ConfidenceThreshould", 0.05, 0, 1));
		e2 = confidenceThres.newListener([&](double&) {
			ViveSR_SetParameterDouble(moduleID, ViveSR::Depth::Param::CONFIDENCE_THRESHOLD, confidenceThres);
		});
		
		group.add(enableEdgeEnhance.set("EnableEdgeEnhance", false));
		e3 = enableEdgeEnhance.newListener([&](bool&) {
			ViveSR_SetParameterBool(moduleID, ViveSR::Depth::Cmd::ENABLE_EDGE_ENHANCE, enableEdgeEnhance);
			return true;
		});

		group.add(closeRange.set("CloseRangeCase", false));
		e4 = closeRange.newListener([&](bool&) {
			ViveSR_SetParameterBool(moduleID, ViveSR::Depth::Cmd::CHANGE_DEPTH_CASE,
				closeRange ? ViveSR::Depth::DepthCase::CLOSE_RANGE : ViveSR::Depth::DepthCase::DEFAULT
			);
			return true;
		});
	}

}