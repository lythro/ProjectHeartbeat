#include "Util.h"
#include <cstdlib>

float rnd(float low, float high) {
	float r = ((float) std::rand() / (RAND_MAX));
	return low + r*(high-low);
}
