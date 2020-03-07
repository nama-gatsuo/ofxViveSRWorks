#pragma once

namespace ViveSR
{
    namespace RigidReconstruction
    {
        /**
        An enum type for RigidReconstruction parameters.
        */
        enum Param {
            FOCAL_LENGTH = 8,               // float
            POINTCLOUD_POINTSIZE = 9,       // float
            EXPORT_ADAPTIVE_MODEL = 10,     // bool
            ADAPTIVE_MAX_GRID = 11,         // float
            ADAPTIVE_MIN_GRID = 12,         // float
            ADAPTIVE_ERROR_THRES = 13,      // float
            SECTOR_SIZE = 15,               // float
            SECTOR_NUM_PER_SIDE = 16,       // int
            ENABLE_FRUSTUM_CULLING = 20,    // bool
            CONFIG_FILEPATH = 21,
            CONFIG_QUALITY,
            LITE_POINT_CLOUD_MODE = 32,
            FULL_POINT_CLOUD_MODE,
            LIVE_ADAPTIVE_MODE,
            MESH_REFRESH_INTERVAL = 37,
            ENABLE_SECTOR_GROUPING = 38,

            SCENE_UNDERSTANDING_ENABLE = 40,
            SCENE_UNDERSTANDING_MACHINE_VISION = 41,
            SCENE_UNDERSTANDING_CONFIG = 42,
            SCENE_UNDERSTANDING_REFINEMENT = 43,

            EXPORT_MODEL_FOR_UNITY_PROGRESS = 50,  // int: 0 - 100
            EXPORT_SCENE_UNDERSTANDING_FOR_UNITY_PROGRESS = 51,  // int: 0 - 100
        };
        /**
        An enum type for scene understanding object type.
        */
        enum SceneUnderstandingObjectType
        {
            FLOOR = 0,
            WALL = 1,
            CEILING = 2,
            CHAIR = 3,
            TABLE = 4,
            BED = 5,
            MONITOR = 6,
            WINDOW = 7,
            FURNITURE = 8,
            DOOR = 9,
            PICTURE = 10,
            PERSON = 11,
            TOTAL = 12
        };

        /**
        An enum type for RigidReconstruction input data structure.
        */
        enum InputMask
        {
            _LEFT_FRAME = 0,		            // sizeof(char) * 640 * 480 * 4
            _DEPTH_MAP = 1,		            // sizeof(float) * 640 * 480 * 1
            _FRAME_SEQ = 2,		            // sizeof(unsigned int)
            _TIME_STP = 3,		            // sizeof(unsigned int)
            _POSE = 4,		                // sizeof(float) * 16
            _LUX_LEFT = 5,		            // sizeof(int)
            _COLOR_TEMPERATURE_LEFT = 6,		// sizeof(int)
            _EXPOSURE_TIME_LEFT = 7,		    // sizeof(int)
            _ANALOG_GAIN_LEFT = 8,		    // sizeof(int)
            _DIGITAL_GAIN_LEFT = 9,		    // sizeof(int)
            _CAMERA_PARAMS = 10,             // sizeof(char) * 1032
            INPUT_MASK_MAX,
        };

        /**
        An enum type for RigidReconstruction output data structure.
        */
        enum OutputMask
        {
            FRAME_SEQ = 0,	// sizeof(unsigned int)
            POSEMTX44 = 1,	// sizeof(float) * 16
            NUM_VERTICES = 2,	// sizeof(int)
            BYTEPERVERT = 3,	// sizeof(int)
            VERTICES = 4,	// sizeof(float) * 8 * 2500000
            NUM_INDICES = 5,	// sizeof(int)
            INDICES = 6,	// sizeof(int) * 2500000
            CLDTYPE = 7,	// sizeof(int)
            COLLIDERNUM = 8,	// sizeof(unsigned int)
            CLD_NUM_VERTS = 9,	// sizeof(unsigned int) * 200
            CLD_NUMIDX = 10,	// sizeof(unsigned int) * 200
            CLD_VERTICES = 11,	// sizeof(float) * 3 * 50000
            CLD_INDICES = 12,	// sizeof(int) * 100000
            SECTOR_NUM = 13,   // sizeof(int)
            SECTOR_ID_LIST = 14,   // sizeof(int) * 1000000
            SECTOR_VERT_NUM = 15,   // sizeof(int) * 1000000
            SECTOR_IDX_NUM = 16,   // sizeof(int) * 1000000
            MODEL_CHUNK_NUM = 17,   // sizeof(int)
            MODEL_CHUNK_IDX = 18,   // sizeof(int)
            RECONSTRUCTION_STAGE = 19,  // sizeof(int)
            RECONSTRUCTION_PERCENTAGE = 20,  // sizeof(int)
            SCENE_UNDERSTANDING_STAGE = 21,  // sizeof(int)
            SCENE_UNDERSTANDING_PERCENTAGE = 22,  // sizeof(int)
            OUTPUT_MASK_MAX,
        };

        /**
        An enum type for control signal to change RigidReconstruction module's behavior.
        */
        enum Cmd {
            START = 200,
            STOP = 201,
            SHOW_INFO = 202,
            EXTRACT_POINT_CLOUD = 203,
            EXTRACT_VERTEX_NORMAL = 204,
            EXPORT_MODEL_RIGHT_HAND = 205,
            EXPORT_MODEL_FOR_UNITY = 206,
            EXPORT_SCENE_UNDERSTANDING_RIGHT_HAND = 207,
            EXPORT_SCENE_UNDERSTANDING_FOR_UNITY = 208,
            MODEL_PREVIEW_START_RIGHT_HAND = 209,
            MODEL_PREVIEW_START_FOR_UNITY = 210,
            MODEL_PREVIEW_NEXT_CHUNK = 211,
            MODEL_PREVIEW_FINISH = 212,
            EXPORT_ROOT_FOLDER = 213,
            RESET_RECONSTRUCTION_ENGINE = 214,
        };

        /**
        An enum type for reconstruction module stage of export object.
        */
        enum ExportStage {
            EXTRACT_MODEL = 0x17,
            COMPACT_TEXTURE = 0x18,
            SAVE_MODEL = 0x19,
            EXTRACT_COLLIDER = 0x1A,
            SCENE_UNDERSTANDING_PASS_1 = 0x30,
            SCENE_UNDERSTANDING_PASS_2 = 0x31,
        };

        /**
        An enum type for scene understanding object config id.
        */
        enum SceneUnderstandingConfigId {
            Floor = 300,
            Wall,
            Ceiling,
            Chair,
            Table,
            Bed,
            Monitor,
            Window,
            Furniture,
            Door,
            Picture,
            Person,
            MaxLabelId,
        };
    }
}