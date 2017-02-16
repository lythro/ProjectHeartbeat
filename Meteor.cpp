#include "Meteor.h"
#include "hsv.h"

#include "string.h"
#include "stdlib.h"
#include "stdio.h"

Meteor::Meteor() : Effect() {
	this->maxSteps = 200;
	this->length = 30;
}


// maxSteps = animation period
// length = length of meteor
void Meteor::setConfig( char* config ) {
	char del[] = " ";
	char* ptr = strtok( config, del );
	// max steps
	if (ptr != NULL) {
		this->maxSteps = atoi(ptr);
		
		// length of meteor in led counts
		ptr = strtok(NULL, del);
		if (ptr != NULL) {
			this->length = atoi(ptr);
			if (this->length > this->numLEDs-1) this->length = this->numLEDs-1;
		}
	}
}

void Meteor::getRGB( unsigned char id, unsigned char* r, unsigned char* g, unsigned char* b ) {
	if (id >= this->numLEDs) {
		*r = *g = *b = 0;
		return;
	}

	*r = *g = *b = 0;

	float rLED = 1. - (float) id / this->numLEDs;
	float rStep = (float) this->step / this->maxSteps;
	float rLen = (float) this->length / this->numLEDs;

	if (rLED < rStep) rLED += 1.;
	if (rLED > rStep + rLen) return;

	float rVal = (rLED - rStep)/rLen;
	calcRGB( rVal, r, g, b );
}


void Meteor::calcRGB( float val, unsigned char* r, unsigned char* g, unsigned char* b) {
	const float peak = 0.8f;
	float brightness = 0.f;
	// linear
	/*
	if (val < peak)
		brightness = val/peak;
	else
		brightness = 1 - (val-peak)/(1.-peak);
	*/

	// x^2
	float vd = (val-1);
	float pd = (peak-1);
	if (val < peak)
		brightness = (val*val)/(peak*peak);
	else
		brightness = (vd*vd)/(pd*pd);

	*r = 255 * brightness;
}
