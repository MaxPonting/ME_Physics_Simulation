#include "Log.h"

#include <SDL.h>

#include <iostream>

namespace ME
{
	//
	// Print a log to console that contains:
	// Time in hour:minute:seconds format since the engine started.
	// The type of log.
	// The log itself.
	//
	void Log::PrintToLog(std::string prefix, std::string log)
	{		
		std::cout << prefix << "[" << log << "]" << std::endl;
	}
}
