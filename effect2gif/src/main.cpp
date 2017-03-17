#include <Magick++.h>
#include <iostream>
using std::cout;
using std::endl;

#include <EffectImage.h>
#include <EffectManager.h>

#include <stdio.h>

int main(int argc, char** argv) {
	Magick::InitializeMagick(*argv);

	if (argc < 2) {
		cout << argv[0] << " <config>" << endl;
		return 1;
	}

	EffectManager eff;
	eff.setConfig( argv[1] );

	EffectImage image( "500x500", 120 );
	cout << eff.getNumLEDs() << endl;
	cout << eff.getNumSteps() << endl;
	
	int max = eff.getNumSteps();
	// restrict gif size, use max 100 frames!
	int numT = 100;
	int numSkip = 1;
	if (max <= numT) {
		numT = max;
	} else {
		numSkip = max / numT;
	}
	image.setDelay( numSkip );


	unsigned char r, g, b;
	for (int t = 0; t < numT; t++) {
		for (int i = 0; i < 120; i++) {
			eff.getRGB( i, &r, &g, &b );
			image.setLED( i, r, g, b );
		}

		image.nextFrame();
		for (int skip = 0; skip < numSkip; skip++) {
			eff.nextStep();
		}

		printf( "[%4i/%4i]\r", t, numT );
		cout << std::flush;
	}
	cout << endl << "saving ..." << endl;

	image.save();
	return 0;
}
