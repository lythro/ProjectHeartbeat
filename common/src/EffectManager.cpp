#include "EffectManager.hpp"
#include "Effect.hpp"
#include "FullRainbow.hpp"

#include "string.h"
#include "stdio.h"

EffectManager::EffectManager() {
	//this->effect = new Effect();
	this->effect = new FullRainbow();
}

void EffectManager::nextStep(){
	this->effect->next();
}

void EffectManager::getRGB( unsigned char id, unsigned char* r, unsigned char* g, unsigned char* b) {
	this->effect->getRGB( id, r, g, b );
}

void EffectManager::setConfig( char* config ) {
	// expect a config of the format: "name:par1 par2 par3 ..."
	char del[] = ":";
	char* ptr = strtok( config, del );
	if (ptr != NULL) {
		char* params = strtok(NULL, del);
		printf( "name: %s\n", ptr );
		printf( "params: %s\n", params );

		if (strcmp( ptr, "fillcolour" ) == 0) {
			delete this->effect;
			this->effect = new Effect();

		} else if (strcmp( ptr, "rainbow" ) == 0) {
			delete this->effect;
			this->effect = new FullRainbow();
		}

		this->effect->setConfig( params );
	}
}
