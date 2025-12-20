#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include "GestorDatos.h"

// Variables globales
Usuario* usuarioActual = nullptr;
GestorDatos gestor;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    
    // Iniciar en la página de Login (índice 0)
    ui->stackedWidget->setCurrentIndex(0); 
}

MainWindow::~MainWindow()
{
    delete ui;
    if (usuarioActual) delete usuarioActual;
}

// =========================================================
//  LÓGICA DE ACCESO (LOGIN & LOGOUT)
// =========================================================

void MainWindow::on_btnLogin_clicked()
{
    // NOMBRES NUEVOS EN EL XML: inputUser, inputPass
    string u = ui->inputUser->text().toStdString();
    string p = ui->inputPass->text().toStdString();

    usuarioActual = gestor.login(u, p);

    if (usuarioActual != nullptr) {
        // Login exitoso -> Vamos al DASHBOARD (Página 1)
        ui->lblBienvenidaDash->setText("Hola, " + QString::fromStdString(usuarioActual->username));
        ui->stackedWidget->setCurrentIndex(1); 
        
        // Limpiamos campos de login por seguridad
        ui->inputUser->clear();
        ui->inputPass->clear();

    } else {
        QMessageBox::warning(this, "Error de Acceso", "Credenciales UCO incorrectas.");
    }
}

void MainWindow::on_btnLogout_clicked()
{
    if(usuarioActual) {
        delete usuarioActual;
        usuarioActual = nullptr;
    }
    // Volver al Login
    ui->stackedWidget->setCurrentIndex(0);
}

// =========================================================
//  NAVEGACIÓN DEL DASHBOARD
// =========================================================

void MainWindow::on_btnDashChats_clicked()
{
    // Ir a página de Chats (Índice 2)
    ui->stackedWidget->setCurrentIndex(2);
    
    // Cargar lógica del chat automáticamente si procede
    if (usuarioActual && usuarioActual->rol == "alumno" && usuarioActual->idTutor != 0) {
        cargarChatEnPantalla(usuarioActual->id, usuarioActual->idTutor);
    } else if (usuarioActual && usuarioActual->rol == "tutor") {
        ui->txtChatDisplay->setText("Seleccione un alumno (Función pendiente de implementación).");
    } else {
        ui->txtChatDisplay->setText("Aún no tienes tutor asignado.");
    }
}

void MainWindow::on_btnDashGestion_clicked()
{
    // Esta es la lógica antigua de "Asignar Tutor"
    if (!usuarioActual) return;

    if (usuarioActual->rol == "tutor") {
         QMessageBox::information(this, "Información", "Como tutor, gestionas a tus alumnos aquí.");
         // Aquí podrías mostrar una lista de alumnos
    } 
    else {
        // Es alumno
        if (usuarioActual->idTutor != 0) {
            QMessageBox::information(this, "Aviso", "Ya tienes un tutor asignado.");
        } else {
            if (gestor.asignarTutorAutomatico(usuarioActual)) {
                QMessageBox::information(this, "Éxito", "¡Se te ha asignado un tutor automáticamente!");
            } else {
                QMessageBox::warning(this, "Error", "No hay tutores disponibles en el sistema.");
            }
        }
    }
}

void MainWindow::on_btnDashNotif_clicked()
{
    // Ir a página de Notificaciones (Índice 3)
    ui->stackedWidget->setCurrentIndex(3);
    cargarNotificaciones();
}

// Botones para "Volver atrás"
void MainWindow::on_btnVolverDash1_clicked() { ui->stackedWidget->setCurrentIndex(1); }
void MainWindow::on_btnVolverDash2_clicked() { ui->stackedWidget->setCurrentIndex(1); }


// =========================================================
//  LÓGICA DEL CHAT
// =========================================================

void MainWindow::on_btnEnviarMsg_clicked()
{
    // NOMBRE NUEVO EN EL XML: inputMsgChat
    QString textoQt = ui->inputMsgChat->text();
    string mensajeStr = textoQt.toStdString();

    if(textoQt.isEmpty()) return;

    // 1. FILTRO DE INSULTOS
    if (!gestor.esMensajeSeguro(mensajeStr)) {
        QMessageBox::critical(this, "Mensaje Bloqueado", 
                              "El mensaje contiene lenguaje inapropiado y no será enviado.");
        ui->inputMsgChat->clear();
        return; 
    }

    // 2. Verificar datos
    int idAlu, idTut;
    if (usuarioActual->rol == "alumno") {
        if(usuarioActual->idTutor == 0) {
            QMessageBox::warning(this, "Error", "Sin tutor asignado.");
            return;
        }
        idAlu = usuarioActual->id;
        idTut = usuarioActual->idTutor;
    } else {
        // Caso Tutor (simplificado)
        QMessageBox::information(this, "Info", "Selección de alumno pendiente.");
        return; 
    }

    // 3. Enviar
    string msgFinal = usuarioActual->username + ": " + mensajeStr;
    gestor.enviarMensaje(idAlu, idTut, msgFinal);

    ui->inputMsgChat->clear();
    cargarChatEnPantalla(idAlu, idTut);
}

void MainWindow::on_btnEliminarChat_clicked()
{
    if (usuarioActual->rol == "alumno" && usuarioActual->idTutor != 0) {
        auto reply = QMessageBox::question(this, "Eliminar Chat", 
                                      "¿Borrar historial completo?",
                                      QMessageBox::Yes|QMessageBox::No);
        if (reply == QMessageBox::Yes) {
            gestor.eliminarChat(usuarioActual->id, usuarioActual->idTutor);
            ui->txtChatDisplay->clear();
            QMessageBox::information(this, "Borrado", "Chat eliminado.");
        }
    }
}

// =========================================================
//  FUNCIONES AUXILIARES
// =========================================================

void MainWindow::cargarChatEnPantalla(int idAlumno, int idTutor) {
    ui->txtChatDisplay->clear();
    ChatInfo info = gestor.obtenerChat(idAlumno, idTutor);

    if (info.existe) {
        for (string msg : info.mensajes) {
            ui->txtChatDisplay->append(QString::fromStdString(msg));
        }
    } else {
        ui->txtChatDisplay->setText("<i>Chat vacío.</i>");
    }
}

void MainWindow::cargarNotificaciones() {
    ui->listNotificaciones->clear();
    // Ejemplo de notificaciones estáticas (RF11)
    ui->listNotificaciones->addItem("Bienvenido al sistema UCO Tutorías.");
    if(usuarioActual->idTutor != 0) {
        ui->listNotificaciones->addItem("Tienes un tutor asignado correctamente.");
    } else {
        ui->listNotificaciones->addItem("Recuerda solicitar la asignación de tutor.");
    }
}