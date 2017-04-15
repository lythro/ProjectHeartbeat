#include "CometHail.h"
#include "hsv.h"

#include "string.h"
#include "stdlib.h"
#include "stdio.h"

CometHail::CometHail() : Effect(), m_comets(1) {
	this->maxSteps = 1000;
}

void CometHail::setNumLEDs( unsigned char num ) {
	Effect::setNumLEDs( num );
	m_comets.setNumLEDs( num );
}

// number of comets.
void CometHail::setConfig( char* config ) {
	char del[] = " ";
	char* ptr = strtok( config, del );
	if (ptr != NULL) {
		int numComets = atoi(ptr);
		m_comets.resize( numComets );
	}
}

void CometHail::getRGB( unsigned char id, unsigned char* r, unsigned char* g, unsigned char* b ) {
	*r = *g = *b = 0;
	if (id >= this->numLEDs) {
		return;
	}

	m_comets.getRGB( id, r, g, b );
}

void CometHail::next() {
	Effect::next();
	m_comets.next();
}
