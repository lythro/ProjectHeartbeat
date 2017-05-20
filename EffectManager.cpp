#include "EffectManager.h"
#include "Effect.h"
#include "FullRainbow.h"
#include "Meteor.h"
#include "SetPixel.h"
#include "Heartbeat.h"
#include "Comet.h" // debug, single shot effect
#include "CometHail.h"
#include "Constant.h"

#include "string.h"
#include "stdio.h"

EffectManager::EffectManager() {
	this->effect = &FullRainbow::getInstance();

	//this->numLEDs = 120;
	//this->numLEDs = 90;
	this->numLEDs = 91; // explaination see below
	this->effect->setNumLEDs( this->numLEDs );
	this->splitMode = false;
}

void EffectManager::nextStep(){
	this->effect->next();
}

void EffectManager::getRGB( unsigned char id, unsigned char* r, unsigned char* g, unsigned char* b) {
	// adjustments to final product: the led strip is slightly shifted.
	// the first LED should be the second effect-led. -- but there is also a gap of one LED thats
	// missing since we need some space for cables etc.
	// to compensate for that, we assume to have 91 LEDs (so the virtual LED strip extends into the
	// gap), and have a shift of 2.
	id += 2;
	if (id == this->numLEDs) id = 0;

	if (this->splitMode) {
		/*
		// let numLEDs/2 be the middle from which to propagate the effect into both directions
		int mid = this->numLEDs/2;
		int nID;
		if (id < mid) nID = id;
		else nID = 2*mid - id;
		*/
		// nope. the ends are the middle
		int mid = this->numLEDs/2;
		int nID;
		if (id < mid) nID = mid - id;
		else nID = id - mid;

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
			tmp = &Effect::getInstance(); //new Effect();
		} else if (strcmp( ptr, "constant" ) == 0) {
			tmp = &Constant::getInstance(); //new Constant();
		} else if (strcmp( ptr, "heartbeat" ) == 0) {
			tmp = &Heartbeat::getInstance(); //new Heartbeat();
		} else if (strcmp( ptr, "rainbow" ) == 0) {
			tmp = &FullRainbow::getInstance(); //new FullRainbow();
		} else if (strcmp( ptr, "meteor" ) == 0) {
			tmp = &Meteor::getInstance(); //new Meteor();
		} else if (strcmp( ptr, "setpixel" ) == 0) {
			tmp = &SetPixel::getInstance();
		} else if (strcmp( ptr, "comethail" ) == 0) {
			tmp = &CometHail::getInstance(); //new CometHail();
		} else {
			success = false;
		}

		// if a valid effect name was given
		if (success) {
			// and the effect instance changed, which
			// means that this is NOT just an update to
			// SetPixel
			if (tmp != this->effect || tmp != &SetPixel::getInstance()) {
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

			this->effect = tmp; // set the new effect.
			// no need to delete the old one, since every one is singleton (?)
			
			// config AFTER number of LEDs for correct one-time calculations!
			this->effect->setConfig( params );
		}
	}
}
