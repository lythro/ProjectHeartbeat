#pragma once

#include "Effect.h"

class Heartbeat : public Effect {
	public:
		Heartbeat() : Effect() {
			this->current_r = this->current_g = this->current_b = 0;
		}

		void getRGB( unsigned char id, unsigned char* r, unsigned char* g, unsigned char* b );
		void next();

	protected:
		static float triangular( float t, float t0, float width );

		unsigned char current_r, current_g, current_b;
};
