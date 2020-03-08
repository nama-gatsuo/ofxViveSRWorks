#include "RigidReconstructionModule.h"

namespace ofxViveSRWorks {
	RigidReconstructionModule::RigidReconstructionModule() : elemCount(0), lastNumVerts(0) {
		group.setName("RigidReconstructionModule");

	}
	RigidReconstructionModule::~RigidReconstructionModule() {

	}
	void RigidReconstructionModule::start() {
		auto check = [&](int result, const std::string& taskName) {
			if (result != ViveSR::Error::WORK) {
				ofLogError("RigidConstructionModule::Start") << taskName << ": " << "Failed! (Code: " << result << ")";
				stop();
			}
		};

		check(
			ViveSR_CreateModule(ViveSR::ModuleType::ENGINE_RIGID_RECONSTRUCTION, &moduleID),
			"ViveSR_CreateModule - RIGID-RECONSTRUCTION"
		);

		ViveSR_InitialModule(moduleID);

		check(
			ViveSR_StartModule(moduleID),
			"ViveSR_StartModule - RIGID-RECONSTRUCTION"
		);

		ViveSR_SetParameterBool(moduleID, ViveSR::RigidReconstruction::Param::FULL_POINT_CLOUD_MODE, true);
		ViveSR_SetParameterBool(moduleID, ViveSR::RigidReconstruction::Cmd::START, true);

		vertices = std::make_unique<float[]>(8 * 2500000);
		indices = std::make_unique<int[]>(2500000);
		cldNumVerts = std::make_unique<uint32_t[]>(200);
		cldNumIdx = std::make_unique<uint32_t[]>(200);
		cldVertices = std::make_unique<float[]>(3 * 50000);
		cldIndices = std::make_unique<int[]>(100000);
		sectorIdList = std::make_unique<int[]>(1000000);
		sectorVertNum = std::make_unique<int[]>(1000000);
		sectorIdxNum = std::make_unique<int[]>(1000000);
		
		const int elemMax = ViveSR::RigidReconstruction::OutputMask::MODEL_CHUNK_IDX + 1;
		void* ptrs[elemMax]{
			&frameSeq,	        // sizeof(unsigned int)
			&(pose[0][0]),            // sizeof(float) * 16
			&numVertices,	    // sizeof(int)
			&stride,	        // sizeof(int)
			vertices.get(),	            // sizeof(float) * 8 * 2500000
			&numIndices,	        // sizeof(int)
			indices.get(),	            // sizeof(int) * 2500000
			&cldType,	            // sizeof(int)
			&colliderNum,	        // sizeof(unsigned int)
			cldNumVerts.get(),	    // sizeof(unsigned int) * 200
			cldNumIdx.get(),	        // sizeof(unsigned int) * 200
			cldVertices.get(),	        // sizeof(float) * 3 * 50000
			cldIndices.get(),	        // sizeof(int) * 100000
			&sectorNum,          // sizeof(int)
			sectorIdList.get(),       // sizeof(int) * 1000000
			sectorVertNum.get(),      // sizeof(int) * 1000000
			sectorIdxNum.get(),       // sizeof(int) * 1000000
			&modelChunkNum,     // sizeof(int)
			&modelChunkIdx,     // sizeof(int)
		};
		
		elements.resize(elemMax);

		for (int i = 0; i < elemMax; ++i) {
			if (ptrs[i]) {
				elements[elemCount].mask = i;
				elements[elemCount].ptr = ptrs[i];
				elemCount++;
			}
		}

	}
	void RigidReconstructionModule::update() {
		int res = ViveSR::Error::FAILED;
		res = ViveSR_GetModuleData(moduleID, elements.data(), elemCount);
		if (res == ViveSR::Error::WORK) {
			if (lastNumVerts != numVertices) {
				lastNumVerts = numVertices;
				
				mesh.clear();
				//mesh.getVbo().setVertexData(vertices.get(), 3, numVertices, GL_DYNAMIC_DRAW);
				for (int i = 0; i < numVertices; i++) {
					mesh.addVertex(glm::vec3(vertices[i * 4], vertices[i * 4 + 1], vertices[i * 4 + 2]));
				}
			}
		}
	}
	void RigidReconstructionModule::stop() {
		auto check = [&](int result, const std::string& taskName) {
			if (result != ViveSR::Error::WORK) {
				ofLogError(__FUNCTION__) << taskName << ": " << "Failed! (Code: " << result << ")";
			}
		};
		check(ViveSR_StopModule(moduleID), "ViveSR_StopModule - RIGID-RECONSTRUCTION");
		// check(ViveSR_ReleaseModule(moduleID), "ViveSR_ReleaseModule - RIGID-RECONSTRUCTION");

	}
	void RigidReconstructionModule::updateParams() {

	}
	void RigidReconstructionModule::toggle() {
		if (reconstruction) {
			ViveSR_SetParameterBool(moduleID, ViveSR::RigidReconstruction::Cmd::START, true);
		} else {
			ViveSR_SetParameterBool(moduleID, ViveSR::RigidReconstruction::Cmd::STOP, true);
		}
	}
}