#pragma once

enum LOG_MODE
{
	LOG_DEBUG = 0,
	LOG_WARNING = 1,
	LOG_ERROR = 2,
	LOG_FATAL = 3,
};
#ifdef _DEBUG
#define DEBUG_LOG(fmt, ...) Engine::Log(LOG_DEBUG, fmt, __VA_ARGS__)
#else 
#define DEBUG_LOG(fmt, ...)
#endif

#define WARNING_LOG(fmt, ...)  Engine::Log(LOG_WARNING, fmt, __VA_ARGS__);
#define ERROR_LOG(fmt, ...)  Engine::Log(LOG_ERROR, fmt, __VA_ARGS__);
#define FATAL_LOG(fmt, ...)  Engine::Log(LOG_FATAL, fmt, __VA_ARGS__);

namespace Engine {
	void Log(LOG_MODE mod, const char * i_fmt, ...);
}


