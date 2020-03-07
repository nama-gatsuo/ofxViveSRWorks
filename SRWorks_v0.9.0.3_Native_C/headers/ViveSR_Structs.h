//========= Copyright 2018, HTC Corporation. All rights reserved. ===========
#pragma once
#include <stdint.h>
namespace ViveSR
{
	struct ModuleInfo {
		int32_t Id;
		int16_t Status;
		int32_t Type;
		int16_t Port;
		int32_t Users;
	};

	enum Platform {
		CPU,
		D3D11,
		OPENGL,
	};

	enum DataType { SR_Bool, SR_Int, SR_UInt, SR_Char, SR_UChar, SR_Float, SR_UFloat, SR_String, SR_Short, SR_Double, SR_UDouble };

	struct MemoryElement {
		int16_t platform;
		int16_t mask;
		int16_t type;
		int64_t description;
		void *ptr;

		MemoryElement() {}
		MemoryElement(Platform _platform, int16_t _mask, int16_t _type, int64_t _description, void *_ptr = 0)
			: platform(_platform), mask(_mask), type(_type), description(_description), ptr(_ptr) { }
	};
}