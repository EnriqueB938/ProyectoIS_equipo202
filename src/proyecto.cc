#include "proyecto.h"
#include "ui_proyecto.h"
#include <QMessageBox>

ProyectoWindow::ProyectoWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ProyectoWindow)
{
    ui->setupUi(this);

    // Conectar botón
    connect(ui->botonSaludar, &QPushButton::clicked,
            this, &ProyectoWindow::on_botonSaludar_clicked);
}

ProyectoWindow::~ProyectoWindow() {
    delete ui;
}

void ProyectoWindow::on_botonSaludar_clicked() {
    QString nombre = ui->inputNombre->text();

    if (nombre.isEmpty()) {
        QMessageBox::information(this, "Mensaje", "Por favor introduce tu nombre.");
        return;
    }

    QMessageBox::information(this, "Saludos",
                             "¡Hola " + nombre + "!");
}
