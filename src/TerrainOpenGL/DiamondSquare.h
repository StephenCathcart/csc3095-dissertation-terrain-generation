#ifndef DIAMONDSQUARE_H
#define DIAMONDSQUARE_H

#include <string>

class DiamondSquare {
public:
	DiamondSquare(void);
	DiamondSquare(std::string, const int dataSize, const int randomSeed, const double cornerSeed, const int bitDepth);
	~DiamondSquare(void);

	void compute();
	void saveToBitmap() const;

	double** getData();
	float getMaxY() const;
	float getMinY() const;
	std::string getFileName() const;
	void setFileName(std::string fileName);
	int getDataSize() const;
	void setDataSize(const int dataSize);
	int getRandomSeed() const;
	void setRandomSeed(const int randomSeed);
	double getCornerSeed() const;
	void setCornerSeed(const double cornerSeed);
	int getBitDepth() const;
	void setBitDepth(const int bitDepth);

private:
	void initializeData();

	//Size of the grid to generate
	//This must be (2^n)+1 (e.g. 257)
	int dataSize;

	// Seed for random generator
	int randomSeed;

	// Initial seed value for the corners of the data
	double cornerSeed;

	// Bit depth
	int bitDepth;

	// 2D array to hold heightmap image data
	double** data;

	// Range of values
	float maxY;
	float minY;

	// Name of heightmap
	std::string fileName;
};

#endif

