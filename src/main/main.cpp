#include "presentation/PlayerApplication.hpp"
#include "factories/SfmlAudioEngineFactory.hpp"
#include "data-source/TrackRepository.hpp"

#include <iostream>
#include <stdlib.h>

int main(int argc, char* argv[])
{
	std::string dataFolderPath = "/home/"+std::string(getenv("USER"))+"/Music";
	if(argc > 1)
	{
		std::cout << "Data folder path provided: " << argv[1] << std::endl;
		dataFolderPath = argv[1];
	}
	else
	{
		std::cout << "No data folder path provided. Using default: " << dataFolderPath << std::endl;
	}
	SfmlAudioEngineFactory audioEngineFactory;
	TrackRepository trackRepository(dataFolderPath);

	PlayerApplication app(&audioEngineFactory, &trackRepository);
	app.run();
	return 0;
}
