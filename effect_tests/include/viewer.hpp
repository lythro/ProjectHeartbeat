#ifndef VIEWER_H_
#define VIEWER_H_

#include <QObject>
#include <QMainWindow>
#include <QString>
#include <QTimer>

#include "ui_viewer.h"
#include "EffectManager.hpp"

class Viewer : public QMainWindow {
	Q_OBJECT

public:
	Viewer();

public slots:
	void changeConfig();
	void updateLEDs();

private:
	Ui::MainWindow* ui;
	EffectManager effects;
	QTimer timer;


};

#endif
