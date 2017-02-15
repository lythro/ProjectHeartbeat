#include "EffectManager.h"
#include "Effect.h"
#include "FullRainbow.h"

#include "string.h"
#include "stdio.h"

EffectManager::EffectManager() {
	//this->effect = new Effect();
	this->effect = new FullRainbow();

	this->numLEDs = 120;
	this->effect->setNumLEDs( this->numLEDs );
	this->splitMode = false;
}

void EffectManager::nextStep(){
	this->effect->next();
}

void EffectManager::getRGB( unsigned char id, unsigned char* r, unsigned char* g, unsigned char* b) {
	if (this->splitMode) {
		// let numLEDs/2 be the middle from which to propagate the effect into both directions
		int mid = this->numLEDs/2;
		int nID;
		if (id < mid) nID = id;
		else nID = 2*mid - id;
		this->effect->getRGB( nID, r, g, b );
	} else {
		this->effect->getRGB( id, r, g, b );
	}
}

void EffectManager::setConfig( char* config ) {
	// expect a config of the format: "name:par1 par2 par3 ..."
	char del[] = ":";
	char* ptr = strtok( config, del );
	if (ptr != NULL) {
		// first: check for "split" which indicates split-mode!
		bool split = false;
		if (strcmp( ptr, "split" ) == 0) {
			split = true;
			ptr = strtok( NULL, del );
			if (ptr == NULL) return;
		}

		// extract parameter-section
		char* params = strtok(NULL, del);
//		printf( "name: %s\n", ptr );
//		printf( "params: %s\n", params );

		bool success = true;
		if (strcmp( ptr, "fillcolour" ) == 0) {
			delete this->effect;
			this->effect = new Effect();

		} else if (strcmp( ptr, "rainbow" ) == 0) {
			delete this->effect;
			this->effect = new FullRainbow();
		} else {
			success = false;
		}

		if (success) {
			if (split) {
				this->splitMode = true;
				this->effect->setNumLEDs( this->numLEDs/2 + 1 );
			} else {
				this->splitMode = false;
				this->effect->setNumLEDs( this->numLEDs );
			}
			// config AFTER number of LEDs for correct one-time calculations!
			this->effect->setConfig( params );
		}
	}
}
