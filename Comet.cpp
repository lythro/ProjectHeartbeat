#include "Comet.h"

Comet::Comet() : Effect() {
	// create a random comet.
	//speed = rnd( 0.001, 0.007 );
	//length = rnd( 0.05, 0.3 );
	float mod = rnd(0., 1.);
	speed = mod * 0.006 + 0.002;
	length = (1.-mod) * 0.35 + 0.05;

	position = -length - rnd(0.2, 1.);
	r = rnd(0., 1.) * 256;
	g = rnd(0., 1.) * 256;
	b = rnd(0., 1.) * 256;
}

void Comet::next() {
	Effect::next();
	position += speed;
	if (isDone()) position = 2.; // no reset, just cap at > 1
}


bool Comet::isDone() {
	return position >= 1.f;
}


float Comet::getVal( float p ) {
	float tPeak = position + 0.8 * length;
	float a, x;

	if (p < position) return 0;
	if (p > position + length) return 0;

	if (p < tPeak) {
		a = 1./(0.8*0.8*length*length);
		x = p - position;
	} else {
		a = 1./(0.2*0.2*length*length);
		x = p - position - length;
	}

	return a * x * x;
}

// calc rgb
void Comet::getRGB( unsigned char id, unsigned char *r, unsigned char *g, unsigned char *b ) {
	if (isDone()) {
		*r = *g = *b = 0;
		return;
	}

	float rLED = 1. - (float) id / this->numLEDs;
	float val = this->getVal( rLED );
	*r = this->r * val;
	*g = this->g * val;
	*b = this->b * val;
}

