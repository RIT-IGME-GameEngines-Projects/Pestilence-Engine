#ifndef LOGGER_H
#define LOGGER_H

// Enum to set flag for which 
enum LOG_FLAG = { ALL, RELEASE, GRAPHICS, MEMORY, SCHEDULING, AUDIO, AI };

class Logger
{
public: 
	// Default constructor
	Logger(); 
private: 
	MyVector<LOG_FLAG> flags; 
};


#endif