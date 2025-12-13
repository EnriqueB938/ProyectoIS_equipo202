#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QInputDialog>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->stackedWidget->setCurrentIndex(0); // Empezar en Login
}

MainWindow::~MainWindow()
{
    delete ui;
    if (usuarioActual) delete usuarioActual;
}

// --- LOGIN ---
void MainWindow::on_btnLogin_clicked()
{
    QString u = ui->inputUser->text();
    QString p = ui->inputPass->text();
    usuarioActual = dataManager.validarUsuario(u, p);

    if (usuarioActual) {
        ui->lblBienvenidaDash->setText("Bienvenido al Panel, " + usuarioActual->nombre);
        ui->stackedWidget->setCurrentIndex(1); // Ir al Dashboard
    } else {
        QMessageBox::warning(this, "Error", "Credenciales incorrectas");
    }
}

void MainWindow::on_btnLogout_clicked()
{
    if (usuarioActual) delete usuarioActual;
    usuarioActual = nullptr;
    ui->inputUser->clear();
    ui->inputPass->clear();
    ui->stackedWidget->setCurrentIndex(0);
}

// --- DASHBOARD: BOTÓN CHATS ---
void MainWindow::on_btnDashChats_clicked()
{
    // Lógica para determinar con quién hablar
    idInterlocutor = 0;

    if (usuarioActual->rol == "alumno") {
        if (usuarioActual->idTutor == 0) {
            QMessageBox::information(this, "Aviso", "No tienes tutor asignado. Ve a 'Gestión Tutoría'.");
            return;
        }
        idInterlocutor = usuarioActual->idTutor;
    } 
    else if (usuarioActual->rol == "tutor") {
        bool ok;
        int idInput = QInputDialog::getInt(this, "Selección", "ID del Alumno a contactar:", 0, 0, 100, 1, &ok);
        if (ok && idInput > 0) idInterlocutor = idInput;
        else return;
    }

    // Si tenemos interlocutor, vamos a la pantalla de chat
    ui->stackedWidget->setCurrentIndex(2); // PageChat
    refrescarChat();
}

// --- DASHBOARD: BOTÓN GESTIÓN (ASIGNAR / VER ALUMNOS) ---
void MainWindow::on_btnDashGestion_clicked()
{
    if (usuarioActual->rol == "alumno") {
        // Lógica de Alumno: Asignar Tutor Automático
        if (usuarioActual->idTutor != 0) {
            QMessageBox::information(this, "Info", "Ya tienes un tutor asignado (ID: " + QString::number(usuarioActual->idTutor) + ")");
        } else {
            if (dataManager.asignarTutor(usuarioActual)) {
                QMessageBox::information(this, "Éxito", "¡Tutor asignado automáticamente! Revisa tus notificaciones.");
            } else {
                QMessageBox::warning(this, "Error", "No hay tutores disponibles en el sistema.");
            }
        }
    } 
    else if (usuarioActual->rol == "tutor") {
        // Lógica de Tutor: Ver lista de alumnos
        QStringList misAlumnos = dataManager.obtenerMisAlumnos(usuarioActual->id);
        if (misAlumnos.isEmpty()) {
            QMessageBox::information(this, "Mis Alumnos", "Aún no tienes alumnos asignados.");
        } else {
            // Mostramos una lista simple en un mensaje emergente
            QString listaStr = misAlumnos.join("\n");
            QMessageBox::information(this, "Mis Alumnos Asignados", listaStr);
        }
    }
}

// --- DASHBOARD: BOTÓN NOTIFICACIONES ---
void MainWindow::on_btnDashNotif_clicked()
{
    ui->listNotificaciones->clear();
    QStringList notifs = dataManager.leerNotificaciones(usuarioActual->id);
    ui->listNotificaciones->addItems(notifs);
    ui->stackedWidget->setCurrentIndex(3); // PageNotif
}

// --- BOTONES "VOLVER" ---
void MainWindow::on_btnVolverDash1_clicked() { ui->stackedWidget->setCurrentIndex(1); }
void MainWindow::on_btnVolverDash2_clicked() { ui->stackedWidget->setCurrentIndex(1); }

// --- FUNCIONES DEL CHAT ---
void MainWindow::refrescarChat() {
    if (idInterlocutor == 0) return;
    int idAlu = (usuarioActual->rol == "alumno") ? usuarioActual->id : idInterlocutor;
    int idTut = (usuarioActual->rol == "tutor") ? usuarioActual->id : idInterlocutor;
    
    QString texto = dataManager.cargarChat(idAlu, idTut);
    ui->txtChatDisplay->setText(texto);
}

void MainWindow::on_btnEnviarMsg_clicked()
{
    QString msg = ui->inputMsgChat->text();
    if (msg.isEmpty() || idInterlocutor == 0) return;

    int idAlu = (usuarioActual->rol == "alumno") ? usuarioActual->id : idInterlocutor;
    int idTut = (usuarioActual->rol == "tutor") ? usuarioActual->id : idInterlocutor;

    // Guardar y Notificar al interlocutor
    dataManager.guardarMensaje(idAlu, idTut, msg, usuarioActual->nombre, idInterlocutor);
    
    // Crear notificación local para mí también
    dataManager.crearNotificacion(usuarioActual->id, "Has enviado un mensaje en el chat.");

    ui->inputMsgChat->clear();
    refrescarChat();
}

void MainWindow::on_btnEliminarChat_clicked()
{
    if (idInterlocutor == 0) return;
    int idAlu = (usuarioActual->rol == "alumno") ? usuarioActual->id : idInterlocutor;
    int idTut = (usuarioActual->rol == "tutor") ? usuarioActual->id : idInterlocutor;

    dataManager.eliminarChat(idAlu, idTut, usuarioActual->id);
    ui->txtChatDisplay->clear();
    QMessageBox::information(this, "Info", "Chat eliminado.");
    ui->stackedWidget->setCurrentIndex(1); // Volver al dashboard
}