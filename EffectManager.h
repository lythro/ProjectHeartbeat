#ifndef EFFECTMANAGER_H_
#define EFFECTMANAGER_H_

#include "Effect.h"

class EffectManager {
	public:
		EffectManager();

		void setConfig( char* config );
		void nextStep();

		void getRGB( unsigned char id, unsigned char* r, unsigned char* g, unsigned char* b );
		int getNumLEDs() { return this->numLEDs; };
		int getNumSteps() { return this->effect->getNumSteps(); }

	private:
		Effect* effect;
		bool splitMode;
		int numLEDs;
	
};

#endif
