#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "GestorDatos.h" 

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    // --- Login ---
    void on_btnLogin_clicked(); // Nombre cambiado (antes btnEntrar)
    void on_btnLogout_clicked(); // Nuevo: Cerrar sesión

    // --- Navegación del Dashboard ---
    void on_btnDashChats_clicked();
    void on_btnDashGestion_clicked(); // (Antes btnAsignarTutor)
    void on_btnDashNotif_clicked();
    void on_btnVolverDash1_clicked(); // Volver desde chat
    void on_btnVolverDash2_clicked(); // Volver desde notificaciones

    // --- Funcionalidad del Chat ---
    void on_btnEnviarMsg_clicked(); // Nombre cambiado (antes btnEnviar)
    void on_btnEliminarChat_clicked();

private:
    Ui::MainWindow *ui;
    
    void cargarChatEnPantalla(int idAlumno, int idTutor);
    void cargarNotificaciones(); // Función nueva para rellenar la lista de notifs
};
#endif // MAINWINDOW_H