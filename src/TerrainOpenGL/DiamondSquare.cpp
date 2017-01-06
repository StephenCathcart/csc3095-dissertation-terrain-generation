#include "DiamondSquare.h"
#include "EasyBMP/EasyBMP.h"

DiamondSquare::DiamondSquare(void) {
	this->fileName = "heightmap";
	this->dataSize = 513;
	this->randomSeed = 256;
	this->cornerSeed = 0.0;
	this->bitDepth = 32;
	this->maxY = -1e32;
	this->minY = 1e32;

	initializeData();
	compute();
}

DiamondSquare::DiamondSquare(std::string fileName, int dataSize, const int randomSeed, const double cornerSeed, int bitDepth) {
	this->fileName = fileName;
	this->dataSize = dataSize;
	this->randomSeed = randomSeed;
	this->cornerSeed = cornerSeed;
	this->bitDepth = bitDepth;
	this->maxY = -1e32;
	this->minY = 1e32;

	initializeData();
	compute();
}

DiamondSquare::~DiamondSquare(void) {
	for(int i = 0; i < dataSize; ++i) {
		delete[] data[i];
	}
	delete[] data;
}


void DiamondSquare::initializeData() {
	data = new double*[dataSize];

	for(int i(0); i < dataSize; ++i) {
		data[i] = new double[dataSize];
	}

	for( int i(0); i < dataSize ; i++ ){
		for( int j(0); j < dataSize; j++) {
			data[i][j] = 0.0;
		}
	}
}

void DiamondSquare::compute() {
	//initialise the values of the corners
	data[0][0] = data[0][dataSize - 1] = data[dataSize - 1][0] = data[dataSize - 1][dataSize - 1] = cornerSeed;

	double h = 200.0; 	//the range (-h -> h) for the average offset
	srand(randomSeed);		//seed the random generator	

	//side length is the distance of a single square side
	//or distance of diagonal in diamond
	//each iteration we are looking at smaller squares and diamonds, we decrease the variation of the offset
	for (int sideLength = dataSize - 1; sideLength >= 2; sideLength /= 2, h /= 2.0)	{

		int halfSide = sideLength/2;

		//generate new square values
		for(int x=0; x < dataSize - 1; x += sideLength) {
			for(int y=0; y < dataSize - 1; y += sideLength) {

				//x,y is upper left corner of the square
				//calculate average of existing corners
				double avg = data[x][y] + 				//top left
					data[x + sideLength][y]   +				//top right
					data[x][y + sideLength]   + 				//lower left
					data[x + sideLength][y + sideLength]; 	//lower right

				avg /= 4.0;

				//center is average plus random offset in the range (-h, h)
				double offset = (-h) + rand() * (h - (-h)) / RAND_MAX;
				data[x + halfSide][y + halfSide] = avg + offset;

			} //for y
		} // for x


		//Generate the diamond values
		//Since diamonds are staggered, we only move x by half side
		//NOTE: if the data shouldn't wrap the x < DATA_SIZE and y < DATA_SIZE
		for (int x = 0; x < dataSize - 1; x += halfSide) {
			for (int y = (x + halfSide) % sideLength; y < dataSize - 1; y += sideLength) {

				//x,y is center of diamond
				//we must use mod and add DATA_SIZE for subtraction 
				//so that we can wrap around the array to find the corners

				double avg = 
					data[(x - halfSide + dataSize) % dataSize][y] +	//left of center
					data[(x + halfSide) % dataSize][y]				+	//right of center
					data[x][(y + halfSide) % dataSize]				+	//below center
					data[x][(y - halfSide + dataSize) % dataSize];	//above center

				avg /= 4.0;

				//new value = average plus random offset
				//calc random value in the range (-h,+h)
				double offset = (-h) + rand() * (h - (-h)) / RAND_MAX;
				avg = avg + offset;

				//update value for center of diamond
				data[x][y] = avg;

				//wrap values on the edges
				//remove this and adjust loop condition above
				//for non-wrapping values
				if (x == 0) data[dataSize - 1][y] = avg;
				if (y == 0) data[x][dataSize - 1] = avg;
			} //for y
		} //for x
	} //for sideLength

	//Calculate minY and maxY values
	for (int i = 0; i < dataSize - 1; i++){
		for(int j = 0; j < dataSize - 1; j++) {
			if (data[i][j] > maxY)
				maxY = data[i][j];
			if (data[i][j] < minY)
				minY = data[i][j];
		}
	}

	fprintf(stderr, "Done! Terrain generated at resolution of %dx%d\n", dataSize - 1, dataSize - 1);
	fprintf(stderr, "min y = %f , max y = %f \n", minY, maxY);
}

void DiamondSquare::saveToBitmap() const {
	BMP heightMap;
	// Set size to DATA_SIZE × DATA_SIZE
	heightMap.SetSize(dataSize - 1, dataSize - 1);
	// Set its color depth to 32-bits
	heightMap.SetBitDepth(bitDepth);

	for (int x = 0; x < dataSize - 1; x++) {
		for (int y = 0; y < dataSize - 1; y++) {
			// The colour to be used per pixel
			float colour = ((data[x][y] - minY) / (maxY - minY)) * 255.0;

			// Set pixel colour
			heightMap(x,y)->Red = colour;
			heightMap(x,y)->Green = colour;
			heightMap(x,y)->Blue = colour;
			heightMap(x,y)->Alpha = 255;
		}
	}
	std::string name = fileName + ".bmp";
	heightMap.WriteToFile(name.c_str());
}

double** DiamondSquare::getData() {
	return this->data;
}

float DiamondSquare::getMaxY() const {
	return this->maxY;
}

float DiamondSquare::getMinY() const {
	return this->minY;
}

std::string DiamondSquare::getFileName() const {
	return this->fileName;
}

void DiamondSquare::setFileName(const std::string fileName) {
	this->fileName = fileName;
}

int DiamondSquare::getDataSize() const {
	return this->dataSize;
}

void DiamondSquare::setDataSize(const int dataSize) {
	this->dataSize = dataSize;
}

int DiamondSquare::getRandomSeed() const {
	return this->randomSeed;
}

void DiamondSquare::setRandomSeed(const int randomSeed) {
	this->randomSeed = randomSeed;
}

double DiamondSquare::getCornerSeed() const {
	return this->cornerSeed;
}

void DiamondSquare::setCornerSeed(const double cornerSeed) {
	this->cornerSeed = cornerSeed;
}

int DiamondSquare::getBitDepth() const {
	return this->bitDepth;
}

void DiamondSquare::setBitDepth(const int bitDepth) {
	this->bitDepth = bitDepth;
}