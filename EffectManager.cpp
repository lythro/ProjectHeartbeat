#include "EffectManager.h"
#include "Effect.h"
#include "FullRainbow.h"
#include "Meteor.h"
#include "SetPixel.h"
#include "Heartbeat.h"

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
		Effect* tmp;
		if (strcmp( ptr, "fillcolour" ) == 0) {
			tmp = new Effect();
		} else if (strcmp( ptr, "heartbeat" ) == 0) {
			tmp = new Heartbeat();
		} else if (strcmp( ptr, "rainbow" ) == 0) {
			tmp = new FullRainbow();
		} else if (strcmp( ptr, "meteor" ) == 0) {
			tmp = new Meteor();
		} else if (strcmp( ptr, "setpixel" ) == 0) {
			tmp = &SetPixel::getInstance();
		} else {
			success = false;
		}

		// if a valid effect name was given
		if (success) {
			// and the effect instance changed, which
			// means that this is NOT just an update to
			// SetPixel
			if (tmp != this->effect) {
				// adjust the number of leds
				if (split) {
					// TODO split mode doesn't make sense for
					// some effects! (setpixel)
					this->splitMode = true;
					tmp->setNumLEDs( this->numLEDs/2 + 1 );
				} else {
					this->splitMode = false;
					tmp->setNumLEDs( this->numLEDs );
				}
			}

			// delete the old effect
			if (this->effect != &SetPixel::getInstance()) {
				delete this->effect;
			}
			this->effect = tmp; // set the new
			// config AFTER number of LEDs for correct one-time calculations!
			this->effect->setConfig( params );
		}
	}
}
