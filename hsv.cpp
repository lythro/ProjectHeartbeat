#include "hsv.h"

void hsv2rgb(float h, float s, float v, 
			unsigned char* r, unsigned char* g, unsigned char* b) {
	float H = h * 360.f;
	int hi = H/60.;
	float f = H/60. - hi;

	float p = v * (1 - s);
	float q = v * (1 - s*f);
	float t = v * (1 - s * (1-f));

	float fr, fg, fb;
	switch (hi) {
		case 0:
		case 6:
			fr = v; fg = t; fb = p;
			break;
		case 1:
			fr = q; fg = v; fb = p;
			break;
		case 2:
			fr = p; fg = v; fb = t;
			break;
		case 3:
			fr = p; fg = q; fb = v;
			break;
		case 4:
			fr = t; fg = p; fb = v;
			break;
		case 5:
			fr = v; fg = p; fb = q;
			break;
	}
	*r = 255*fr;
	*g = 255*fg;
	*b = 255*fb;
}

