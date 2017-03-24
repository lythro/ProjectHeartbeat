#include "FullRainbow.h"
#include "hsv.h"

#include "string.h"
#include "stdlib.h"
#include "stdio.h"

FullRainbow::FullRainbow() : Effect() {
	this->maxSteps = 200;
	this->offset = (float)this->maxSteps/this->numLEDs;
	this->brightness = 1.;
}


// rainbow:maxSteps colorRange brightness
// int maxSteps --> how fast does the change happen?
// int numCircles --> how many hsv-circles to show?
void FullRainbow::setConfig( char* config ) {
	char del[] = " ";
	char* ptr = strtok( config, del );
	// max steps
	if (ptr != NULL) {
		this->maxSteps = atoi(ptr);
		
		// num hsv circles
		ptr = strtok(NULL, del);
		if (ptr != NULL) {
			int num = atoi(ptr);
			this->offset = ((float)this->maxSteps/this->numLEDs) * num;

			// brightness
			ptr = strtok(NULL, del);
			if (ptr != NULL) {
				float br = atof(ptr);
				if (0.f <= br && br <= 1.f) this->brightness = br;
			}
		}
	}
}

void FullRainbow::getRGB( unsigned char id, unsigned char* r, unsigned char* g, unsigned char* b ) {
	if (id >= this->numLEDs) {
		*r = *g = *b = 0;
		return;
	}

	float s = this->offset * id + this->step;
	while (s > this->maxSteps) s = s - this->maxSteps;

	hsv2rgb( s/this->maxSteps, 1., this->brightness, r, g, b );
}
