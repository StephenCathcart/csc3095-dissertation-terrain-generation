#include "Settings.h"
#include <fstream>

float	Settings::tessLevelInner	= 70.0f;
float	Settings::tessLevelOuter	= 70.0f;
int		Settings::smoothingScale	= 0;
float	Settings::mountainScale		= 3;
bool	Settings::hasThermalErosion	= false;
int		Settings::noiseAlgorithm	= 0;
int		Settings::noiseSeed			= 2348;
int		Settings::cornerSeed		= 3;	
int		Settings::dataSize			= 129;
float	Settings::waterScale		= 0.09f;		
float	Settings::rippleIntensity	= 650.0f;
float	Settings::transparency		= 0.4f;
int		Settings::waterRed			= 1;
int		Settings::waterGreen		= 1;	
int		Settings::waterBlue			= 5;
bool	Settings::isWireMode		= false;
bool	Settings::isToonShaded		= false;
float	Settings::radius			= 100;
int		Settings::lightRed			= 1;
int		Settings::lightGreen		= 1;	
int		Settings::lightBlue			= 1;
float	Settings::groundTypeScale	= 0.3f;

void	Settings::load() {
	std::ifstream file("settings.prog");

	file >> Settings::tessLevelInner;
	file >> Settings::tessLevelOuter;
	file >> Settings::smoothingScale;
	file >> Settings::mountainScale;
	file >> Settings::hasThermalErosion;
	file >> Settings::noiseAlgorithm;
	file >> Settings::noiseSeed;
	file >> Settings::cornerSeed;
	file >> Settings::dataSize;
	file >> Settings::waterScale;
	file >> Settings::rippleIntensity;
	file >> Settings::transparency;
	file >> Settings::waterRed;
	file >> Settings::waterGreen;
	file >> Settings::waterBlue;
	file >> Settings::isWireMode;
	file >> Settings::isToonShaded;
	file >> Settings::radius;
	file >> Settings::lightRed;
	file >> Settings::lightGreen;
	file >> Settings::lightBlue;
	file >> Settings::groundTypeScale;
}

void	Settings::save() {
	std::ofstream file("settings.prog");

	file << Settings::tessLevelInner << std::endl;
	file << Settings::tessLevelOuter << std::endl;
	file << Settings::smoothingScale << std::endl;
	file << Settings::mountainScale << std::endl;
	file << Settings::hasThermalErosion << std::endl;
	file << Settings::noiseAlgorithm << std::endl;
	file << Settings::noiseSeed << std::endl;
	file << Settings::cornerSeed << std::endl;
	file << Settings::dataSize << std::endl;
	file << Settings::waterScale << std::endl;
	file << Settings::rippleIntensity << std::endl;
	file << Settings::transparency << std::endl;
	file << Settings::waterRed << std::endl;
	file << Settings::waterGreen << std::endl;
	file << Settings::waterBlue << std::endl;
	file << Settings::isWireMode << std::endl;
	file << Settings::isToonShaded << std::endl;
	file << Settings::radius << std::endl;
	file << Settings::lightRed << std::endl;
	file << Settings::lightGreen << std::endl;
	file << Settings::lightBlue << std::endl;
	file << Settings::groundTypeScale << std::endl;
}

Settings::Settings(void) {
}

Settings::~Settings(void) {
}
