#include "Constant.h"
#include "string.h"
#include "stdlib.h"

void Constant::getRGB( unsigned char id, unsigned char *r, unsigned char *g, unsigned char *b ) {
	*r = this->r;
	*g = this->g;
	*b = this->b;
}


// r g b
void Constant::setConfig( char* config ) {
	char del[] = " ";
	// r
	char* ptr = strtok( config, del );
	if (ptr != NULL) {
		this->r = atoi(ptr);
		// g
		ptr = strtok( NULL, del );
		if (ptr != NULL) {
			this->g = atoi(ptr);
			// b
			ptr = strtok( NULL, del );
			if (ptr != NULL) {
				this->b = atoi(ptr);
			}
		}
	}
}

