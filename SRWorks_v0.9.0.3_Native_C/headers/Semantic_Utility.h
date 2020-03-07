#pragma once
#include <stdint.h>
#include "ViveSR_RigidReconstructionEnums.h" 

// TODO: replace with int array in future release
struct SceneUnderstandingConfig {
    union
    {
        struct
        {
            int32_t nFloorMaxInst;
            int32_t nWallMaxInst;
            int32_t nCeilingMaxInst;
            int32_t nChairMaxInst;
            int32_t nTableMaxInst;
            int32_t nBedMaxInst;
            int32_t nMonitorMaxInst;
            int32_t nWindowMaxInst;
            int32_t nFurnitureMaxInst;
            int32_t nDoorMaxInst;
            int32_t nPictureMaxInst;
            int32_t nPersonMaxInst;
        };
        int32_t nMaxDetectInstance[ViveSR::RigidReconstruction::SceneUnderstandingObjectType::TOTAL];
    };
};
