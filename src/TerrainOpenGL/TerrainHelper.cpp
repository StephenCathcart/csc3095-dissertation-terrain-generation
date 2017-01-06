#include "TerrainHelper.h"
#include <iostream>

TerrainHelper::TerrainHelper(void) {
}


TerrainHelper::~TerrainHelper(void) {
}

// SmoothTerrain
// Operates on a 2d array of doubles
// Smooths terrain data using an averaging box filter 
// The filtersize should be 2^n + 1
void TerrainHelper::smoothTerrain(double** data, const int dataSize, const int filterSize, const int iterations) {
	for(int i(0); i < iterations; i++) {

		int count = 0;
		float total = 0;

		//loop through all the values
		for(int x = 0; x < dataSize - 1; x++) {
			for(int y = 0; y < dataSize - 1; y++) {

				//count keeps track of how many points contribute to the total value at this point
				//total stores the summation of points around this point
				//Reset the count
				count = 0;
				total = 0;

				//loop through the points around this one (contained in the filter)
				for (int x0 = x - filterSize; x0 <= x + filterSize; x0++) {
					//if the point is outside the data set, ignore it
					if (x0 < 0 || x0 > dataSize-1) {
						continue;
					}
					for(int y0 = y - filterSize; y0 <= y + filterSize; y0++) {
						if(y0 < 0 || y0 > dataSize-1)
							continue;

						//add the contribution from the filter to the total for this point
						total += data[x0][y0];
						count++;

					} //y0
				} //x0
				//Store the averaged value
				if (count != 0 && total != 0) {
					data[x][y] = total / (float)count;
				}
			} //y
		} //x
	}
}