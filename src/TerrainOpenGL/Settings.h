#pragma once
class Settings {
public:
	~Settings(void);

	static float	tessLevelInner;
	static float	tessLevelOuter;
	static int		smoothingScale;
	static float	mountainScale;
	static bool		hasThermalErosion;
	static int		noiseAlgorithm;
	static int		noiseSeed;
	static int		cornerSeed;
	static int		dataSize;
	static float	waterScale;
	static float	rippleIntensity;
	static float	transparency;
	static int		waterRed;
	static int		waterGreen;
	static int		waterBlue;
	static bool		isWireMode;
	static bool		isToonShaded;
	static float	radius;
	static int		lightRed;
	static int		lightGreen;
	static int		lightBlue;
	static float	groundTypeScale;

	static void		load();
	static void		save();

private:
	Settings(void);
};

