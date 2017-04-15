#ifndef COMETHAIL_H_
#define COMETHAIL_H_

#include "Effect.h"
#include "EffectSet.h"
#include "Comet.h"


class CometHail : public Effect {
	public:
		CometHail();

		void next();
		void setNumLEDs( unsigned char num );
		void getRGB( unsigned char id, unsigned char* r, unsigned char* g, unsigned char* b );
		void setConfig( char* config );

	protected:
		EffectSet<Comet> m_comets;
};

#endif
