#include "Meteor.h"
#include "hsv.h"

#include "string.h"
#include "stdlib.h"
#include "stdio.h"

Meteor::Meteor() : Effect() {
	this->maxSteps = 200;
	this->length = 5;
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
		}
	}
}

void Meteor::getRGB( unsigned char id, unsigned char* r, unsigned char* g, unsigned char* b ) {
	if (id >= this->numLEDs) {
		*r = *g = *b = 0;
		return;
	}

	*r = *g = *b = 0;

	float rStep = (float)this->step/this->maxSteps;
	float rLED = (float)id/this->numLEDs;
	float rLen = (float)this->length/this->numLEDs;
	
	float relR = 1 - 1./rLen * (rStep - rLED);
	*r = 255 * relR;
}
