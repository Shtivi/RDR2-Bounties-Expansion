#include "Main.h";

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

void ModProgress::save()
{
	std::map<int, BountyMissionStatus>::iterator it;
	std::ofstream file;


	if (!hasChanges)
	{
		return;
	}

	file.open(dataFile);;
	if (file.is_open())
	{
		for (it = cache.begin(); it != cache.end(); ++it)
		{
			std::stringstream output;
			output << it->first << " " << it->second;
			file << output.str();
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
	}
	else
	{
		it->second = status;
	}

	hasChanges = true;
}

void ModProgress::readFromDataFile()
{
	std::ifstream file;
	std::string input;

	file.open(dataFile);;
	if (file.is_open())
	{
		while (!file.eof())
		{
			std::getline(file, input);
			parseToCache(input);
		}

		file.close();
	}
	else
	{
		std::ofstream newFile;

		newFile.open(dataFile, std::ios_base::out);
		if (newFile.is_open())
		{
			newFile.close();
		}
		else
		{
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