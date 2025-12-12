#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QInputDialog> // Para que el tutor elija con quién hablar

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->stackedWidget->setCurrentIndex(0); // Mostrar Login al inicio
}

MainWindow::~MainWindow()
{
    delete ui;
    if (usuarioActual) delete usuarioActual;
}

// 1. LOGICA DE LOGIN
void MainWindow::on_btnLogin_clicked()
{
    QString user = ui->inputUser->text();
    QString pass = ui->inputPass->text();

    usuarioActual = dataManager.validarUsuario(user, pass);

    if (usuarioActual) {
        ui->stackedWidget->setCurrentIndex(1); // Ir al chat
        configurarInterfazSegunRol();
        actualizarChatUI();
    } else {
        QMessageBox::warning(this, "Error", "Credenciales incorrectas");
    }
}

// 2. CONFIGURAR VISTA (ALUMNO vs TUTOR)
void MainWindow::configurarInterfazSegunRol() {
    ui->labelInfo->setText("Hola, " + usuarioActual->nombre + " (" + usuarioActual->rol + ")");
    ui->chatDisplay->clear();

    if (usuarioActual->rol == "alumno") {
        ui->btnAsignar->setVisible(true);
        if (usuarioActual->idTutor == 0) {
            ui->chatDisplay->setText("No tienes tutor asignado. Pulsa 'Asignar Tutor'.");
            ui->inputMsg->setEnabled(false);
            ui->btnEnviar->setEnabled(false);
            idInterlocutor = 0;
        } else {
            ui->inputMsg->setEnabled(true);
            ui->btnEnviar->setEnabled(true);
            idInterlocutor = usuarioActual->idTutor; // El alumno habla con su tutor
        }
    } 
    else if (usuarioActual->rol == "tutor") {
        ui->btnAsignar->setVisible(false); // Tutor no se asigna a sí mismo
        // SIMPLIFICACION: El tutor elige con qué ID de alumno hablar
        bool ok;
        int idAlu = QInputDialog::getInt(this, "Selección", "Introduce ID del alumno a tutorizar:", 1, 0, 100, 1, &ok);
        if (ok) {
            idInterlocutor = idAlu;
            ui->inputMsg->setEnabled(true);
        } else {
            ui->inputMsg->setEnabled(false);
        }
    }
}

// 3. ENVIAR MENSAJE
void MainWindow::on_btnEnviar_clicked()
{
    if (idInterlocutor == 0) return;
    QString msg = ui->inputMsg->text();
    if (msg.isEmpty()) return;

    int idAlu = (usuarioActual->rol == "alumno") ? usuarioActual->id : idInterlocutor;
    int idTut = (usuarioActual->rol == "tutor") ? usuarioActual->id : idInterlocutor;

    dataManager.guardarMensaje(idAlu, idTut, msg, usuarioActual->nombre);
    
    ui->inputMsg->clear();
    actualizarChatUI();
}

// 4. ACTUALIZAR PANTALLA DE CHAT
void MainWindow::actualizarChatUI() {
    if (idInterlocutor == 0) return;

    int idAlu = (usuarioActual->rol == "alumno") ? usuarioActual->id : idInterlocutor;
    int idTut = (usuarioActual->rol == "tutor") ? usuarioActual->id : idInterlocutor; // En caso de alumno, idInterlocutor es el tutor

    QString historial = dataManager.cargarChat(idAlu, idTut);
    ui->chatDisplay->setText(historial);
}

// 5. ASIGNAR TUTOR AUTOMATICAMENTE
void MainWindow::on_btnAsignar_clicked()
{
    if (usuarioActual->idTutor != 0) {
        QMessageBox::information(this, "Info", "Ya tienes tutor.");
        return;
    }

    if (dataManager.asignarTutor(usuarioActual)) {
        QMessageBox::information(this, "Éxito", "Tutor asignado. Reinicia sesión para ver cambios completos o empieza a chatear.");
        configurarInterfazSegunRol(); // Recargar interfaz
    } else {
        QMessageBox::warning(this, "Error", "No hay tutores disponibles en la base de datos.");
    }
}

// 6. BORRAR CHAT
void MainWindow::on_btnBorrarChat_clicked()
{
    if (idInterlocutor == 0) return;
    
    int idAlu = (usuarioActual->rol == "alumno") ? usuarioActual->id : idInterlocutor;
    int idTut = (usuarioActual->rol == "tutor") ? usuarioActual->id : idInterlocutor;

    dataManager.eliminarChat(idAlu, idTut);
    ui->chatDisplay->clear();
    QMessageBox::information(this, "Info", "Chat eliminado.");
}

// 7. SALIR
void MainWindow::on_btnLogout_clicked()
{
    if (usuarioActual) {
        delete usuarioActual;
        usuarioActual = nullptr;
    }
    ui->inputUser->clear();
    ui->inputPass->clear();
    ui->stackedWidget->setCurrentIndex(0); // Volver al login
}
