///////////////////////////////////////////////////////////////////////////////////////
//
//  IMPORTANT: READ BEFORE DOWNLOADING, COPYING, INSTALLING OR USING.
//
//  By downloading, copying, installing or using the software you agree to this license.
//  If you do not agree to this license, do not download, install,
//  copy or use the software.
//
//                           License Agreement
//                     For Vive Super Reality Library
//
// Copyright (c) 2017,		HTC Corporation
//
// All rights reserved. Third party copyrights are property of their respective owners.
//
// Redistribution and use in source and binary forms, with or without modification,
// are permitted provided that the following conditions are met:
//
//   * Redistribution's of source code must retain the above copyright notice,
//     this list of conditions and the following disclaimer.
//
//   * Redistribution's in binary form must reproduce the above copyright notice,
//     this list of conditions and the following disclaimer in the documentation
//     and/or other materials provided with the distribution.
//
//   * The name of the copyright holders may not be used to endorse or promote products
//     derived from this software without specific prior written permission.
//
// This software is provided by the copyright holders and contributors "as is" and
// any express or implied warranties, including, but not limited to, the implied
// warranties of merchantability and fitness for a particular purpose are disclaimed.
// In no event shall the Intel Corporation or contributors be liable for any direct,
// indirect, incidental, special, exemplary, or consequential damages
// (including, but not limited to, procurement of substitute goods or services;
// loss of use, data, or profits; or business interruption) however caused
// and on any theory of liability, whether in contract, strict liability,
// or tort (including negligence or otherwise) arising in any way out of
// the use of this software, even if advised of the possibility of such damage.
//
///////////////////////////////////////////////////////////////////////////////////////
#pragma once
#include "ViveSR_Structs.h"
#ifdef VIVESR_CLIENT_EXPORTS
#define VIVE_SR_CLIENT __declspec(dllexport)
#else
#define VIVE_SR_CLIENT __declspec(dllimport)
#endif

using ExportProgessCB = void(*)(int, int);

