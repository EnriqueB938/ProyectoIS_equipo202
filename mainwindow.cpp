#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include "GestorDatos.h"
#include <iomanip>

Usuario* usuarioActual = nullptr;
GestorDatos gestor;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->stackedWidget->setCurrentIndex(0); 
}

MainWindow::~MainWindow()
{
    delete ui;
    if (usuarioActual) delete usuarioActual;
}

// --- LOGIN ---
void MainWindow::on_btnLogin_clicked()
{
    string u = ui->inputUser->text().toStdString();
    string p = ui->inputPass->text().toStdString();

    usuarioActual = gestor.login(u, p);

    if (usuarioActual != nullptr) {
        ui->lblBienvenidaDash->setText("Hola, " + QString::fromStdString(usuarioActual->username));
        ui->stackedWidget->setCurrentIndex(1); 
        ui->inputUser->clear();
        ui->inputPass->clear();
    } else {
        QMessageBox::warning(this, "Error", "Credenciales UCO incorrectas.");
    }
}

void MainWindow::on_btnLogout_clicked()
{
    if(usuarioActual) { delete usuarioActual; usuarioActual = nullptr; }
    ui->stackedWidget->setCurrentIndex(0);
}

// --- NAVEGACIÓN ---
void MainWindow::on_btnDashChats_clicked()
{
    ui->stackedWidget->setCurrentIndex(2);
    if (usuarioActual && usuarioActual->rol == "alumno" && usuarioActual->idTutor != 0) {
        cargarChatEnPantalla(usuarioActual->id, usuarioActual->idTutor);
    } else {
        ui->txtChatDisplay->setText("Selecciona un chat activo.");
    }
}

// --- AQUÍ ESTÁ EL CAMBIO QUE PEDISTE (GESTIÓN) ---
void MainWindow::on_btnDashGestion_clicked()
{
    if (!usuarioActual) return;

    // CASO 1: ERES TUTOR
    if (usuarioActual->rol == "tutor") {
         // Buscamos qué alumnos tiene asignados este tutor
         vector<string> misAlumnos = gestor.obtenerAlumnosDeTutor(usuarioActual->id);
         
         if (misAlumnos.empty()) {
             QMessageBox::information(this, "Gestión de Alumnos", 
                 "Actualmente no tienes ningún alumno asignado bajo tu tutela.");
         } else {
             QString lista = "Tus alumnos asignados son:\n";
             for (string nombre : misAlumnos) {
                 lista += "- " + QString::fromStdString(nombre) + "\n";
             }
             QMessageBox::information(this, "Gestión de Alumnos", lista);
         }
    } 
    // CASO 2: ERES ALUMNO
    else {
        if (usuarioActual->idTutor != 0) {
            // Ya tiene tutor -> Buscamos el nombre del tutor
            string nombreTutor = gestor.obtenerNombrePorId(usuarioActual->idTutor);
            
            QString msg = "Ya tienes un tutor asignado.\n\n"
                          "Tu tutor es: " + QString::fromStdString(nombreTutor);
            
            QMessageBox::information(this, "Estado de Tutoría", msg);
        } else {
            // No tiene tutor -> Asignamos uno
            if (gestor.asignarTutorAutomatico(usuarioActual)) {
                string nombreNuevoTutor = gestor.obtenerNombrePorId(usuarioActual->idTutor);
                QMessageBox::information(this, "Éxito", 
                    "¡Asignación completada!\nTu nuevo tutor es: " + QString::fromStdString(nombreNuevoTutor));
            } else {
                QMessageBox::warning(this, "Error", "No hay tutores disponibles en el sistema.");
            }
        }
    }
}

void MainWindow::on_btnDashNotif_clicked()
{
    ui->stackedWidget->setCurrentIndex(3);
    cargarNotificaciones();
}

void MainWindow::on_btnVolverDash1_clicked() { ui->stackedWidget->setCurrentIndex(1); }
void MainWindow::on_btnVolverDash2_clicked() { ui->stackedWidget->setCurrentIndex(1); }

