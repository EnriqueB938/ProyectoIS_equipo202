/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.15.13
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QVBoxLayout *verticalLayout;
    QStackedWidget *stackedWidget;
    QWidget *pageLogin;
    QVBoxLayout *layoutLogin;
    QSpacerItem *vspacer1;
    QLabel *lblTitleLogin;
    QLineEdit *inputUser;
    QLineEdit *inputPass;
    QPushButton *btnLogin;
    QSpacerItem *vspacer2;
    QWidget *pageDashboard;
    QVBoxLayout *layoutDash;
    QLabel *lblBienvenidaDash;
    QSpacerItem *vspacer3;
    QPushButton *btnDashChats;
    QPushButton *btnDashGestion;
    QPushButton *btnDashNotif;
    QSpacerItem *vspacer4;
    QPushButton *btnLogout;
    QWidget *pageChats;
    QVBoxLayout *layoutChatPage;
    QLabel *lblChatHeader;
    QTextEdit *txtChatDisplay;
    QHBoxLayout *layoutInputChat;
    QLineEdit *inputMsgChat;
    QPushButton *btnEnviarMsg;
    QHBoxLayout *layoutChatTools;
    QPushButton *btnEliminarChat;
    QPushButton *btnVolverDash1;
    QWidget *pageNotif;
    QVBoxLayout *layoutNotif;
    QLabel *lblNotifTitle;
    QListWidget *listNotificaciones;
    QPushButton *btnVolverDash2;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(700, 550);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        verticalLayout = new QVBoxLayout(centralwidget);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        stackedWidget = new QStackedWidget(centralwidget);
        stackedWidget->setObjectName(QString::fromUtf8("stackedWidget"));
        pageLogin = new QWidget();
        pageLogin->setObjectName(QString::fromUtf8("pageLogin"));
        layoutLogin = new QVBoxLayout(pageLogin);
        layoutLogin->setObjectName(QString::fromUtf8("layoutLogin"));
        vspacer1 = new QSpacerItem(0, 0, QSizePolicy::Minimum, QSizePolicy::Expanding);

        layoutLogin->addItem(vspacer1);

        lblTitleLogin = new QLabel(pageLogin);
        lblTitleLogin->setObjectName(QString::fromUtf8("lblTitleLogin"));
        lblTitleLogin->setAlignment(Qt::AlignCenter);
        QFont font;
        font.setPointSize(18);
        font.setBold(true);
        lblTitleLogin->setFont(font);

        layoutLogin->addWidget(lblTitleLogin);

        inputUser = new QLineEdit(pageLogin);
        inputUser->setObjectName(QString::fromUtf8("inputUser"));

        layoutLogin->addWidget(inputUser);

        inputPass = new QLineEdit(pageLogin);
        inputPass->setObjectName(QString::fromUtf8("inputPass"));
        inputPass->setEchoMode(QLineEdit::Password);

        layoutLogin->addWidget(inputPass);

        btnLogin = new QPushButton(pageLogin);
        btnLogin->setObjectName(QString::fromUtf8("btnLogin"));

        layoutLogin->addWidget(btnLogin);

        vspacer2 = new QSpacerItem(0, 0, QSizePolicy::Minimum, QSizePolicy::Expanding);

        layoutLogin->addItem(vspacer2);

        stackedWidget->addWidget(pageLogin);
        pageDashboard = new QWidget();
        pageDashboard->setObjectName(QString::fromUtf8("pageDashboard"));
        layoutDash = new QVBoxLayout(pageDashboard);
        layoutDash->setObjectName(QString::fromUtf8("layoutDash"));
        lblBienvenidaDash = new QLabel(pageDashboard);
        lblBienvenidaDash->setObjectName(QString::fromUtf8("lblBienvenidaDash"));
        QFont font1;
        font1.setPointSize(16);
        font1.setBold(true);
        lblBienvenidaDash->setFont(font1);
        lblBienvenidaDash->setAlignment(Qt::AlignCenter);

        layoutDash->addWidget(lblBienvenidaDash);

        vspacer3 = new QSpacerItem(0, 0, QSizePolicy::Minimum, QSizePolicy::Expanding);

        layoutDash->addItem(vspacer3);

        btnDashChats = new QPushButton(pageDashboard);
        btnDashChats->setObjectName(QString::fromUtf8("btnDashChats"));
        btnDashChats->setMinimumHeight(70);
        QFont font2;
        font2.setPointSize(12);
        font2.setBold(true);
        btnDashChats->setFont(font2);

        layoutDash->addWidget(btnDashChats);

        btnDashGestion = new QPushButton(pageDashboard);
        btnDashGestion->setObjectName(QString::fromUtf8("btnDashGestion"));
        btnDashGestion->setMinimumHeight(70);
        btnDashGestion->setFont(font2);

        layoutDash->addWidget(btnDashGestion);

        btnDashNotif = new QPushButton(pageDashboard);
        btnDashNotif->setObjectName(QString::fromUtf8("btnDashNotif"));
        btnDashNotif->setMinimumHeight(70);
        btnDashNotif->setFont(font2);

        layoutDash->addWidget(btnDashNotif);

        vspacer4 = new QSpacerItem(0, 0, QSizePolicy::Minimum, QSizePolicy::Expanding);

        layoutDash->addItem(vspacer4);

        btnLogout = new QPushButton(pageDashboard);
        btnLogout->setObjectName(QString::fromUtf8("btnLogout"));

        layoutDash->addWidget(btnLogout);

        stackedWidget->addWidget(pageDashboard);
        pageChats = new QWidget();
        pageChats->setObjectName(QString::fromUtf8("pageChats"));
        layoutChatPage = new QVBoxLayout(pageChats);
        layoutChatPage->setObjectName(QString::fromUtf8("layoutChatPage"));
        lblChatHeader = new QLabel(pageChats);
        lblChatHeader->setObjectName(QString::fromUtf8("lblChatHeader"));
        QFont font3;
        font3.setPointSize(14);
        font3.setBold(true);
        lblChatHeader->setFont(font3);
        lblChatHeader->setAlignment(Qt::AlignCenter);

        layoutChatPage->addWidget(lblChatHeader);

        txtChatDisplay = new QTextEdit(pageChats);
        txtChatDisplay->setObjectName(QString::fromUtf8("txtChatDisplay"));
        txtChatDisplay->setReadOnly(true);

        layoutChatPage->addWidget(txtChatDisplay);

        layoutInputChat = new QHBoxLayout();
        layoutInputChat->setObjectName(QString::fromUtf8("layoutInputChat"));
        inputMsgChat = new QLineEdit(pageChats);
        inputMsgChat->setObjectName(QString::fromUtf8("inputMsgChat"));

        layoutInputChat->addWidget(inputMsgChat);

        btnEnviarMsg = new QPushButton(pageChats);
        btnEnviarMsg->setObjectName(QString::fromUtf8("btnEnviarMsg"));

        layoutInputChat->addWidget(btnEnviarMsg);


        layoutChatPage->addLayout(layoutInputChat);

        layoutChatTools = new QHBoxLayout();
        layoutChatTools->setObjectName(QString::fromUtf8("layoutChatTools"));
        btnEliminarChat = new QPushButton(pageChats);
        btnEliminarChat->setObjectName(QString::fromUtf8("btnEliminarChat"));

        layoutChatTools->addWidget(btnEliminarChat);

        btnVolverDash1 = new QPushButton(pageChats);
        btnVolverDash1->setObjectName(QString::fromUtf8("btnVolverDash1"));

        layoutChatTools->addWidget(btnVolverDash1);


        layoutChatPage->addLayout(layoutChatTools);

        stackedWidget->addWidget(pageChats);
        pageNotif = new QWidget();
        pageNotif->setObjectName(QString::fromUtf8("pageNotif"));
        layoutNotif = new QVBoxLayout(pageNotif);
        layoutNotif->setObjectName(QString::fromUtf8("layoutNotif"));
        lblNotifTitle = new QLabel(pageNotif);
        lblNotifTitle->setObjectName(QString::fromUtf8("lblNotifTitle"));
        lblNotifTitle->setFont(font2);
        lblNotifTitle->setAlignment(Qt::AlignCenter);

        layoutNotif->addWidget(lblNotifTitle);

        listNotificaciones = new QListWidget(pageNotif);
        listNotificaciones->setObjectName(QString::fromUtf8("listNotificaciones"));

        layoutNotif->addWidget(listNotificaciones);

        btnVolverDash2 = new QPushButton(pageNotif);
        btnVolverDash2->setObjectName(QString::fromUtf8("btnVolverDash2"));

        layoutNotif->addWidget(btnVolverDash2);

        stackedWidget->addWidget(pageNotif);

        verticalLayout->addWidget(stackedWidget);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 700, 21));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        stackedWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "Tutor\303\255a UCO Pro", nullptr));
        MainWindow->setStyleSheet(QCoreApplication::translate("MainWindow", "QMainWindow { background-color: #F0F0F0; }", nullptr));
        lblTitleLogin->setText(QCoreApplication::translate("MainWindow", "ACCESO UCO", nullptr));
        lblTitleLogin->setStyleSheet(QCoreApplication::translate("MainWindow", "color: #333333;", nullptr));
        inputUser->setPlaceholderText(QCoreApplication::translate("MainWindow", "Usuario", nullptr));
        inputUser->setStyleSheet(QCoreApplication::translate("MainWindow", "padding: 8px; border-radius: 5px; border: 1px solid #ccc; background: white;", nullptr));
        inputPass->setPlaceholderText(QCoreApplication::translate("MainWindow", "Contrase\303\261a", nullptr));
        inputPass->setStyleSheet(QCoreApplication::translate("MainWindow", "padding: 8px; border-radius: 5px; border: 1px solid #ccc; background: white;", nullptr));
        btnLogin->setText(QCoreApplication::translate("MainWindow", "Iniciar Sesi\303\263n", nullptr));
        btnLogin->setStyleSheet(QCoreApplication::translate("MainWindow", "QPushButton { background-color: #2E86C1; color: white; border-radius: 5px; padding: 10px; font-weight: bold; } QPushButton:hover { background-color: #2874A6; }", nullptr));
        lblBienvenidaDash->setText(QCoreApplication::translate("MainWindow", "Hola, Usuario", nullptr));
        lblBienvenidaDash->setStyleSheet(QCoreApplication::translate("MainWindow", "color: #2C3E50; margin-bottom: 20px;", nullptr));
        btnDashChats->setText(QCoreApplication::translate("MainWindow", "CHATS", nullptr));
        btnDashChats->setStyleSheet(QCoreApplication::translate("MainWindow", "QPushButton { background-color: #85C1E9; color: white; border-radius: 10px; border: 2px solid #5DADE2; } QPushButton:hover { background-color: #5DADE2; }", nullptr));
        btnDashGestion->setText(QCoreApplication::translate("MainWindow", "ASIGNACI\303\223N AUTOM\303\201TICA", nullptr));
        btnDashGestion->setStyleSheet(QCoreApplication::translate("MainWindow", "QPushButton { background-color: #85C1E9; color: white; border-radius: 10px; border: 2px solid #5DADE2; } QPushButton:hover { background-color: #5DADE2; }", nullptr));
        btnDashNotif->setText(QCoreApplication::translate("MainWindow", "NOTIFICACIONES", nullptr));
        btnDashNotif->setStyleSheet(QCoreApplication::translate("MainWindow", "QPushButton { background-color: #85C1E9; color: white; border-radius: 10px; border: 2px solid #5DADE2; } QPushButton:hover { background-color: #5DADE2; }", nullptr));
        btnLogout->setText(QCoreApplication::translate("MainWindow", "Cerrar Sesi\303\263n", nullptr));
        btnLogout->setStyleSheet(QCoreApplication::translate("MainWindow", "background-color: #E74C3C; color: white; border-radius: 5px; padding: 5px;", nullptr));
        lblChatHeader->setText(QCoreApplication::translate("MainWindow", "Sala de Chat", nullptr));
        txtChatDisplay->setStyleSheet(QCoreApplication::translate("MainWindow", "background-color: white; border-radius: 5px; padding: 5px; font: 11pt \"Segoe UI\";", nullptr));
        inputMsgChat->setPlaceholderText(QCoreApplication::translate("MainWindow", "Escribe aqu\303\255...", nullptr));
        inputMsgChat->setStyleSheet(QCoreApplication::translate("MainWindow", "padding: 5px; background: white;", nullptr));
        btnEnviarMsg->setText(QCoreApplication::translate("MainWindow", "Enviar", nullptr));
        btnEliminarChat->setText(QCoreApplication::translate("MainWindow", "Eliminar este chat", nullptr));
        btnVolverDash1->setText(QCoreApplication::translate("MainWindow", "Volver al Panel", nullptr));
        lblNotifTitle->setText(QCoreApplication::translate("MainWindow", "Tus Notificaciones", nullptr));
        listNotificaciones->setStyleSheet(QCoreApplication::translate("MainWindow", "background-color: white; border-radius: 5px; padding: 5px;", nullptr));
        btnVolverDash2->setText(QCoreApplication::translate("MainWindow", "Volver al Panel", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
