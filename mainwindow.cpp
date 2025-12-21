#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <ctime>
#include <iomanip>
#include <sstream>

Usuario* usuarioActual = nullptr;
GestorDatos gestor;

// Constructor
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->stackedWidget->setCurrentIndex(0); 
    idAlumnoChatActual = 0;
}

MainWindow::~MainWindow()
{
    delete ui;
    if (usuarioActual) delete usuarioActual;
}

// --- UTILIDADES ---
string obtenerFechaHora() {
    auto t = std::time(nullptr);
    auto tm = *std::localtime(&t);
    std::ostringstream oss;
    oss << std::put_time(&tm, "[%d/%m/%Y %H:%M]"); 
    return oss.str();
}

// --- LOGIN ---
void MainWindow::on_btnLogin_clicked()
{
    string u = ui->inputUser->text().toStdString();
    string p = ui->inputPass->text().toStdString();

    usuarioActual = gestor.login(u, p);

    if (usuarioActual != nullptr) {
        ui->lblBienvenidaDash->setText("Hola, " + QString::fromStdString(usuarioActual->username));
        ui->stackedWidget->setCurrentIndex(1); // Ir a Dashboard
        ui->inputUser->clear();
        ui->inputPass->clear();

        // Configuración según el Rol
        if (usuarioActual->rol == "tutor") {
            configurarDashboardTutor(); // Rellenar el desplegable
        } else {
            // Si es alumno, ocultamos el selector porque no lo necesita
            ui->cmbAlumnosTutor->hide();
            ui->lblSelectInfo->hide();
        }

    } else {
        QMessageBox::warning(this, "Error", "Credenciales UCO incorrectas.");
    }
}

// --- NUEVA FUNCIÓN: Rellenar el desplegable ---
void MainWindow::configurarDashboardTutor() {
    ui->cmbAlumnosTutor->clear();
    ui->cmbAlumnosTutor->show();
    ui->lblSelectInfo->show();

    // Obtenemos los alumnos del tutor logueado
    vector<AlumnoResumen> misAlumnos = gestor.obtenerAlumnosDeTutor(usuarioActual->id);
    
    if (misAlumnos.empty()) {
        ui->cmbAlumnosTutor->addItem("Sin alumnos asignados", 0);
        ui->cmbAlumnosTutor->setEnabled(false);
    } else {
        ui->cmbAlumnosTutor->setEnabled(true);
        for (auto a : misAlumnos) {
            // Añadimos el Nombre al texto visible y el ID a la data oculta
            ui->cmbAlumnosTutor->addItem(QString::fromStdString(a.nombre), a.id);
        }
    }
}

void MainWindow::on_btnLogout_clicked()
{
    if(usuarioActual) { delete usuarioActual; usuarioActual = nullptr; }
    ui->stackedWidget->setCurrentIndex(0);
}

// --- BOTÓN IR A CHAT ---
void MainWindow::on_btnDashChats_clicked()
{
    // 1. Determinar con quién vamos a hablar
    if (usuarioActual->rol == "tutor") {
        // Leemos el ID guardado en el ComboBox
        int idSeleccionado = ui->cmbAlumnosTutor->currentData().toInt();
        
        if (idSeleccionado == 0) {
            QMessageBox::warning(this, "Aviso", "No hay alumno seleccionado o asignado.");
            return;
        }
        idAlumnoChatActual = idSeleccionado;
        ui->lblChatHeader->setText("Chat con: " + ui->cmbAlumnosTutor->currentText());
    
    } else {
        // Caso Alumno
        if (usuarioActual->idTutor == 0) {
            QMessageBox::warning(this, "Aviso", "Aún no tienes tutor. Ve a Gestión.");
            return;
        }
        string nombreTutor = gestor.obtenerNombrePorId(usuarioActual->idTutor);
        ui->lblChatHeader->setText("Chat con Tutor: " + QString::fromStdString(nombreTutor));
    }

    // 2. Ir a la página y cargar
    ui->stackedWidget->setCurrentIndex(2);
    
    if (usuarioActual->rol == "tutor") 
        cargarChatEnPantalla(idAlumnoChatActual, usuarioActual->id);
    else 
        cargarChatEnPantalla(usuarioActual->id, usuarioActual->idTutor);
}

// --- BOTÓN IR A NOTIFICACIONES ---
void MainWindow::on_btnDashNotif_clicked() 
{ 
    // Si soy tutor, verifico que haya alumno seleccionado para filtrar sus notifs
    if (usuarioActual->rol == "tutor") {
        int idSeleccionado = ui->cmbAlumnosTutor->currentData().toInt();
        if (idSeleccionado == 0) {
            QMessageBox::warning(this, "Aviso", "Selecciona un alumno en el desplegable para ver su historial.");
            return;
        }
        idAlumnoChatActual = idSeleccionado; // Actualizamos contexto
    }
    
    ui->stackedWidget->setCurrentIndex(3); 
    cargarNotificaciones(); 
}