extern "C" {
	/* Get the version of this library
	[out] version number x.x.x.x
	*/
	VIVE_SR_CLIENT int ViveSR_GetVersion(char** version);

	/* Initialize SRWorks framework
	[out] error code. please refer Error in ViveSR_Enums.h
	*/
	VIVE_SR_CLIENT int ViveSR_CreateContext(const char* workingDirectory, int length);

	/* Stop all process and release all settings.
	[out] error code. please refer Error in ViveSR_Enums.h
	*/
	VIVE_SR_CLIENT int ViveSR_DestroyContext();

	VIVE_SR_CLIENT int ViveSR_GetContextInfo(void* info);

	VIVE_SR_CLIENT int ViveSR_CreateModule(int moduleType, int *moduleID);
	VIVE_SR_CLIENT int ViveSR_InitialModule(int moduleID);
	VIVE_SR_CLIENT int ViveSR_StartModule(int moduleID);
	VIVE_SR_CLIENT int ViveSR_StopModule(int moduleID);
	VIVE_SR_CLIENT int ViveSR_ReleaseModule(int moduleID);
	VIVE_SR_CLIENT int ViveSR_DestroyModule(int moduleID);

	/* let module "to" able to receive data from the module "from"
	[in] module id of the sender
	[in] module id of the receiver
	[in] link mode
	[out] error code. please refer Error in ViveSR_Enums.h
	*/
	VIVE_SR_CLIENT int ViveSR_LinkModule(int from, int to, int mode);

	/* Get interested data of the specific module
	[in] module id
	[in,out] declare an array and assign its mask
	[in] length of the parameter "data".
	[out] error code. please refer Error in ViveSR_Enums.h
	*/
	VIVE_SR_CLIENT int ViveSR_GetModuleData(int moduleID, ViveSR::MemoryElement *data, unsigned int length);

	/* Get interested size of data the specific module
	[in] module id
	[in,out] declare an array and assign its mask
	[in] length of the parameter "data".
	[out] error code. please refer Error in ViveSR_Enums.h
	*/
	VIVE_SR_CLIENT int ViveSR_GetModuleDataSize(int moduleID, ViveSR::MemoryElement *data, unsigned int length);

    /* Begin periodic and asynchronous update of data of a specific module
       Note: support one subscription per module only
    [in] module id
    [in] declare an array and assign its mask
    [in] length of the parameter "data".
    [in] suggested frequency of retrieval of data.
    [out] error code. please refer Error in ViveSR_Enums.h
    */
    VIVE_SR_CLIENT int ViveSR_SubscribeModuleData(
        int moduleID, ViveSR::MemoryElement *data, unsigned int length, unsigned int target_fps = 0);

    /* End periodic and asynchronous update of data of a specific module
    [in] module id
    [out] error code. please refer Error in ViveSR_Enums.h
    */
    VIVE_SR_CLIENT int ViveSR_UnsubscribeModuleData(int moduleID);

    /**
     * Register a callback function to receive data when the module has new outputs.
     * Notice: only supports callback functions with two integers as input arguments for now
     * @param[in] moduleID module id
     * @param[in] type callback type. please refer module's header.
     * @param[in] callback_arg_0 the first input argument of the callback function
     * @param[in] callback_arg_1 the second input argument of the callback function
     * @param[in] callback function pointer of callback
     * @return error code. please refer Error in ViveSR_Enums.h
     */
	VIVE_SR_CLIENT int ViveSR_RegisterCallback(
        int moduleID, int type, int16_t callback_arg_0, int16_t callback_arg_1, ExportProgessCB callback);

    /**
     * Unegister all callback functions related to a specific module.
     * @param[in] moduleID module id
     * @param[in] type callback type. please refer module's header.
     * @return error code. please refer Error in ViveSR_Enums.h
     */
	VIVE_SR_CLIENT int ViveSR_UnregisterCallback(int moduleID, int type);

	/* Enable the log writer or not
	[in] enable or disable
	[out] error code. please refer Error in ViveSR_Enums.h
	*/
	VIVE_SR_CLIENT int ViveSR_EnableLog(bool enable);

	/* Set log level
	[in] the more higher level, the more detailed logs will be recorded. please refer SR_LogLevel in ViveSR_Enums.h
	[out] error code. please refer Error in ViveSR_Enums.h
	*/
	VIVE_SR_CLIENT int ViveSR_SetLogLevel(int level);

	/* Set specific parameter of the assigned module
	[in] module id
	[in] parameter type. please refer module's header.
	[in] parameter
	[out] error code. please refer Error in ViveSR_Enums.h
	*/
	VIVE_SR_CLIENT int ViveSR_SetParameterBool(int moduleID, int type, bool parameter);

	/* Set specific parameter of the assigned module
	[in] module id
	[in] parameter type. please refer module's header.
	[in] parameter
	[out] error code. please refer Error in ViveSR_Enums.h
	*/
	VIVE_SR_CLIENT int ViveSR_SetParameterInt(int moduleID, int type, int parameter);

	/* Set specific parameter of the assigned module
	[in] module id
	[in] parameter type. please refer module's header.
	[in] parameter
	[out] error code. please refer Error in ViveSR_Enums.h
	*/
	VIVE_SR_CLIENT int ViveSR_SetParameterFloat(int moduleID, int type, float parameter);

	/* Set specific parameter of the assigned module
	[in] module id
	[in] parameter type. please refer module's header.
	[in] parameter
	[out] error code. please refer Error in ViveSR_Enums.h
	*/
	VIVE_SR_CLIENT int ViveSR_SetParameterDouble(int moduleID, int type, double parameter);

	/* Set specific parameter of the assigned module
	[in] module id
	[in] parameter type. please refer module's header.
	[in] parameter
	[out] error code. please refer Error in ViveSR_Enums.h
	*/
	VIVE_SR_CLIENT int ViveSR_SetParameterStruct(int moduleID, int type, void *parameter, int size);

    /* Set specific parameter of the assigned module
    [in] module id
    [in] parameter type. please refer module's header.
    [in] parameter
    [out] error code. please refer Error in ViveSR_Enums.h
    */
    VIVE_SR_CLIENT int ViveSR_SetParameterMemBlock(int moduleID, int type, void *parameter, int size);

	/* Get specific parameter from the assigned module
	[in] module id
	[in] parameter type. please refer module's header.
	[out] parameter
	[out] error code. please refer Error in ViveSR_Enums.h
	*/
	VIVE_SR_CLIENT int ViveSR_GetParameterBool(int moduleID, int type, bool *parameter);

	/* Get specific parameter from the assigned module
	[in] module id
	[in] parameter type. please refer module's header.
	[out] parameter
	[out] error code. please refer Error in ViveSR_Enums.h
	*/
	VIVE_SR_CLIENT int ViveSR_GetParameterInt(int moduleID, int type, int *parameter);

	/* Get specific parameter from the assigned module
	[in] module id
	[in] parameter type. please refer module's header.
	[out] parameter
	[out] error code. please refer Error in ViveSR_Enums.h
	*/
	VIVE_SR_CLIENT int ViveSR_GetParameterFloat(int moduleID, int type, float *parameter);

	/* Get specific parameter from the assigned module
	[in] module id
	[in] parameter type. please refer module's header.
	[out] parameter
	[out] error code. please refer Error in ViveSR_Enums.h
	*/
	VIVE_SR_CLIENT int ViveSR_GetParameterDouble(int moduleID, int type, double *parameter);

    /* Get specific parameter from the assigned module
    [in] module id
    [in] parameter type. please refer module's header.
    [out] parameter. Notice: the user has the responsiblity to allocate the memory
    [int/out] expected parameter size and actual response size.
    Note: the current implementation return ViveSR::Error::NOT_MATCH if the two values are not the same
    [out] error code. please refer Error in ViveSR_Enums.h
    */
    VIVE_SR_CLIENT int ViveSR_GetParameterStruct(int moduleID, int type, void **parameter, int *parameter_size);

    /* Get specific parameter from the assigned module
    [in] module id
    [in] parameter type. please refer module's header.
    [out] parameter. Notice: the user has the responsiblity to allocate the memory
    [int/out] expected parameter size and actual response size.
    Note: the current implementation return ViveSR::Error::NOT_MATCH if the two values are not the same
    [out] error code. please refer Error in ViveSR_Enums.h
    */
	VIVE_SR_CLIENT int ViveSR_GetParameterMemBlock(int moduleID, int type, void **parameter, int *parameter_size);

	/* Get module information from the assigned module
	[in] module id
	[out] module information
	[out] error code. please refer Error in ViveSR_Enums.h
	*/
	VIVE_SR_CLIENT int ViveSR_GetModuleInfo(int moduleID, ViveSR::ModuleInfo *info);

    /* Set minimum frame interval to restrict module FPS
    [in] module id
    [in] desired frame interval
    [out] error code. please refer Error in ViveSR_Enums.h
    */
    VIVE_SR_CLIENT int ViveSR_SetMinFrameIntervalInNano(int moduleID, long long interval);

    VIVE_SR_CLIENT int ViveSR_ClearModuleError(int moduleID);
}