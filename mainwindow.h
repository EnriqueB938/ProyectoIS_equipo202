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
    void on_btnLogin_clicked();
    void on_btnEnviar_clicked();
    void on_btnAsignar_clicked();
    void on_btnBorrarChat_clicked();
    void on_btnLogout_clicked();

private:
    Ui::MainWindow *ui;
    DataManager dataManager;
    Usuario* usuarioActual = nullptr;
    
    // Auxiliar para saber con quién habla el tutor
    // (Para simplificar, el tutor habla con el alumno ID 1 por defecto o el que definamos)
    int idInterlocutor = 0; 

    void actualizarChatUI();
    void configurarInterfazSegunRol();
};
#endif // MAINWINDOW_H