#include "SeeThroughModule.h"
#include "ofGraphics.h"
#include "of3dGraphics.h"
#include <unordered_map>

namespace ofxViveSRWorks {

	SeeThroughModule::SeeThroughModule() : elemCount(0) {
		group.setName("SeeThroughModule");
		group.add(useDistorted.set("useDistorted", false));
		group.add(useUndistorted.set("useUndistorted", false));

		std::string path = "../../../../../addons/ofxViveSRWorks/shader/";
		texShader.load(path + "texShader");
	}

	SeeThroughModule::~SeeThroughModule() {
	}

	void SeeThroughModule::start() {

		check(ViveSR_CreateModule(ViveSR::ModuleType::ENGINE_SEETHROUGH, &moduleID), "ViveSR_CreateModule");
		check(ViveSR_InitialModule(moduleID), "ViveSR_InitialModule");

		check(ViveSR_SetParameterBool(moduleID, ViveSR::SeeThrough::Param::DISTORT_GPU_TO_CPU_ENABLE, true), "DISTORT_GPU_TO_CPU_ENABLE");
		check(ViveSR_SetParameterBool(moduleID, ViveSR::SeeThrough::Param::DEPTH_UNDISTORT_GPU_TO_CPU_ENABLE, true), "DEPTH_UNDISTORT_GPU_TO_CPU_ENABLE");

		check(ViveSR_SetParameterBool(moduleID, ViveSR::SeeThrough::Param::VR_INIT, true), "VR_INIT");
		check(ViveSR_SetParameterInt(moduleID, ViveSR::SeeThrough::Param::VR_INIT_TYPE, ViveSR::SeeThrough::InitType::SCENE), "VR_INIT_TYPE");

		check(ViveSR_StartModule(moduleID), "ViveSR_StartModule");

		// Acquire SRWorks parameters
		check(ViveSR_GetParameterBool(moduleID, ViveSR::SeeThrough::Param::OUTPUT_4K_READY, &b4kImageReady), "OUTPUT_4K_READY");
		ofLogVerbose(__FUNCTION__) << "4K image: " << (b4kImageReady ? "available" : "not available");

		// checkCameraParams();

		check(ViveSR_GetParameterFloat(moduleID, ViveSR::SeeThrough::Param::OFFSET_HEAD_TO_CAMERA_x0, &offset[0].x), "OFFSET_HEAD_TO_CAMERA_x0");		// float[6]  (x0,y0,z0,x1,y1,z1)
		check(ViveSR_GetParameterFloat(moduleID, ViveSR::SeeThrough::Param::OFFSET_HEAD_TO_CAMERA_y0, &offset[0].y), "OFFSET_HEAD_TO_CAMERA_y0");
		check(ViveSR_GetParameterFloat(moduleID, ViveSR::SeeThrough::Param::OFFSET_HEAD_TO_CAMERA_z0, &offset[0].z), "OFFSET_HEAD_TO_CAMERA_z0");
		check(ViveSR_GetParameterFloat(moduleID, ViveSR::SeeThrough::Param::OFFSET_HEAD_TO_CAMERA_x1, &offset[1].x), "OFFSET_HEAD_TO_CAMERA_x1");
		check(ViveSR_GetParameterFloat(moduleID, ViveSR::SeeThrough::Param::OFFSET_HEAD_TO_CAMERA_y1, &offset[1].y), "OFFSET_HEAD_TO_CAMERA_y1");
		check(ViveSR_GetParameterFloat(moduleID, ViveSR::SeeThrough::Param::OFFSET_HEAD_TO_CAMERA_z1, &offset[1].z), "OFFSET_HEAD_TO_CAMERA_z1");
		
		for (int i = ViveSR::SeeThrough::CAMERA_Param::CAMERA_FCX_0; i < ViveSR::SeeThrough::CAMERA_Param::CAMERA_PARAMS_MAX; i++) {
			check(ViveSR_GetParameterDouble(moduleID, i, &(cameraParamsSeeThrough[i])), "CameraParams " + ofToString(i));
		}

		foculLength[0] = cameraParamsSeeThrough[4];
		foculLength[1] = cameraParamsSeeThrough[5];
		distortedC[0].x = cameraParamsSeeThrough[0];
		distortedC[0].y = cameraParamsSeeThrough[2];
		distortedC[1].x = cameraParamsSeeThrough[1];
		distortedC[1].y = cameraParamsSeeThrough[3];
		undistortedC[0].x = cameraParamsSeeThrough[18];
		undistortedC[0].y = cameraParamsSeeThrough[19];
		undistortedC[1].x = cameraParamsSeeThrough[20];
		undistortedC[1].y = cameraParamsSeeThrough[21];

		int res = ViveSR_GetParameterDouble(moduleID, ViveSR::SeeThrough::OUTPUT_FPS, &fps);
		ofLogVerbose(__FUNCTION__) << "FPS: " << fps;

		ViveSR_GetParameterInt(moduleID, ViveSR::SeeThrough::OUTPUT_DISTORTED_WIDTH, &distortedSize.x);
		ViveSR_GetParameterInt(moduleID, ViveSR::SeeThrough::OUTPUT_DISTORTED_HEIGHT, &distortedSize.y);
		ViveSR_GetParameterInt(moduleID, ViveSR::SeeThrough::OUTPUT_DISTORTED_CHANNEL, &distortedChannel);
		ofLogNotice(__FUNCTION__) << "Distorted: " << distortedSize.x << " x " << distortedSize.y << " ( " << distortedChannel << " ch )";

		ViveSR_GetParameterInt(moduleID, ViveSR::SeeThrough::OUTPUT_UNDISTORTED_WIDTH, &undistortedSize.x);
		ViveSR_GetParameterInt(moduleID, ViveSR::SeeThrough::OUTPUT_UNDISTORTED_HEIGHT, &undistortedSize.y);
		ViveSR_GetParameterInt(moduleID, ViveSR::SeeThrough::OUTPUT_UNDISTORTED_CHANNEL, &undistortedChannel);
		ofLogNotice(__FUNCTION__) << "Undistorted: " << undistortedSize.x << " x " << undistortedSize.y << " ( " << undistortedChannel << " ch )";

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
		for (auto& ut : undistortedTex) {
			ut.allocate(undistortedSize.x, undistortedSize.y, glInternalFormat);
			ut.setTextureMinMagFilter(GL_NEAREST, GL_NEAREST);
			//ut.getTextureData().bFlipTexture = true;
		}
		

		glInternalFormat = distortedChannel == 3 ? GL_RGB8 : GL_RGBA8;
		distortedTex[0].allocate(distortedSize.x, distortedSize.y, glInternalFormat);
		distortedTex[1].allocate(distortedSize.x, distortedSize.y, glInternalFormat);

		float aspect = float(undistortedSize.x) / float(undistortedSize.y);
		
		// Rough approximation of image plane size
		// Plane size can be calculated by focul length, fov, and aspect ratio
		// But this time put this number manually as temporal checking...
		renderRect = ofMesh::plane(8.0, 8.0 / aspect, 2, 2);
		renderRect.clearTexCoords();
		renderRect.addTexCoord(glm::vec2(0, undistortedSize.y));
		renderRect.addTexCoord(glm::vec2(undistortedSize));
		renderRect.addTexCoord(glm::vec2(0));
		renderRect.addTexCoord(glm::vec2(undistortedSize.x, 0));
		

	}