// --- CHAT (CON FILTRO DE INSULTOS) ---
string obtenerFechaHora() {
    auto t = std::time(nullptr);
    auto tm = *std::localtime(&t);
    std::ostringstream oss;
    oss << std::put_time(&tm, "[%d/%m/%Y %H:%M]"); 
    return oss.str();
}

void MainWindow::on_btnEnviarMsg_clicked()
{
    QString textoQt = ui->inputMsgChat->text();
    string mensajeStr = textoQt.toStdString();
    if(textoQt.isEmpty()) return;
    if (!gestor.esMensajeSeguro(mensajeStr)) {
        QMessageBox::critical(this, "Mensaje Bloqueado", 
                              "El mensaje contiene lenguaje inapropiado y no será enviado.");
        ui->inputMsgChat->clear();
        return; 
    }

    int idAlu, idTut;
    if (usuarioActual->rol == "alumno") {
        if(usuarioActual->idTutor == 0) {
            QMessageBox::warning(this, "Error", "Sin tutor asignado.");
            return;
        }
        idAlu = usuarioActual->id;
        idTut = usuarioActual->idTutor;
    } else {
        QMessageBox::information(this, "Info", "Selección de alumno pendiente.");
        return; 
    }
    string fecha = obtenerFechaHora();
    string msgFinal = fecha + " " + usuarioActual->username + ": " + mensajeStr;
    gestor.enviarMensaje(idAlu, idTut, msgFinal);
    ui->inputMsgChat->clear();
    cargarChatEnPantalla(idAlu, idTut);
}

void MainWindow::on_btnEliminarChat_clicked()
{
    if (usuarioActual->rol == "alumno" && usuarioActual->idTutor != 0) {
        auto reply = QMessageBox::question(this, "Eliminar", "¿Borrar historial?", QMessageBox::Yes|QMessageBox::No);
        if (reply == QMessageBox::Yes) {
            gestor.eliminarChat(usuarioActual->id, usuarioActual->idTutor);
            ui->txtChatDisplay->clear();
            QMessageBox::information(this, "Borrado", "Chat eliminado.");
        }
    }
}


void MainWindow::cargarChatEnPantalla(int idAlumno, int idTutor) {
    ui->txtChatDisplay->clear();
    ChatInfo info = gestor.obtenerChat(idAlumno, idTutor);
    if (info.existe) {
        for (string msg : info.mensajes) ui->txtChatDisplay->append(QString::fromStdString(msg));
    } else {
        ui->txtChatDisplay->setText("<i>Chat vacío.</i>");
    }
}


void MainWindow::cargarNotificaciones() {
    ui->listNotificaciones->clear();
    
    ui->listNotificaciones->addItem("SISTEMA: Panel de notificaciones actualizado.");
    int idAlu = -1, idTut = -1;

    if (usuarioActual->rol == "alumno" && usuarioActual->idTutor != 0) {
        idAlu = usuarioActual->id;
        idTut = usuarioActual->idTutor;
    } else if (usuarioActual->rol == "tutor") {
        return; 
    }

    if (idAlu != -1 && idTut != -1) {
        ChatInfo info = gestor.obtenerChat(idAlu, idTut);
        
        if (info.existe) {
            for (string msg : info.mensajes) {
                size_t finFecha = msg.find("]");
                string fechaStr = "";
                if (finFecha != string::npos) {
                    fechaStr = msg.substr(0, finFecha + 1); 
                }
                size_t inicioNombre = finFecha + 2; 
                size_t finNombre = msg.find(":", inicioNombre);
                
                if (finNombre != string::npos) {
                    string nombreRemitente = msg.substr(inicioNombre, finNombre - inicioNombre);
                    if (nombreRemitente == usuarioActual->username) {
                        ui->listNotificaciones->addItem(QString::fromStdString(fechaStr) + "Has enviado un mensaje.");
                    } else {
                        ui->listNotificaciones->addItem(QString::fromStdString(fechaStr) + "Nuevo mensaje recibido de " + QString::fromStdString(nombreRemitente));
                    }
                }
            }
        }
    }
}