void MainWindow::on_btnDashGestion_clicked()
{
    // Esta función se mantiene igual, solo informa
    if (!usuarioActual) return;
    if (usuarioActual->rol == "tutor") {
         vector<AlumnoResumen> misAlumnos = gestor.obtenerAlumnosDeTutor(usuarioActual->id);
         if (misAlumnos.empty()) QMessageBox::information(this, "Gestión", "No tienes alumnos.");
         else {
             QString lista = "Lista de clase:\n";
             for (auto a : misAlumnos) lista += "- " + QString::fromStdString(a.nombre) + "\n";
             QMessageBox::information(this, "Gestión", lista);
         }
    } else {
        if (usuarioActual->idTutor != 0) {
            string nombreTutor = gestor.obtenerNombrePorId(usuarioActual->idTutor);
            QMessageBox::information(this, "Estado", "Tu tutor es: " + QString::fromStdString(nombreTutor));
        } else {
            if (gestor.asignarTutorAutomatico(usuarioActual)) {
                configurarDashboardTutor(); // Actualizar si cambiara algo
                QMessageBox::information(this, "Éxito", "Tutor asignado.");
            } else {
                QMessageBox::warning(this, "Error", "No hay tutores disponibles.");
            }
        }
    }
}

// --- ENVÍO DE MENSAJES ---
void MainWindow::on_btnEnviarMsg_clicked()
{
    QString textoQt = ui->inputMsgChat->text();
    string mensajeStr = textoQt.toStdString();
    if(textoQt.isEmpty()) return;

    if (!gestor.esMensajeSeguro(mensajeStr)) {
        QMessageBox::critical(this, "Bloqueado", "Mensaje inapropiado.");
        ui->inputMsgChat->clear();
        return; 
    }

    int idAlu, idTut;
    if (usuarioActual->rol == "alumno") {
        idAlu = usuarioActual->id;
        idTut = usuarioActual->idTutor;
    } else {
        // Usamos la variable global actualizada desde el Dashboard
        idAlu = idAlumnoChatActual;
        idTut = usuarioActual->id;
    }

    string fecha = obtenerFechaHora();
    string msgFinal = fecha + " " + usuarioActual->username + ": " + mensajeStr;
    gestor.enviarMensaje(idAlu, idTut, msgFinal);

    ui->inputMsgChat->clear();
    cargarChatEnPantalla(idAlu, idTut);
}

// --- CARGAR CHAT ---
void MainWindow::cargarChatEnPantalla(int idAlumno, int idTutor) {
    ui->txtChatDisplay->clear();
    ChatInfo info = gestor.obtenerChat(idAlumno, idTutor);
    if (info.existe) {
        for (string msg : info.mensajes) ui->txtChatDisplay->append(QString::fromStdString(msg));
    } else {
        ui->txtChatDisplay->setText("<i>No hay mensajes previos con este alumno.</i>");
    }
}

// --- CARGAR NOTIFICACIONES (FILTRADAS POR ALUMNO) ---
void MainWindow::cargarNotificaciones() {
    ui->listNotificaciones->clear();
    
    int idAlu = -1, idTut = -1;
    QString nombreOtro = "";

    if (usuarioActual->rol == "alumno") {
        ui->lblNotifTitle->setText("Historial con tu Tutor");
        if (usuarioActual->idTutor != 0) {
            idAlu = usuarioActual->id;
            idTut = usuarioActual->idTutor;
        }
    } 
    else { // TUTOR
        // Usamos el ID del alumno seleccionado en el Dashboard
        idAlu = idAlumnoChatActual;
        idTut = usuarioActual->id;
        string nombreAlu = gestor.obtenerNombrePorId(idAlu);
        ui->lblNotifTitle->setText("Historial con: " + QString::fromStdString(nombreAlu));
    }

    if (idAlu != -1 && idTut != -1) {
        ChatInfo info = gestor.obtenerChat(idAlu, idTut);
        if (info.existe) {
             for (string msg : info.mensajes) {
                 // Lógica simple para ver quién escribió
                 if (msg.find(usuarioActual->username + ":") != string::npos) 
                     ui->listNotificaciones->addItem("Tú enviaste un mensaje.");
                 else 
                     ui->listNotificaciones->addItem("Recibiste un mensaje.");
             }
        } else {
             ui->listNotificaciones->addItem("No hay actividad reciente con este usuario.");
        }
    }
}

// --- RESTO DE BOTONES ---
void MainWindow::on_btnVolverDash1_clicked() { ui->stackedWidget->setCurrentIndex(1); }
void MainWindow::on_btnVolverDash2_clicked() { ui->stackedWidget->setCurrentIndex(1); }

void MainWindow::on_btnEliminarChat_clicked()
{
    int idAlu = (usuarioActual->rol == "alumno") ? usuarioActual->id : idAlumnoChatActual;
    int idTut = (usuarioActual->rol == "alumno") ? usuarioActual->idTutor : usuarioActual->id;

    if (idAlu != 0 && idTut != 0) {
        auto reply = QMessageBox::question(this, "Eliminar", "¿Borrar historial?", QMessageBox::Yes|QMessageBox::No);
        if (reply == QMessageBox::Yes) {
            gestor.eliminarChat(idAlu, idTut);
            ui->txtChatDisplay->clear();
            QMessageBox::information(this, "Borrado", "Chat eliminado.");
        }
    }
}