#include "Main.h";
#include <iostream>
#include <fstream>
#include <string>

void log(const char* msg)
{
	std::ofstream file;
	file.open("BountiesExpansion.txt", std::ios_base::app);

	if (file.is_open())
	{
		file << msg << "\n";
		file.close();
	}
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