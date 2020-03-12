#include "RigidReconstructionModule.h"

namespace ofxViveSRWorks {
	RigidReconstructionModule::RigidReconstructionModule() : elemCount(0), lastNumVerts(0) {
		group.setName("RigidReconstructionModule");
		createParams();
	}
	RigidReconstructionModule::~RigidReconstructionModule() {

	}
	void RigidReconstructionModule::start() {
		auto check = [&](int result, const std::string& taskName) {
			if (result != ViveSR::Error::WORK) {
				ofLogError("RigidConstructionModule::Start") << taskName << ": " << "Failed! (Code: " << result << ")";
			}
		};

		check(ViveSR_CreateModule(ViveSR::ModuleType::ENGINE_RIGID_RECONSTRUCTION, &moduleID), "ViveSR_CreateModule");
		check(ViveSR_InitialModule(moduleID), "ViveSR_InitialModule");
		
		// Set to ofParameter then callbacks will be called
		mode = 0;
		maxGrid = 1.f;
		minGrid = 0.1f;

		check(ViveSR_SetParameterBool(moduleID, ViveSR::RigidReconstruction::Cmd::RESET_RECONSTRUCTION_ENGINE, true), "SET RESET_RECONSTRUCTION_ENGINE");
		check(ViveSR_SetParameterBool(moduleID, ViveSR::RigidReconstruction::Param::ENABLE_FRUSTUM_CULLING, false), "SET ENABLE_FRUSTUM_CULLING");
		check(ViveSR_SetParameterBool(moduleID, ViveSR::RigidReconstruction::Param::SCENE_UNDERSTANDING_ENABLE, false), "SET SCENE_UNDERSTANDING_ENABLE");
		
		check(ViveSR_StartModule(moduleID), "ViveSR_StartModule");
		
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
		if (!reconstruction) return;

		int res = ViveSR::Error::FAILED;
		res = ViveSR_GetModuleData(moduleID, elements.data(), elemCount);
		if (res == ViveSR::Error::WORK) {
			if (lastNumVerts != numVertices && numVertices != 0) {
				lastNumVerts = numVertices;

				if (mode == Mode::RECONSTRUCT_MESH) {
					mesh.clear();
					mesh.setMode(OF_PRIMITIVE_TRIANGLES);
					for (int i = 0; i < numVertices; i++) {
						mesh.addVertex(glm::vec3(vertices[i * 4], vertices[i * 4 + 1], - vertices[i * 4 + 2])); // invert Z value for OpenGL coordinate
					}
					mesh.addIndices(reinterpret_cast<ofIndexType*>(indices.get()), numIndices);
				} else {
					pointCloud.clear();
					pointCloud.setMode(OF_PRIMITIVE_POINTS);
					for (int i = 0; i < numVertices; i++) {
						pointCloud.addVertex(glm::vec3(vertices[i * 4], vertices[i * 4 + 1], - vertices[i * 4 + 2]));
					}
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
		check(ViveSR_StopModule(moduleID), "ViveSR_StopModule");
		// check(ViveSR_ReleaseModule(moduleID), "ViveSR_ReleaseModule - RIGID-RECONSTRUCTION");

	}
	void RigidReconstructionModule::createParams() {
		group.add(reconstruction.set("Reconstruction", false));
		e0 = reconstruction.newListener([&](bool&) {
			if (reconstruction) {
				ViveSR_SetParameterBool(moduleID, ViveSR::RigidReconstruction::Cmd::START, true);
				ofLogNotice("ofxViveSRWorks::RigidReconstructionModule") << "Start Reconstruction";
			} else {
				ViveSR_SetParameterBool(moduleID, ViveSR::RigidReconstruction::Cmd::STOP, true);
				ofLogNotice("ofxViveSRWorks::RigidReconstructionModule") << "Stop Reconstruction";
			}
		});

		group.add(mode.set("Mode", 0, 0, 2));
		e1 = mode.newListener([&](int&) {
			std::vector<bool> flags(3);
			std::string modeName;
			if (mode == Mode::VIEW_CLOUD) {
				flags = { true, false, false };
				modeName = "LITE_POINT_CLOUD_MODE";
			} else if (mode == Mode::VIEW_CLOUD_FULL) {
				flags = { false, false, true };
				modeName = "FULL_POINT_CLOUD_MODE";
			} else if (mode == Mode::RECONSTRUCT_MESH) {
				flags = { false, true, false };
				modeName = "LIVE_ADAPTIVE_MODE";
			}
			ViveSR_SetParameterBool(moduleID, ViveSR::RigidReconstruction::Param::LITE_POINT_CLOUD_MODE, flags[0]);
			ViveSR_SetParameterBool(moduleID, ViveSR::RigidReconstruction::Param::LIVE_ADAPTIVE_MODE, flags[1]);
			ViveSR_SetParameterBool(moduleID, ViveSR::RigidReconstruction::Param::FULL_POINT_CLOUD_MODE, flags[2]);

			ofLogNotice("ofxViveSRWorks::RigidReconstructionModule") << "ModeName: " << modeName;

		});

		group.add(maxGrid.set("MaxGrid", 1.f, 0.01f, 2.f));
		e2 = maxGrid.newListener([&](float&) {
			ViveSR_SetParameterFloat(moduleID, ViveSR::RigidReconstruction::Param::ADAPTIVE_MAX_GRID, maxGrid.get());
		});

		group.add(minGrid.set("MinGrid", 1.f, 0.01f, 2.f));
		e3 = minGrid.newListener([&](float&) {
			ViveSR_SetParameterFloat(moduleID, ViveSR::RigidReconstruction::Param::ADAPTIVE_MIN_GRID, minGrid.get());
		});

		
	}

}
