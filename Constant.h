#ifndef CONSTANT_H_
#define CONSTANT_H_

#include "Effect.h"

class Constant : public Effect {
	private:
		Constant() : Effect() {}
	public:
		static Constant& getInstance() {
			static Constant c;
			return c;
		}

		virtual void  getRGB( unsigned char id, unsigned char* r, 
												unsigned char* g, 
												unsigned char* b );

		void setConfig( char* param );
};

#endif
