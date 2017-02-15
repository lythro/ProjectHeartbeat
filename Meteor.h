#ifndef METEOR_H_
#define METEOR_H_

#include "Effect.h"
#include "hsv.h"

class Meteor : public Effect {
	public:
		Meteor();

		void getRGB( unsigned char id, unsigned char* r, unsigned char* g, unsigned char* b );
		void setConfig( char* config );

	protected:
		int length;

};

#endif
