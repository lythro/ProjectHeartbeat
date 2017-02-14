
#include "viewer.hpp"

#include <iostream>
using std::cout;
using std::endl;

Viewer::Viewer() {
	ui = new Ui::MainWindow();
	ui->setupUi( this );

	this->ui->widget->setEffectManager( &this->effects );
	this->connect( ui->lineEdit, SIGNAL(returnPressed()), this, SLOT(changeConfig()) );
	this->connect( &this->timer, SIGNAL(timeout()), this, SLOT(updateLEDs()) );

	this->timer.setInterval( 10 );
	this->timer.start();

}

void Viewer::changeConfig() {
	cout << "changeConfig: " << ui->lineEdit->displayText().toStdString() << endl;
}

void Viewer::updateLEDs() {
	this->effects.nextStep();
	this->update();
}
