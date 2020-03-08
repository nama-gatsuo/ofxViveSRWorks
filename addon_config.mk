meta:
	ADDON_NAME = ofxOpenVrUtil
	ADDON_DESCRIPTION = Addon to access HTC Vive COSMOS xR experience
	ADDON_AUTHOR = Ayumu Nagamatsu
	ADDON_TAGS = "VR" "HTC Vive COSOMS" "Sense SDK" "SRWorks"
	ADDON_URL = http://github.com/nama-gatsuo/ofxViveSRWorks

common:

vs:
	# ADDON_DLLS_TO_COPY += "openvr/bin/win64/openvr_api.dll"
	ADDON_LIBS		+= "SRWorks_v0.9.0.3_Native_C/libs/ViveSRWorks_Client.lib"
	ADDON_INCLUDES	+= "SRWorks_v0.9.0.3_Native_C/headers/"
	ADDON_DLLS_TO_COPY += "SRWorks_v0.9.0.3_Native_C/x64/Release/ViveSRWorks_Client.dll"
	ADDON_DLLS_TO_COPY += "SRWorks_v0.9.0.3_Native_C/x64/Release/SRWorks_Log.dll"
	ADDON_DLLS_TO_COPY += "SRWorks_v0.9.0.3_Native_C/x64/Release/ViveSR_CommunicationRules.dll"
