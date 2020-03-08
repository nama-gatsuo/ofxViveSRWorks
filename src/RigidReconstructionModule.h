#pragma once
#include "ofLog.h"
#include "ofUtils.h"
#include <array>
#include "ofVectorMath.h"
#include "ofParameter.h"
#include "ofVboMesh.h"

#include "ViveSR_Enums.h"
#include "ViveSR_API_Enums.h"
#include "ViveSR_Client.h"
#include "ViveSR_Structs.h"
#include "ViveSR_RigidReconstructionEnums.h"
//#include "ViveSR_SeeThroughEnums.h"

namespace ofxViveSRWorks {
	class RigidReconstructionModule {
	public:
		RigidReconstructionModule();
		~RigidReconstructionModule();

		void start();
		void update();
		void stop();

		int getModuleID() const { return moduleID; }
		ofParameterGroup& getParameters() { return group; }
        const ofVboMesh& getMesh() const { return mesh; }

	private:
		int moduleID;

        unsigned int frameSeq;
        glm::mat4 pose;
        int numVertices, lastNumVerts;
        int stride;
        std::unique_ptr<float[]> vertices; // sizeof(float) * 8 * 2500000
        int numIndices;	                   // sizeof(int)
        std::unique_ptr<int[]> indices;	   // sizeof(int) * 2500000
        int cldType;	                   // sizeof(int)
        uint32_t colliderNum;	       // sizeof(unsigned int)
        std::unique_ptr<uint32_t[]> cldNumVerts; // sizeof(unsigned int) * 200
        std::unique_ptr<uint32_t[]> cldNumIdx;	 // sizeof(unsigned int) * 200
        std::unique_ptr<float[]> cldVertices;	 // sizeof(float) * 3 * 50000
        std::unique_ptr<int32_t[]> cldIndices;	 // sizeof(int) * 100000
        int sectorNum;                 // sizeof(int)
        std::unique_ptr<int32_t[]> sectorIdList;            // sizeof(int) * 1000000
        std::unique_ptr<int32_t[]> sectorVertNum;           // sizeof(int) * 1000000
        std::unique_ptr<int32_t[]> sectorIdxNum;            // sizeof(int) * 1000000
        int modelChunkNum;            // sizeof(int)
        int modelChunkIdx;

        std::vector<ViveSR::MemoryElement> elements;
        int elemCount;

		ofParameterGroup group;
		ofParameter<bool> reconstruction;
        ofVboMesh mesh;

		void updateParams();
		void toggle();
	};
}