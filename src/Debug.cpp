#include "Debug.h"
#include <Windows.h>
#include <stdarg.h>
#include <stdio.h>

debug_callback_t* fpDebugCallback = (debug_callback_t*)0x0111A048;

void RegisterDebugCallback(debug_callback_t cb) {
	*fpDebugCallback = cb;
}

void DebugPrint(char *Format, ...)
{
	char DstBuf[1023];
	va_list va;

	va_start(va, Format);
	if ( *fpDebugCallback )
	{
		vsnprintf_s(DstBuf, sizeof(DstBuf), sizeof(DstBuf)-1, Format, va);
		(*fpDebugCallback)(DstBuf);
	}

	va_end(va);
}
