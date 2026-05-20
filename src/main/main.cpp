#include "presentation/PlayerApplication.hpp"
#include "factories/SfmlAudioEngineFactory.hpp"
#include "data-source/TrackRepository.hpp"

int main(int argc, char* argv[])
{
	SfmlAudioEngineFactory audioEngineFactory;
	audioEngineFactory.createAudioEngine();
	// TrackRepository trackRepository(argc > 1 ? argv[1] : "data");

	// PlayerApplication app(&audioEngineFactory, &trackRepository);
	return 0;
}
