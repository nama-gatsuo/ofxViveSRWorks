namespace ViveSR
{
	namespace SeeThrough
	{
        /**
        An enum type for see-through parameters.
        */
        enum Param
        {
            VR_INIT = 0,
            VR_INIT_TYPE,
            OUTPUT_DISTORTED_WIDTH,
            OUTPUT_DISTORTED_HEIGHT,
            OUTPUT_DISTORTED_CHANNEL,
            OUTPUT_UNDISTORTED_WIDTH,
            OUTPUT_UNDISTORTED_HEIGHT,
            OUTPUT_UNDISTORTED_CHANNEL,
            OUTPUT_FPS,
            OFFSET_HEAD_TO_CAMERA,						// float[6]  (x0,y0,z0,x1,y1,z1)
            PLAY_AREA_RECT,								// float[12] (x0,y0,z0,x1,y1,z1,...)
            VIDEO_RES_NATIVE_PTR,
            VIDEO_RES_VIEW_NATIVE_PTR,
            IMAGE_NATIVE_TEXTURE_PTR_L,
            IMAGE_NATIVE_TEXTURE_PTR_R,
            CAMERA_BRIGHTNESS = 100,
            CAMERA_CONTRAST,
            CAMERA_HUE,
            CAMERA_SATURATION,
            CAMERA_SHARPNESS,
            CAMERA_GAMMA,
            CAMERA_COLOR_ENABLE,
            CAMERA_WHITE_BALANCE,
            CAMERA_BACKLIGHT_COMPENSATION,
            CAMERA_GAIN,
            CAMERA_PAN,
            CAMERA_TILT,
            CAMERA_ROLL,
            CAMERA_ZOOM,
            CAMERA_EXPOSURE,
            CAMERA_IRIS,
            CAMERA_FOCUS,
            DEVICE_SYSTEM_TYPE,
            UNDISTORTION_MODE = 200,
            UNDISTORTION_CX,
            UNDISTORTION_CY,
            UNDISTORTION_FOCAL_LENGTH,
            UNDISTORTION_FMAT_RM_L,
            UNDISTORTION_FMAT_RM_R,
            UNDISTORTION_INTRINSIC_L,
            UNDISTORTION_INTRINSIC_R,
            UNDISTORTION_R_RECTIFY_L,
            UNDISTORTION_R_RECTIFY_R,
            UNDISTORTION_COEFFS_L,
            UNDISTORTION_COEFFS_R,
            UNDISTORTION_P_NEWPROJ_L,
            UNDISTORTION_P_NEWPROJ_R,
            UNDISTORTION_MAP_SIZE,
            UNDISTORTION_MAP_L,
            UNDISTORTION_MAP_R,
            UNDISTORTION_CENTER,
            MESH_NATIVE_VERTEX_BUFFER_PTR_L,		// void *
            MESH_NATIVE_VERTEX_BUFFER_PTR_R,		// void *
            MESH_NATIVE_VERTEX_ARRAY_L,				// void *
            MESH_NATIVE_VERTEX_ARRAY_R,				// void *
            MESH_CALIB_NATIVE_VERTEX_BUFFER_PTR_L,	// void *
            MESH_CALIB_NATIVE_VERTEX_BUFFER_PTR_R,	// void *
            MESH_CALIB_NATIVE_VERTEX_ARRAY_L,		// void *
            MESH_CALIB_NATIVE_VERTEX_ARRAY_R,		// void *
            ENABLE_IMAGE_PLANE_MESH_L,				// bool
            ENABLE_IMAGE_PLANE_MESH_R,				// bool
            ENABLE_CALIB_IMAGE_PLANE_MESH_L,		// bool
            ENABLE_CALIB_IMAGE_PLANE_MESH_R,		// bool
            CAMERA_PARAMETERS = 300,                // void *
            OFFSET_HEAD_TO_CAMERA_x0,				// float[6]  (x0,y0,z0,x1,y1,z1)
            OFFSET_HEAD_TO_CAMERA_y0,
            OFFSET_HEAD_TO_CAMERA_z0,
            OFFSET_HEAD_TO_CAMERA_x1,
            OFFSET_HEAD_TO_CAMERA_y1,
            OFFSET_HEAD_TO_CAMERA_z1,
            CAMERA_CONTROL_STATUS = 400,
            CAMERA_CONTROL_DEFAULT_VALUE,
            CAMERA_CONTROL_MIN,
            CAMERA_CONTROL_MAX,
            CAMERA_CONTROL_STEP,
            CAMERA_CONTROL_DEFAULT_MODE,
            CAMERA_CONTROL_VALUE,
            CAMERA_CONTROL_MODE,
            RESET_AllCAMERA_QUALITY,
            TRACKING_POSE = 500,
            OUTPUT_4K_READY,
            D3D11_SHARED_HANDLE_UNDISTORTED_LEFT,	//int
            D3D11_SHARED_HANDLE_UNDISTORTED_RIGHT,	//int
            TRACKING_POSE_VALID_LEFT,               //int
            TRACKING_POSE_VALID_RIGHT,              //int
            TRACKING_POSE_POS_LEFT_X,               //float
            TRACKING_POSE_POS_LEFT_Y,               //float
            TRACKING_POSE_POS_LEFT_Z,               //float
            TRACKING_POSE_POS_RIGHT_X,              //float
            TRACKING_POSE_POS_RIGHT_Y,              //float
            TRACKING_POSE_POS_RIGHT_Z,              //float
            TRACKING_POSE_ROT_LEFT_X,               //float
            TRACKING_POSE_ROT_LEFT_Y,               //float
            TRACKING_POSE_ROT_LEFT_Z,               //float
            TRACKING_POSE_ROT_LEFT_W,               //float
            TRACKING_POSE_ROT_RIGHT_X,              //float
            TRACKING_POSE_ROT_RIGHT_Y,              //float
            TRACKING_POSE_ROT_RIGHT_Z,              //float
            TRACKING_POSE_ROT_RIGHT_W,              //float
            SKIP_VGA_PROCESS,
            DISTORT_GPU_TO_CPU_ENABLE,
            DEPTH_UNDISTORT_GPU_TO_CPU_ENABLE
		};
        /**
        An enum type for camera parameters.
        */
        enum CAMERA_Param
        {
            CAMERA_FCX_0 = 0,                       // DOUBLE   0 is left camera
            CAMERA_FCX_1,                           // DOUBLE   1 is right camera
            CAMERA_FCY_0,                           // DOUBLE   0 is left camera
            CAMERA_FCY_1,                           // DOUBLE   1 is right camera
            CAMERA_FLEN_0,                          // DOUBLE   0 is left camera
            CAMERA_FLEN_1,                          // DOUBLE   1 is right camera
            CAMERA_ROTATION_0,                      // DOUBLE   The rotation array is row order.
            CAMERA_ROTATION_1,                      // DOUBLE
            CAMERA_ROTATION_2,                      // DOUBLE
            CAMERA_ROTATION_3,                      // DOUBLE
            CAMERA_ROTATION_4,                      // DOUBLE
            CAMERA_ROTATION_5,                      // DOUBLE
            CAMERA_ROTATION_6,                      // DOUBLE
            CAMERA_ROTATION_7,                      // DOUBLE
            CAMERA_ROTATION_8,                      // DOUBLE
            CAMERA_TRANSLATION_0,                   // DOUBLE
            CAMERA_TRANSLATION_1,                   // DOUBLE
            CAMERA_TRANSLATION_2,                   // DOUBLE
            UNDISTORTION_CENTER_CX_L,               // DOUBLE
            UNDISTORTION_CENTER_CY_L,               // DOUBLE
            UNDISTORTION_CENTER_CX_R,               // DOUBLE
            UNDISTORTION_CENTER_CY_R,               // DOUBLE
            CAMERA_PARAMS_MAX
        };

        /**
        An enum type for camera control type is automatic or manual.
        */
        enum CTRL_MODE {
            CTRL_AUTO = 0x01,
            CTRL_MANUAL = 0x02,
        };

        /**
        An enum type for VR initial type.
        */
		enum InitType {
			SCENE = 1,	   // Application will submit 3D frames
			BACKGROUND = 3 // Application should not start SteamVR if it's not already running, and should not
		};
        /**
        An enum type for see-through output data structure.
        */
		enum OutputMask
		{
			DISTORTED_FRAME_LEFT = 0,		// sizeof(char) * 612 * 460 * 4
			DISTORTED_FRAME_RIGHT = 1,		// sizeof(char) * 612 * 460 * 4
			UNDISTORTED_FRAME_LEFT = 2,		// sizeof(char) * 1150 * 750 * 4
			UNDISTORTED_FRAME_RIGHT = 3,	// sizeof(char) * 1150 * 750 * 4
			FRAME_SEQ = 4,					// sizeof(unsigned int)
			TIME_STP = 5,					// sizeof(unsigned int)
			POSE_LEFT = 6,					// sizeof(float) * 16
			POSE_RIGHT = 7,					// sizeof(float) * 16
			LUX_LEFT = 8,					// sizeof(int)
			LUX_RIGHT = 9,					// sizeof(int)
			COLOR_TEMPERATURE_LEFT = 10,	// sizeof(int)
			COLOR_TEMPERATURE_RIGHT = 11,	// sizeof(int)
			EXPOSURE_TIME_LEFT = 12,		// sizeof(int)
			EXPOSURE_TIME_RIGHT = 13,		// sizeof(int)
			ANALOG_GAIN_LEFT = 14,			// sizeof(int)
			ANALOG_GAIN_RIGHT = 15,			// sizeof(int)
			DIGITAL_GAIN_LEFT = 16,			// sizeof(int)
			DIGITAL_GAIN_RIGHT = 17,		// sizeof(int)
            CAMERA_PARAMS = 18,             // sizeof(char) * 1032
            D3D11_TEXTURE2D_SHARED_HANDLE_LEFT = 19,    // sizeof(void *)
            D3D11_TEXTURE2D_SHARED_HANDLE_RIGHT = 20,   // sizeof(void *)
            D3D11_TEXTURE2D_BUFFER_INDEX = 21,  // sizeof(unsigned int)
            GAMMA = 22,                         //sizeof(float)
			MAX,
		};
        /**
        An enum type for camera controller type mapping.
        */
        enum CameraControlType {
            CAMERA_CRTL_BRIGHTNESS = CAMERA_BRIGHTNESS,
            CAMERA_CRTL_CONTRAST = CAMERA_BRIGHTNESS,
            CAMERA_CRTL_HUE = CAMERA_HUE,
            CAMERA_CRTL_SATURATION = CAMERA_SATURATION,
            CAMERA_CRTL_SHARPNESS = CAMERA_SHARPNESS,
            CAMERA_CRTL_GAMMA = CAMERA_GAMMA,
            CAMERA_CRTL_COLOR_ENABLE = CAMERA_COLOR_ENABLE,
            CAMERA_CRTL_WHITE_BALANCE = CAMERA_WHITE_BALANCE,
            CAMERA_CRTL_BACKLIGHT_COMPENSATION = CAMERA_BACKLIGHT_COMPENSATION,
            CAMERA_CRTL_GAIN = CAMERA_GAIN,
            CAMERA_CRTL_PAN = CAMERA_PAN,
            CAMERA_CRTL_TILT = CAMERA_TILT,
            CAMERA_CRTL_ROLL = CAMERA_ROLL,
            CAMERA_CRTL_ZOOM = CAMERA_ZOOM,
            CAMERA_CRTL_EXPOSURE = CAMERA_EXPOSURE,
            CAMERA_CRTL_IRIS = CAMERA_IRIS,
            CAMERA_CRTL_FOCUS = CAMERA_FOCUS
        };
	}
}
