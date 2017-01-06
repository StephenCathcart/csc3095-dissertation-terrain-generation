#ifndef TERRAINHELPER_H
#define TERRAINHELPER_H

class TerrainHelper {
public:
	static void smoothTerrain(double** data, const int dataSize, const int filterSize, const int iterations);

private:
	TerrainHelper(void);
	~TerrainHelper(void);
};

#endif

