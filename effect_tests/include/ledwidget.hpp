#ifndef LEDWIDGET_H_
#define LEDWIDGET_H_

#include "EffectManager.hpp"
#include <QWidget>

class LEDWidget : public QWidget {
	Q_OBJECT
	
	public:
		LEDWidget( QWidget* parent = 0 ) : QWidget(parent) {
			this->effman = NULL;
		}

		void setEffectManager( EffectManager* effman ) { this->effman = effman; }
		void paintEvent( QPaintEvent* event );

	private:
		EffectManager* effman;
};

#endif
