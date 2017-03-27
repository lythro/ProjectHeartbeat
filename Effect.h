#ifndef EFFECT_H_
#define EFFECT_H_

class Effect {
	public:
		Effect();
		virtual ~Effect() {};

		virtual void next();
		virtual void  getRGB( unsigned char id, unsigned char* r, 
												unsigned char* g, 
												unsigned char* b );
		virtual void setConfig( char* config );

		int getNumLEDs() { return numLEDs; };
		virtual void setNumLEDs( unsigned char num ) { this->numLEDs = num; }

		int getNumSteps() { return maxSteps; }
	protected:
		int step;
		int maxSteps;
		unsigned char numLEDs;
		unsigned char r, g, b;
};

#endif
