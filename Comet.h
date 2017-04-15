#ifndef COMET_H_
#define COMET_H_

#include "Effect.h"
#include "Util.h"


class Comet : public Effect {
	public:
		Comet();
		void next();
		bool isDone();

		void getRGB( unsigned char id, unsigned char *r, unsigned char *g, unsigned char *b );

	public:
		float speed, length, position;
		unsigned char r, g, b;

		// x^2 from 0 to 1 at t=tPeak and back down to 0 at t=1
		float getVal( float p );
};

#endif
