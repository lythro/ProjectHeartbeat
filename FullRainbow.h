#ifndef FULLRAINBOW_H_
#define FULLRAINBOW_H_

#include "Effect.h"

class FullRainbow : public Effect {
	private:
		FullRainbow();

	public:
		static FullRainbow& getInstance() {
			static FullRainbow fr;
			return fr;
		}

		void getRGB( unsigned char id, unsigned char* r, unsigned char* g, unsigned char* b );
		void setConfig( char* config );

	protected:
		float offset;
		float brightness;
};

#endif
