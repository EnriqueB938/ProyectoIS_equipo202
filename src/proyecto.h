#ifndef PROYECTO_H
#define PROYECTO_H

#include <QWidget>

namespace Ui {
class ProyectoWindow;
}

class ProyectoWindow : public QWidget {
    Q_OBJECT

public:
    explicit ProyectoWindow(QWidget *parent = nullptr);
    ~ProyectoWindow();

private slots:
    void on_botonSaludar_clicked();

private:
    Ui::ProyectoWindow *ui;
};

#endif // PROYECTO_H
