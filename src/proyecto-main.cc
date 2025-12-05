#include <QApplication>
#include "proyecto.h"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    ProyectoWindow window;
    window.show();

    return app.exec();
}
