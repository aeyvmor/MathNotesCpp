#include "MainWindow.h"
#include <QApplication>
#include <QSslSocket>
#include <QFontDatabase>

int main(int argc, char *argv[])
{
    qputenv("QT_SSL_BACKEND", "schannel");
QApplication a(argc, argv);

// Load the custom font from resources
int fontId = QFontDatabase::addApplicationFont(":/assets/Caveat-VariableFont_wght.ttf");
if (fontId == -1) {
    qWarning("Failed to load custom font.");
}

MainWindow w(fontId);
    w.show();
    return a.exec();
}