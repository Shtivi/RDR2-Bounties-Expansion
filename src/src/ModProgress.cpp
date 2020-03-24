#include "Main.h";

using namespace std;

ModProgress::ModProgress(const char* dataFile)
{
	hasChanges = false;
	this->dataFile = dataFile;
	readFromDataFile();
}

void ModProgress::completeMission(int missionId)
{
	setMissionProgress(missionId, BountyMissionStatus::Completed);
}

void ModProgress::collectMission(int missionId)
{
	setMissionProgress(missionId, BountyMissionStatus::CollectedPoster);
}

void ModProgress::allowMission(int missionId)
{
	setMissionProgress(missionId, BountyMissionStatus::Pending);
}

void ModProgress::save()
{
	std::map<int, BountyMissionStatus>::iterator it;
	std::ofstream file;


	if (!hasChanges)
	{
		return;
	}

	log("saving mod progress");

	file.open(dataFile);;
	if (file.is_open())
	{
		it = cache.begin();

		while (it != cache.end())
		{
			std::stringstream output;
			output << it->first << " " << it->second;
			file << output.str();

			it++;
			if (it != cache.end())
			{
				file << "\n";
			}
		}

		hasChanges = false;
		file.close();
	}
}

BountyMissionStatus ModProgress::getMissionProgress(int missionId)
{
	std::map<int, BountyMissionStatus>::iterator it = cache.find(missionId);

	if (it == cache.end())
	{
		log("couldnt find");
		cache[missionId] = BountyMissionStatus::Unavailable;
		return BountyMissionStatus::Unavailable;
	}

	return it->second;;
}

void ModProgress::setMissionProgress(int missionId, BountyMissionStatus status)
{
	std::map<int, BountyMissionStatus>::iterator it = cache.find(missionId);

	if (it == cache.end())
	{
		cache[missionId] = status;
		hasChanges = true;
	}
	else
	{
		if (it->second != status)
		{
			hasChanges = true;
			it->second = status;
		}
	}

}

void ModProgress::readFromDataFile()
{
	std::ifstream file;
	std::string input;

	file.open(dataFile);;
	if (file.is_open())
	{
		log("data file opened, parsing...");

		while (!file.eof())
		{
			std::getline(file, input);
			parseToCache(input);
		}

		log("data file loaded");

		//file.close();
	}
	else
	{
		log("unable open data file for reading, trying to create new...");

		std::ofstream newFile;

		newFile.open(dataFile, std::ios_base::out);
		if (!newFile.is_open())
		{
			log("unable to create a new data file. fatal.");
			throw "Unable to create a new data file";
		}
	}
}

void ModProgress::parseToCache(std::string inputLine)
{
	std::string idStr, statusStr;
	int id, status;

	int splitPos = inputLine.find_first_of(' ');

	if (splitPos == std::string::npos)
	{
		throw "Invalid input line";
	}

	idStr = inputLine.substr(0, splitPos);
	statusStr = inputLine.substr(splitPos + 1);

	id = std::stoi(idStr);
	status = std::stoi(statusStr);

	cache[id] = (BountyMissionStatus)status;
}