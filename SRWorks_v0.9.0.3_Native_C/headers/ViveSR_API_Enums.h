//========= Copyright 2018, HTC Corporation. All rights reserved. ===========
#pragma once

namespace ViveSR
{
	enum ModuleParam {
		ENABLE_FPSCONTROL	= 1001,
		SET_FPS				= 1002,
	};
	enum ModuleType {
		ENGINE_SEETHROUGH					= 1,	// support device : VIVE Pro
		DEVICE_VIVE_HMD_DUALCAM				,	// obsolete
		ENGINE_UNDISTORTION					,	// obsolete
		ENGINE_DEPTH						,
		ENGINE_RIGID_RECONSTRUCTION			,
        ENGINE_LIGHT_ESTIMATION             ,
		ENGINE_HUMAN_DETECTION				,
		ENGINE_AI_SCENE						,
		ENGINE_LIP_CAMERA					,
		ENGINE_LIP_PREDICTION				,
		ENGINE_EYE_CAMERA					,
		ENGINE_EYE_PREDICTION				,
		ENGINE_FACIAL_DRIVER				,
        ENGINE_DEPTH_MESH                   ,
        ENGINE_SEE_THROUGH_4K               ,
        ENGINE_DEPTH_REGISTRATION           ,
        ENGINE_CONTORLLER_POSE              ,
		ENGINE_MAX
	};

	enum LinkType {
		NONE				= -1,
		PASSIVE				= 0,
		ACTIVE				= 1,
	};

	enum LogLevel {
		LOG_LEVEL_0			= 3,	// turn-off any log except error & warning
		LOG_LEVEL_1			= 4,	// the lower level, the less log, default value
		LOG_LEVEL_2			= 5,
		LOG_LEVEL_3			= 6,
		LOG_LEVEL_MAX		= 10,	// turn-on all log msg
	};
}