#ifndef LOGGER_H
#define LOGGER_H

#include "MyVector.h"

// Enum to set flag for which 
enum LOG_FLAG { ALL, RELEASE, GRAPHICS, MEMORY, SCHEDULING, AUDIO, AI };

class Logger
{
public: 
	// Default constructor
	Logger()
	{
		flags = new MyVector<LOG_FLAG>();

	};
private: 
	// Pointer to a MyVector - stored on heap
	MyVector<LOG_FLAG>* flags; 

	// Add a flag to the list of flags to log. 
	void addFlag(LOG_FLAG lf)
	{
		// If the flag is ALL, remove everything in vector and replace with ALL
		if (lf == ALL)
		{
			flags->Release();
			flags->Push(lf);
		}
		else
		{
			flags->Push(lf);
		}
	};

	// Remove a flag from the list
	void removeFlag(LOG_FLAG lf)
	{
		for (int i = 0; i < flags->GetSize(); i++)
		{
			if (flags->GetCopyAt(i) == lf)
			{
				// Remove it
				flags->RetrieveByIndex(i);
				return; // No more!
			}
		}
	};

	void clearFlags()
	{
		flags->Release();
	};

	// Check to see if the Logger has a specific flag
	bool hasFlag(LOG_FLAG lf)
	{
		for (int i = 0; i < flags->GetSize(); i++)
		{
			if (flags->GetCopyAt(i) == lf) return true;
		}
		return false;
	}
};


#endif