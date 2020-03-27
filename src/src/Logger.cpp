#include "Main.h";
#include <iostream>
#include <fstream>
#include <string>

void log(const char* msg)
{
	log(msg, "BountiesExpansion.log");
}

void log(Vector3 pos)
{
	std::stringstream output;
	output << pos.x << ", " << pos.y << ", " << pos.z;
	log(output.str().c_str());
}

void log(std::string msg)
{
	log(msg.c_str());
}

void log(const char* msg, const char* fileName)
{
	std::ofstream file;
	file.open(fileName, std::ios_base::app);

	if (file.is_open())
	{
		file << msg << "\n";
		file.close();
	}
}