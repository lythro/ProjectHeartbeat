#include <QApplication>
#include "viewer.hpp"

int main(int argc, char** args) {
	QApplication app( argc, args );

	Viewer v;
	v.show();

	app.exec();
	return 0;
}
