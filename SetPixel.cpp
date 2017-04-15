#include "SetPixel.h"
#include <string.h>
#include <stdlib.h>

SetPixel::SetPixel() { //: Effect() {
	int leds = this->getNumLEDs();
	this->r = new unsigned char[leds];
	this->g = new unsigned char[leds];
	this->b = new unsigned char[leds];

	for (int i = 0; i < leds; i++) {
		this->r[i] = 0;
		this->g[i] = 0;
		this->b[i] = 0;
	}
}

void SetPixel::setNumLEDs( unsigned char num ) {
	Effect::setNumLEDs( num );

	delete[] this->r;
	delete[] this->g;
	delete[] this->b;

	this->r = new unsigned char[num];
	this->g = new unsigned char[num];
	this->b = new unsigned char[num];
	
	for (int i = 0; i < num; i++) {
		this->r[i] = 0;
		this->g[i] = 0;
		this->b[i] = 0;
	}

}

SetPixel::~SetPixel() {
	delete[] this->r;
	delete[] this->g;
	delete[] this->b;
}

void SetPixel::getRGB( unsigned char id, unsigned char* r, unsigned char* g, unsigned char* b) {
	if (id >= this->getNumLEDs()) {
		*r = *g = *b = 255;
		return;
	}

	*r = this->r[id];
	*g = this->g[id];
	*b = this->b[id];
}

// id r g b
void SetPixel::setConfig( char* config ) {
	char del[] = " ";
	char* ptr = strtok( config, del );

	unsigned char id, r,g,b;
	// id
	if (ptr != NULL) {
		id = atoi(ptr);
		if (id >= this->getNumLEDs()) return;
		// r
		ptr = strtok( NULL, del );
		if (ptr != NULL) {
			r = atoi(ptr);
			// g
			ptr = strtok( NULL, del );
			if (ptr != NULL) {
				g = atoi(ptr);
				// b
				ptr = strtok( NULL, del );
				if (ptr != NULL) {
					b = atoi(ptr);
				} else return;
			} else return;
		} else return;
	} else return;

	// set:
	this->r[id] = r;
	this->g[id] = g;
	this->b[id] = b;
}
