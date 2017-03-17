#pragma once
#include <string>
#include <Magick++.h>
#include <vector>

class EffectImage {
	public:
		EffectImage( std::string size, int numLEDs );
		~EffectImage();

		void setLED( int id, int r, int g, int b );
		void setDelay( int d );
		void fillEllipse( int x, int y, int w, int h, Magick::Color );

		void nextFrame();
		void save();

	protected:
		int numLEDs;
		int sizeX, sizeY;
		int xmid, ymid;
		float radstep;
		int circleRadX, circleRadY;
		int pre_radX, pre_radY;

		int *reds, *greens, *blues;
		Magick::Image image;
		std::vector<Magick::Image> frames;

};
