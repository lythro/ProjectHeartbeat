#include "FullRainbow.hpp"
#include "hsv.hpp"

FullRainbow::FullRainbow() : Effect() {
	this->maxSteps = 200;
	this->offset = this->maxSteps/this->getNumLEDs();
}

void FullRainbow::getRGB( unsigned char id, unsigned char* r, unsigned char* g, unsigned char* b ) {
	if (id >= this->numLEDs) {
		*r = *g = *b = 0;
		return;
	}

	float s = this->offset * id + this->step;
	while (s > this->maxSteps) s = s - this->maxSteps;

	hsv2rgb( s/this->maxSteps, 1., 1., r, g, b );
}
