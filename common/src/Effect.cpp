#include "Effect.hpp"

Effect::Effect() {
	this->step = 0;
	this->maxSteps = 100;
	this->numLEDs = 60;
	this->mode = false;
}

void Effect::next() {
	this->step++;
	if (this->step > this->maxSteps) {
		this->step = 0;
		this->mode = !this->mode;
	}
}

void Effect::getRGB( unsigned char id, unsigned char* r, unsigned char* g, unsigned char* b ) {
	if (id >= this->numLEDs) {
		*r = *g = *b = 0;
		return;
	}

	if (this->mode) {
		*r = 250 - this->step * 2.5;
	} else {
		*r = this->step * 2.5;
	}
	*g = *b = 0;
}



