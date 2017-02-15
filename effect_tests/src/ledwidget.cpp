#include "ledwidget.h"
#include "EffectManager.h"

#include <QPaintEvent>
#include <QPainter>
#include <QBrush>
#include <QColor>
#include <QSize>

#include <cmath>

#include <iostream>

void LEDWidget::paintEvent( QPaintEvent* event ) {
	if (!this->effman) return;

	QSize size = this->size();
	int numLED = this->effman->getNumLEDs();
	float radstep = (M_PI/180.) * (360 / numLED);
	int pre_radX = radstep * size.width()/4;
	int pre_radY = radstep * size.height()/4;

	int xmid = (size.width()-pre_radX*2)/2;
	int ymid = (size.height()-pre_radY*2)/2;
	int circleRadX = radstep * 0.5 * xmid;
	int circleRadY = radstep * 0.5 * ymid;

	QPainter painter(this);

	for (int i = 0; i < numLED; i++) {
		int x = xmid + cos(radstep * i) * xmid;
		int y = ymid + sin(radstep * i) * ymid;
		unsigned char r, g, b;
		effman->getRGB( i, &r, &g, &b );
	//	std::cout << (int)r << " - " << (int)g << " - " << (int)b << std::endl;

		QBrush brush = QBrush(QColor(r, g, b));
		painter.setBrush( brush );
		painter.drawEllipse( QPoint(pre_radX+x, pre_radY+y), circleRadX, circleRadY );
	}
}
