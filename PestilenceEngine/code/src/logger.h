#ifndef LOGGER_H
#define LOGGER_H

#include "MyVector.h"

// Enum to set flag for which 
enum LOG_FLAG { _ALL, _RELEASE, _GRAPHICS, _MEMORY, _SCHEDULING, _AUDIO, _AI };

class Logger
{
public: 
	// Default constructor
	Logger()
	{

	};
private: 
	// Keep track of which LOG_FLAGs are flagged. 
	struct FLAG_LIST
	{
		bool ALL = false; 
		bool RELEASE = false; 
		bool GRAPHICS = false; 
		bool MEMORY = false; 
		bool SCHEDULING = false; 
		bool AUDIO = false; 
		bool AI = false; 
	};
	FLAG_LIST flags; 

	// Add a flag to the list of flags to log. 
	void addFlag(LOG_FLAG lf)
	{
		switch (lf)
		{
			case (_ALL) : clearFlags();  flags.ALL = true; break;
			case (_RELEASE) : clearFlags();  flags.RELEASE = true; break;
			case (_GRAPHICS) : flags.GRAPHICS = true; break; 
			case (_MEMORY) : flags.MEMORY = true;  break;
			case (_SCHEDULING) : flags.SCHEDULING = true; break;
			case (_AUDIO) : flags.AUDIO = true;
			case(_AI) : flags.AI = true;  break;
		}
	};

	// Remove a flag from the list
	void removeFlag(LOG_FLAG lf)
	{
		
	};

	void clearFlags()
	{
		
	};

	// Check to see if the Logger has a specific flag
	bool hasFlag(LOG_FLAG lf)
	{
		
	}
};


#endif