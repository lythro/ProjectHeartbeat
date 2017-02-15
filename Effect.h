#ifndef EFFECT_H_
#define EFFECT_H_

class Effect {
	public:
		Effect();
		virtual ~Effect() {};

		void next();
		virtual void  getRGB( unsigned char id, unsigned char* r, 
												unsigned char* g, 
												unsigned char* b );
		virtual void setConfig( char* config );

		int getNumLEDs() { return numLEDs; };
		void setNumLEDs( unsigned char num ) { this->numLEDs = num; }
	protected:
		int step;
		int maxSteps;
		unsigned char numLEDs;
		bool mode;
		char colour;
};

#endif