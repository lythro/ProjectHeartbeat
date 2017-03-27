#include "Heartbeat.h"

/**
 *  ________
 * 1          /\
 *           /  \
 *          /    \
 *         /      \
 * 0______/        \_____
 *            t0
 *         \~width~/
 */
float Heartbeat::triangular( float t, float t0, float width ) {
	float tl = t0 - width/2.f;
	float th = t0 + width/2.f;

	if (t <= tl || t >= th) return 0.f;

	float a = 2.f/width;
	float r = 0.f;
	if (t <= t0) {
		r = 1.f - (t0 - t) * a;
	} else {
		r = 1.f - (t - t0) * a ;
	}
	return r;
}


void Heartbeat::next() {
	Effect::next();

	// TODO adjust these
	const float width = 0.3;
	const float t0 = 0.3;
	const float t1 = 0.6;

	float t = (float) this->step / this->maxSteps;
	float v = Heartbeat::triangular( t, t0, width )
			+ Heartbeat::triangular( t, t1, width );
	if (v > 1.f) v = 1.f;
	this->current_r = this->r * v;
	this->current_g = this->g * v;
	this->current_b = this->b * v;
}

void Heartbeat::getRGB( unsigned char /*id*/,
		unsigned char* r, unsigned char* g, unsigned char* b ) {
	*r = this->current_r;
	*g = this->current_g;
	*b = this->current_b;
}
