#pragma once
#include "SeeThroughModule.h"
#include "DepthModule.h"
#include "RigidReconstructionModule.h"
#include "ofFbo.h"

namespace ofxViveSRWorks {

	enum { L = 0, R };

	class Interface {
	public:
		Interface();
		~Interface() {}

		void init(bool useMeshReconstruction = true);
		void update();
		void exit();

		const glm::mat4& getTransform(int i) const { return seeThrough.getTransform(i); }
		const ofTexture& getDistortedTexture(int i) const { return seeThrough.getDistortedTexture(i); }
		const ofTexture& getUndistortedTexture(int i) const { return seeThrough.getUndistortedTexture(i); }
		const ofTexture& getDepthTexture() const { return depth.getDepthTexture(); }
		const ofVboMesh& getMesh() const { return rigidReconstruction.getMesh(); }

		void drawMesh(ofPolyRenderMode mode = OF_MESH_WIREFRAME) const;

		/* Draw see-through image from the front stereo-camera as background*/
		void drawSeeThrough(int i) { seeThrough.draw(i); }
		
		/* Apply alpha masking for depth occlusion by reconstructed room mesh */
		void applyMask();

		ofParameterGroup& getParameters() { return group; }
	private:
		bool useMeshReconstruction;

		SeeThroughModule seeThrough;
		DepthModule depth;
		RigidReconstructionModule rigidReconstruction;
		
		std::array<ofFbo, 2> seeThroughForEye;

		ofParameterGroup group;
		ofShader meshShader;
		ofShader pointShader;

	};


}