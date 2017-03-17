#include <EffectImage.h>
#include <Magick++.h>
#include <cmath>
#include <iostream>

EffectImage::EffectImage( std::string size, int numLEDs )
	: image( size, "black" ) {
	reds = new int[numLEDs];
	greens = new int[numLEDs];
	blues = new int[numLEDs];

	this->numLEDs = numLEDs;
	sizeX = image.columns()-1;
	sizeY = image.rows()-1;
	image.animationDelay(1); // 1/100 second per frame --> 100 Hz

	radstep = (M_PI/180.) * (360 / numLEDs);
	pre_radX = radstep * sizeX/4;
	pre_radY = radstep * sizeY/4;

	xmid = (sizeX - pre_radX*2)/2;
	ymid = (sizeY - pre_radY*2)/2;

	circleRadX = radstep * 0.5 * xmid;
	circleRadY = radstep * 0.5 * ymid;
}

EffectImage::~EffectImage() {
	delete[] reds;
	delete[] greens;
	delete[] blues;
}


void EffectImage::setLED( int id, int r, int g, int b ) {
	int x = xmid + cos(radstep * id + M_PI/2.) * xmid;
	int y = ymid + sin(radstep * id + M_PI/2.) * ymid;

	Magick::ColorRGB color( r/255., g/255., b/255. );
	fillEllipse( pre_radX + x, pre_radY + y, circleRadX, circleRadY, color );
}

void EffectImage::fillEllipse( int ox, int oy, int w, int h, Magick::Color color ) {
	for (int y = -h; y <= h; y++) {
		for (int x = -w; x <= w; x++) {
			if (x*x*h*h + y*y*w*w <= h*h*w*w) {
		//		std::cout << ox+x << " -- " << oy+y << std::endl;
				image.pixelColor( ox+x, oy+y, color );
			}
		}
	}
}

void EffectImage::nextFrame() {
	frames.push_back( image );
}

void EffectImage::save() {
	// TODO name
	//image.write( "test.gif" );
	Magick::writeImages( frames.begin(), frames.end(), "test.gif" );
}

void EffectImage::setDelay( int d ) {
	image.animationDelay( d );
}
