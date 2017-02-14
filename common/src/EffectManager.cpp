#include "EffectManager.hpp"
#include "Effect.hpp"

EffectManager::EffectManager() {
	this->effect = new Effect();
}

void EffectManager::nextStep(){
	this->effect->next();
}

void EffectManager::getRGB( unsigned char id, unsigned char* r, unsigned char* g, unsigned char* b) {
	this->effect->getRGB( id, r, g, b );
}

void EffectManager::setConfig( char* config, int len ) {
	// TODO: parse config, cut name (and timing?), forward remaining char* to effect
}
