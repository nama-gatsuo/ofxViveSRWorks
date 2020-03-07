#pragma once
namespace ViveSR
{
    namespace Depth
    {
        /**
        An enum type for depth parameters.
        */
        enum Param {
            OUTPUT_WIDTH,
            OUTPUT_HEIGHT,
            OUTPUT_CHAANEL_0,
            OUTPUT_CHAANEL_1,
            TYPE,
            FOCULENS,
            BASELINE,
            COLLIDER_QUALITY,
            MESH_NEAR_DISTANCE,
            MESH_FAR_DISTANCE,
            DENOISE_MEDIAN_FILTER,	// range : 1, 3, 5; (default: 3)
            CONFIDENCE_THRESHOLD,	// range : 0 ~ 5; (default: 0.05)
            DENOISE_GUIDED_FILTER,  // range : 1 ~ 7; (default: 3)
            DEPTH_USING_CASE,
        };

        /**
        An enum type for depth type.
        */
        enum DepthCase
        {
            DEFAULT,
            CLOSE_RANGE,
        };

        /**
        An enum type for depth input data structure.
        */
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
            _D3D11_TEXTURE2D_SHARED_HANDLE_LEFT = 19,    // sizeof(void *)
            _D3D11_TEXTURE2D_SHARED_HANDLE_RIGHT = 20,   // sizeof(void *)
            _D3D11_TEXTURE2D_BUFFER_INDEX = 21,  // sizeof(unsigned int)
            _GAMMA = 22,                         // sizeof(float)*1
            INPUT_MASK_MAX,
        };

        /**
        An enum type for depth output data structure.
        */
        enum OutputMask
        {
            LEFT_FRAME = 0,		            // sizeof(char) * 640 * 480 * 4
            DEPTH_MAP = 1,		            // sizeof(float) * 640 * 480 * 1
            FRAME_SEQ = 2,		            // sizeof(unsigned int)
            TIME_STP = 3,		            // sizeof(unsigned int)
            POSE = 4,		                // sizeof(float) * 16
            LUX_LEFT = 5,		            // sizeof(int)
            COLOR_TEMPERATURE_LEFT = 6,		// sizeof(int)
            EXPOSURE_TIME_LEFT = 7,		    // sizeof(int)
            ANALOG_GAIN_LEFT = 8,		    // sizeof(int)
            DIGITAL_GAIN_LEFT = 9,		    // sizeof(int)
            CAMERA_PARAMS = 10,             // sizeof(char) * 1032
            OUTPUT_MASK_MAX,
        };

        /**
        An enum type for control signal to change depth module's behavior.
        */
        enum Cmd {
            EXTRACT_DEPTH_MESH = 100,
            ENABLE_REFINEMENT = 103,
            ENABLE_EDGE_ENHANCE,
            CHANGE_DEPTH_CASE,
        };
    }

}