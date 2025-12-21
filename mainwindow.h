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
    void on_btnLogin_clicked();
    void on_btnLogout_clicked();

    void on_btnDashChats_clicked();
    void on_btnDashGestion_clicked();
    void on_btnDashNotif_clicked(); // Ver notificaciones
    
    void on_btnVolverDash1_clicked();
    void on_btnVolverDash2_clicked();

    void on_btnEnviarMsg_clicked();
    void on_btnEliminarChat_clicked();

private:
    Ui::MainWindow *ui;
    
    // Esta variable ahora se controla desde el ComboBox del Dashboard
    int idAlumnoChatActual; 
    
    void cargarChatEnPantalla(int idAlumno, int idTutor);
    void cargarNotificaciones();
    void configurarDashboardTutor(); // Nueva función auxiliar
};
#endif // MAINWINDOW_H