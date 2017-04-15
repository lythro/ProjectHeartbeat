#ifndef METEOR_H_
#define METEOR_H_

#include "Effect.h"

class Meteor : public Effect {
	private:
		Meteor();

	public:
		static Meteor& getInstance() {
			static Meteor m;
			return m;
		}

		void getRGB( unsigned char id, unsigned char* r, unsigned char* g, unsigned char* b );
		void setConfig( char* config );

	protected:
		int length;
		unsigned char mr, mg, mb;
	
	private:
		void calcRGB( float val, unsigned char* r, unsigned char* g, unsigned char* b );

};

#endif
