#pragma once

#include "Effect.h"

class SetPixel : public Effect {
	private:
		SetPixel();
		~SetPixel();

	public:
		static SetPixel& getInstance() {
			static SetPixel px;
			return px;
		}

		void setNumLEDs( unsigned char num ) override;

		void getRGB( unsigned char id, 
					unsigned char* r, 
					unsigned char* g, 
					unsigned char* b ) override;

		void setConfig( char* config ) override;

	protected:
		unsigned char *r, *g, *b;
};
