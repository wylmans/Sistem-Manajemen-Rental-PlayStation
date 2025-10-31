#include "MainWindow.h"
#include <QApplication>
#include <QFile>

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    QFile styleFile("assets/style.qss");
    if (styleFile.open(QFile::ReadOnly))
        app.setStyleSheet(styleFile.readAll());

    MainWindow window;
    window.resize(1200, 700);
    window.show();

    return app.exec();
}
