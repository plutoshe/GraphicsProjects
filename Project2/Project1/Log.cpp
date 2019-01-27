#include "Log.h"

#include <assert.h>
#include <stdio.h>
#include <cstdlib>
#include <stdarg.h>		// for va_<xxx>
#include <stdio.h>		// for vsprintf_s()
#include <Windows.h>	// for OutputDebugStringA(). Uggh.. this pulls in a lot of Windows specific stuff

namespace Engine {


	void Log(const LOG_MODE mod, const char * i_fmt, ...)
	{
		assert(i_fmt);
		assert(strlen(i_fmt) <= 256);

		const size_t lenTemp = 256;
		char strTemp[lenTemp];
		switch (mod)
		{
		case LOG_DEBUG:
			strcpy_s(strTemp, "Log: ");
			break;
		case LOG_WARNING:
			strcpy_s(strTemp, "Warning: ");
			break;
		case LOG_ERROR:
			strcpy_s(strTemp, "Error: ");
			break;
		case LOG_FATAL:
			strcpy_s(strTemp, "Fatal: ");
			break;
		default:
			break;
		}


		strcat_s(strTemp, i_fmt);
		strcat_s(strTemp, "\n");
		const size_t lenOutput = lenTemp + 32;

		char strOutput[lenOutput];

		// define a variable argument list variable 
		va_list args;

		// initialize it. second parameter is variable immediately
		// preceeding variable arguments
		va_start(args, i_fmt);

		// (safely) print our formatted string to a char buffer
		vsprintf_s(strOutput, lenOutput, strTemp, args);

		va_end(args);
		switch (mod)
		{
		case LOG_DEBUG:
			OutputDebugStringA(strOutput);
			break;
		case LOG_WARNING:
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x000E);
			OutputDebugStringA(strOutput);
			printf(strOutput);
			break;
		case LOG_ERROR:
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x000C);
			OutputDebugStringA(strOutput);
			printf(strOutput);
			break;
		case LOG_FATAL:
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x000F);
			OutputDebugStringA(strOutput);
			printf(strOutput);
			exit(1);
			break;
		default:
			break;
		}
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x000F);
		return;
	}

}