	void SeeThroughModule::update() {

		int res = ViveSR::Error::FAILED;
		res = ViveSR_GetModuleData(moduleID, elements.data(), elemCount);
		
		if (res == ViveSR::Error::WORK) {
			if (useUndistorted) {
				GLint glFormat = distortedChannel == 3 ? GL_RGB : GL_RGBA;
				//float start = ofGetElapsedTimef();
				undistortedTex[0].loadData(units[0].undistortedFrame.get(), undistortedSize.x, undistortedSize.y, glFormat);
				undistortedTex[1].loadData(units[1].undistortedFrame.get(), undistortedSize.x, undistortedSize.y, glFormat);
				//float end = ofGetElapsedTimef();
				//ofLogNotice() << (end - start) / (1.f / 90.f);
			}
			if (useDistorted) {
				GLint glFormat = distortedChannel == 3 ? GL_RGB : GL_RGBA;
				distortedTex[0].loadData(units[0].distortedFrame.get(), distortedSize.x, distortedSize.y, glFormat);
				distortedTex[1].loadData(units[1].distortedFrame.get(), distortedSize.x, distortedSize.y, glFormat);
			}
			
		}
	}

	void SeeThroughModule::stop() {
		check(ViveSR_StopModule(moduleID), "ViveSR_StopModule - SEE-THROUGH");
		// check(ViveSR_ReleaseModule(moduleID), "ViveSR_ReleaseModule - SEE-THROUGH");

	}

