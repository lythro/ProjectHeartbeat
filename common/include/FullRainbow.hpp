#ifndef FULLRAINBOW_H_
#define FULLRAINBOW_H_

#include "Effect.hpp"

class FullRainbow : public Effect {
	public:
		FullRainbow();

		void getRGB( unsigned char id, unsigned char* r, unsigned char* g, unsigned char* b );

	protected:
		float offset;
};

#endif
