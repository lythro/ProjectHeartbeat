#include "Effect.hpp"
#include "string.h"
#include "stdlib.h"

Effect::Effect() {
	this->step = 0;
	this->maxSteps = 100;
	this->numLEDs = 60;
	this->mode = false;
	this->colour = 'r';
}

void Effect::next() {
	this->step++;
	if (this->step > this->maxSteps) {
		this->step = 0;
		this->mode = !this->mode;
	}
}


// 'r' for fade black <-> red
// 'g' for                green
// 'b' for                blue
void Effect::setConfig( char* config ) {
	char del[] = " ";
	char* ptr = strtok( config, del );
	if (ptr != NULL) {
		if (ptr[0] == 'r' || ptr[0] == 'g' || ptr[0] == 'b')
			this->colour = ptr[0];
	}
}


void Effect::getRGB( unsigned char id, unsigned char* r, unsigned char* g, unsigned char* b ) {
	if (id >= this->numLEDs) {
		*r = *g = *b = 0;
		return;
	}

	unsigned char* c;
	if (this->colour == 'r') c = r;
	else if (this->colour == 'g') c = g;
	else c = b;

	*r = *g = *b = 0;
	if (this->mode) {
		*c = 250 - this->step * 2.5;
	} else {
		*c = this->step * 2.5;
	}
}



