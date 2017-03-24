#include "Effect.h"
#include "string.h"
#include "stdlib.h"

Effect::Effect() {
	this->step = 0;
	this->maxSteps = 100;
	this->mode = false;
	this->numLEDs = 60;
	this->r = 255;
	this->g = 0;
	this->b = 0;
}

void Effect::next() {
	this->step++;
	if (this->step > this->maxSteps) {
		this->step = 0;
		this->mode = !this->mode;
	}
}


// maxSteps r g b
void Effect::setConfig( char* config ) {
	char del[] = " ";
	// r
	char* ptr = strtok( config, del );
	if (ptr != NULL) {
		this->maxSteps = atoi(ptr);

		// r
		ptr = strtok( NULL, del );
		if (ptr != NULL) {
			this->r = atoi(ptr);
			// g
			ptr = strtok( NULL, del );
			if (ptr != NULL) {
				this->g = atoi(ptr);
				// b
				ptr = strtok( NULL, del );
				if (ptr != NULL) {
					this->b = atoi(ptr);
				}
			}
		}
	}
}



void Effect::getRGB( unsigned char id, unsigned char* r, unsigned char* g, unsigned char* b ) {
	if (id >= this->numLEDs) {
		*r = *g = *b = 0;
		return;
	}

	float dim = (float) this->step / this->maxSteps;
	if (mode) dim = 1.f - dim;

	*r = dim * this->r;
	*g = dim * this->g;
	*b = dim * this->b;
}



