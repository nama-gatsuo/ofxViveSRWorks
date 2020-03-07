#pragma once
namespace ViveSR
{
    namespace AIVision
    {
        enum Param {
            MODULEINFO,		// This version only supports Model_Path being configured
            REFINE_TYPE,
            Img_CH,
            Img_Crop_W,
            Img_Crop_H,
            Label_W,
            Label_H,
            Label_CH,
            Label_Number
        };
        enum InputMask
        {
            _DISTORTED_FRAME_LEFT = 0,		// sizeof(char) * 612 * 460 * 4
            _DISTORTED_FRAME_RIGHT = 1,		// sizeof(char) * 612 * 460 * 4
            _UNDISTORTED_FRAME_LEFT = 2,		// sizeof(char) * 1150 * 750 * 4
            _UNDISTORTED_FRAME_RIGHT = 3,	// sizeof(char) * 1150 * 750 * 4
            _FRAME_SEQ = 4,					// sizeof(unsigned int)
            _TIME_STP = 5,					// sizeof(unsigned int)
            _POSE_LEFT = 6,					// sizeof(float) * 16
            _POSE_RIGHT = 7,					// sizeof(float) * 16
            _LUX_LEFT = 8,					// sizeof(int)
            _LUX_RIGHT = 9,					// sizeof(int)
            _COLOR_TEMPERATURE_LEFT = 10,	// sizeof(int)
            _COLOR_TEMPERATURE_RIGHT = 11,	// sizeof(int)
            _EXPOSURE_TIME_LEFT = 12,		// sizeof(int)
            _EXPOSURE_TIME_RIGHT = 13,		// sizeof(int)
            _ANALOG_GAIN_LEFT = 14,			// sizeof(int)
            _ANALOG_GAIN_RIGHT = 15,			// sizeof(int)
            _DIGITAL_GAIN_LEFT = 16,			// sizeof(int)
            _DIGITAL_GAIN_RIGHT = 17,		// sizeof(int)
            _CAMERA_PARAMS = 18,             // sizeof(char) * 1032
            INPUT_MASK_MAX,
        };
        enum OutputMask {
            FRAME_LEFT = 0,		// sizeof(char)*width*height*channel
            LABEL_LEFT = 1,		// sizeof(char)*width*height
            FRAME_RIGHT = 2,		// sizeof(char)*width*height*channel
            LABEL_RIGHT = 3,		// sizeof(char)*width*height
            FRAME_SEQ = 4,
            TIME_STP = 5,
            POSE_LEFT = 6,		// sizeof(float) * 16
            POSE_RIGHT = 7,		// sizeof(float) * 16
            LUX_LEFT = 8,		// sizeof(int)
            LUX_RIGHT = 9,		// sizeof(int)
            COLOR_TEMPERATURE_LEFT = 10,		// sizeof(int)
            COLOR_TEMPERATURE_RIGHT = 11,		// sizeof(int)
            EXPOSURE_TIME_LEFT = 12,		// sizeof(int)
            EXPOSURE_TIME_RIGHT = 13,		// sizeof(int)
            ANALOG_GAIN_LEFT = 14,		// sizeof(int)
            ANALOG_GAIN_RIGHT = 15,		// sizeof(int)
            DIGITAL_GAIN_LEFT = 16,		// sizeof(int)
            DIGITAL_GAIN_RIGHT = 17,		// sizeof(int)
            DM_MAX,
        };
        enum Callback {
            BASIC = 1001,
        };
        enum SceneLabelRefineType {
            REFINE_NONE,
            REFINE_SMALL_HOMOGENEOUS_REGION,
            REFINE_LARGE_HOMOGENEOUS_REGION,
        };
        enum AI_Model {
            SCENE_SEMANTIC,
            HUMAN,
        };
        enum OutputMode {
            ID = 1, // use number to represent scene recognition result.
            MASK_ID = 2, // use number to represent scene recognition result, and focus on single item classify.
            VIS_ID = 4, // use color map to represent scene recognition result.
            VIS_W_ID = 5, // alpha blending : VIS_ID + source image
            VIS_MASK_ID = 6, // use color map to represent scene recognition result, and focus on single item classify.
            VIS_MASK_W_ID = 7, // alpha blending : VIS_MASK_ID + source image
        };

        enum SR_ProcessUnit {
            CPU = 1,
            GPU = 2,
        };
        enum SR_ImageType
        {
            DISTORTED = 0,
            UNDISTORTED = 1,
        };
    }
}
