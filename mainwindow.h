#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "DataManager.cc"

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
    // Login
    void on_btnLogin_clicked();
    void on_btnLogout_clicked();

    // Dashboard navegación
    void on_btnDashChats_clicked();
    void on_btnDashGestion_clicked();
    void on_btnDashNotif_clicked();

    // Botones de volver
    void on_btnVolverDash1_clicked();
    void on_btnVolverDash2_clicked();

    // Funciones de Chat
    void on_btnEnviarMsg_clicked();
    void on_btnEliminarChat_clicked();

private:
    Ui::MainWindow *ui;
    DataManager dataManager;
    Usuario* usuarioActual = nullptr;
    int idInterlocutor = 0; // Con quién estoy hablando

    void cargarInterfazChat();
    void refrescarChat();
};
#endif // MAINWINDOW_H