	void SeeThroughModule::draw(int i) {
		ofDisableDepthTest();
		ofPushMatrix();
		ofMultMatrix(glm::scale(glm::vec3(1.f, 1.f, -1.f)) * units[i].pose);
		ofTranslate(0, 0, 2.f); // Translate image plane to far away
		
		texShader.begin();
		texShader.setUniformTexture("tex", getUndistortedTexture(i), 0);
		renderRect.draw();
		texShader.end();

		ofPopMatrix();
		ofEnableDepthTest();
		
	}

	void SeeThroughModule::checkCameraParams() {
		std::unordered_map<int, std::string> modes{
			{ ViveSR::SeeThrough::CAMERA_BRIGHTNESS, "CAMERA_BRIGHTNESS" },
			{ ViveSR::SeeThrough::CAMERA_CONTRAST, "CAMERA_CONTRAST" },
			{ ViveSR::SeeThrough::CAMERA_HUE, "CAMERA_HUE" },
			{ ViveSR::SeeThrough::CAMERA_SATURATION, "CAMERA_SATURATION" },
			{ ViveSR::SeeThrough::CAMERA_SHARPNESS, "CAMERA_SHARPNESS" },
			{ ViveSR::SeeThrough::CAMERA_GAMMA, "CAMERA_GAMMA" },
			{ ViveSR::SeeThrough::CAMERA_COLOR_ENABLE, "CAMERA_COLOR_ENABLE" },
			{ ViveSR::SeeThrough::CAMERA_WHITE_BALANCE, "CAMERA_WHITE_BALANCE" },
			{ ViveSR::SeeThrough::CAMERA_BACKLIGHT_COMPENSATION, "CAMERA_BACKLIGHT_COMPENSATION" },
			{ ViveSR::SeeThrough::CAMERA_GAIN, "CAMERA_GAIN" },
			{ ViveSR::SeeThrough::CAMERA_PAN, "CAMERA_PAN" },
			{ ViveSR::SeeThrough::CAMERA_TILT, "CAMERA_TILT" },
			{ ViveSR::SeeThrough::CAMERA_ROLL, "CAMERA_ROLL" },
			{ ViveSR::SeeThrough::CAMERA_ZOOM, "CAMERA_ZOOM" },
			{ ViveSR::SeeThrough::CAMERA_EXPOSURE, "CAMERA_EXPOSURE" },
			{ ViveSR::SeeThrough::CAMERA_IRIS, "CAMERA_IRIS" },
			{ ViveSR::SeeThrough::CAMERA_FOCUS, "CAMERA_FOCUS" }
		};

		for (auto m : modes) {
			bool t = true;
			int min, max, defaultValue, step, mode;

			check(ViveSR_GetParameterBool(moduleID, m.first, &t), "Query " + m.second);
			check(ViveSR_GetParameterInt(moduleID, ViveSR::SeeThrough::CAMERA_CONTROL_MAX, &max), "Max of " + m.second);
			check(ViveSR_GetParameterInt(moduleID, ViveSR::SeeThrough::CAMERA_CONTROL_MIN, &min), "Min of " + m.second);
			check(ViveSR_GetParameterInt(moduleID, ViveSR::SeeThrough::CAMERA_CONTROL_STEP, &step), "Step of " + m.second);
			check(ViveSR_GetParameterInt(moduleID, ViveSR::SeeThrough::CAMERA_CONTROL_DEFAULT_VALUE, &defaultValue), "Defalt of " + m.second);
			check(ViveSR_GetParameterInt(moduleID, ViveSR::SeeThrough::CAMERA_CONTROL_MODE, &mode), "Mode of " + m.second);

			ofLogNotice(m.second) << "max: " << max << ", min: " << min << ", default: " << defaultValue << ", mode: " << mode;
		}
	}

	void SeeThroughModule::check(int result, const std::string& taskName) {
		if (result != ViveSR::Error::WORK) {
			ofLogError(__FUNCTION__) << taskName << ": " << "Failed! (Code: " << result << ")";
		}
	}

}