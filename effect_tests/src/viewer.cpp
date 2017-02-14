
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
	char* tmp = new char[ui->lineEdit->displayText().toStdString().length()+1];
	strcpy( tmp, ui->lineEdit->displayText().toStdString().c_str() );

	this->effects.setConfig( tmp );

	delete[] tmp;
}

void Viewer::updateLEDs() {
	this->effects.nextStep();
	this->update();
}
