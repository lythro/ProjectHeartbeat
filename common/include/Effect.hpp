#ifndef EFFECT_H_
#define EFFECT_H_

class Effect {
	public:
		Effect();

		void next();
		void getRGB( unsigned char id, unsigned char* r, unsigned char* g, unsigned char* b );

		int getNumLEDs() { return numLEDs; };
	private:
		int step;
		int maxSteps;
		unsigned char numLEDs;
		bool mode;
};

#endif
