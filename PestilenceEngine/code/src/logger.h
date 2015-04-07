#ifndef LOGGER_H
#define LOGGER_H

#include "MyVector.h"
#include <fstream> 
#include <iostream>
#include "time.h"

// Enum to set flag for which 
enum LOG_FLAG { _ALL, _RELEASE, _GRAPHICS, _MEMORY, _SCHEDULING, _AUDIO, _AI };

class Logger
{
public: 
	// Default constructor
	Logger()
	{
		// logger created; open file? 
		//logfile.open(LOG_FILE_NAME);
			// get and log current time
		time_t now = time(0); 
		tm* localtm = localtime(&now); 
		std::cout << asctime(localtm); 
		//logfile.close();
	};

	// Stop processes, close file
	void stop()
	{
		//logfile.close();
	}
	void log(LOG_FLAG lf, std::string text)
	{
		if (hasFlag(lf)){
			logfile.open(LOG_FILE_NAME);
			logfile << text.c_str();
			logfile.close();
		}
	};

private: 
	
	// File name that the logger will print to.
	std::string LOG_FILE_NAME = "pestilencelog.txt";

	// File that the logger will print to.
	std::ofstream logfile;

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

	// Keep track of which flags are active. 
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
		switch (lf)
		{
			case (_ALL) : clearFlags();  flags.ALL = false; break;
			case (_RELEASE) : clearFlags();  flags.RELEASE = false; break;
			case (_GRAPHICS) : flags.GRAPHICS = false; break;
			case (_MEMORY) : flags.MEMORY = false;  break;
			case (_SCHEDULING) : flags.SCHEDULING = false; break;
			case (_AUDIO) : flags.AUDIO = false;
			case(_AI) : flags.AI = false;  break;
		}
	};

	void clearFlags()
	{
		flags.ALL = false; flags.AI = false; flags.AUDIO = false; 
		flags.GRAPHICS = false; flags.MEMORY = false; flags.RELEASE = false; 
		flags.SCHEDULING = false; 
	};

	// Check to see if the Logger has a specific flag
	bool hasFlag(LOG_FLAG lf)
	{
		switch (lf)
		{
		case (_ALL) : if (flags.ALL == true) return true; break;
		case(_AI) : if (flags.AI == true) return true; break; 
		case(_AUDIO) : if (flags.AUDIO == true) return true; break; 
		case (_RELEASE) : if (flags.RELEASE == true) return true; break; 
		case(_GRAPHICS) : if (flags.GRAPHICS == true) return true; break; 
		case(_MEMORY) : if (flags.MEMORY == true) return true; break; 
		case(_SCHEDULING) : if (flags.SCHEDULING == true) return true; break; 
		}
		return false;
	}
};


#endif