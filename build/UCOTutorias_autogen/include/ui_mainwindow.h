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
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QVBoxLayout *verticalLayout_main;
    QStackedWidget *stackedWidget;
    QWidget *pageLogin;
    QVBoxLayout *verticalLayout_login;
    QSpacerItem *verticalSpacer_1;
    QLabel *labelTitle;
    QLineEdit *inputUser;
    QLineEdit *inputPass;
    QPushButton *btnLogin;
    QSpacerItem *verticalSpacer_2;
    QWidget *pageChat;
    QVBoxLayout *verticalLayout_chat;
    QHBoxLayout *horizontalLayout_header;
    QLabel *labelInfo;
    QSpacerItem *horizontalSpacer;
    QPushButton *btnLogout;
    QTextEdit *chatDisplay;
    QHBoxLayout *horizontalLayout_input;
    QLineEdit *inputMsg;
    QPushButton *btnEnviar;
    QHBoxLayout *horizontalLayout_actions;
    QPushButton *btnAsignar;
    QPushButton *btnBorrarChat;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(600, 500);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        verticalLayout_main = new QVBoxLayout(centralwidget);
        verticalLayout_main->setObjectName(QString::fromUtf8("verticalLayout_main"));
        stackedWidget = new QStackedWidget(centralwidget);
        stackedWidget->setObjectName(QString::fromUtf8("stackedWidget"));
        pageLogin = new QWidget();
        pageLogin->setObjectName(QString::fromUtf8("pageLogin"));
        verticalLayout_login = new QVBoxLayout(pageLogin);
        verticalLayout_login->setObjectName(QString::fromUtf8("verticalLayout_login"));
        verticalSpacer_1 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_login->addItem(verticalSpacer_1);

        labelTitle = new QLabel(pageLogin);
        labelTitle->setObjectName(QString::fromUtf8("labelTitle"));
        QFont font;
        font.setPointSize(16);
        font.setBold(true);
        font.setWeight(75);
        labelTitle->setFont(font);
        labelTitle->setAlignment(Qt::AlignCenter);

        verticalLayout_login->addWidget(labelTitle);

        inputUser = new QLineEdit(pageLogin);
        inputUser->setObjectName(QString::fromUtf8("inputUser"));

        verticalLayout_login->addWidget(inputUser);

        inputPass = new QLineEdit(pageLogin);
        inputPass->setObjectName(QString::fromUtf8("inputPass"));
        inputPass->setEchoMode(QLineEdit::Password);

        verticalLayout_login->addWidget(inputPass);

        btnLogin = new QPushButton(pageLogin);
        btnLogin->setObjectName(QString::fromUtf8("btnLogin"));

        verticalLayout_login->addWidget(btnLogin);

        verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_login->addItem(verticalSpacer_2);

        stackedWidget->addWidget(pageLogin);
        pageChat = new QWidget();
        pageChat->setObjectName(QString::fromUtf8("pageChat"));
        verticalLayout_chat = new QVBoxLayout(pageChat);
        verticalLayout_chat->setObjectName(QString::fromUtf8("verticalLayout_chat"));
        horizontalLayout_header = new QHBoxLayout();
        horizontalLayout_header->setObjectName(QString::fromUtf8("horizontalLayout_header"));
        labelInfo = new QLabel(pageChat);
        labelInfo->setObjectName(QString::fromUtf8("labelInfo"));
        QFont font1;
        font1.setBold(true);
        labelInfo->setFont(font1);

        horizontalLayout_header->addWidget(labelInfo);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_header->addItem(horizontalSpacer);

        btnLogout = new QPushButton(pageChat);
        btnLogout->setObjectName(QString::fromUtf8("btnLogout"));

        horizontalLayout_header->addWidget(btnLogout);


        verticalLayout_chat->addLayout(horizontalLayout_header);

        chatDisplay = new QTextEdit(pageChat);
        chatDisplay->setObjectName(QString::fromUtf8("chatDisplay"));
        chatDisplay->setReadOnly(true);

        verticalLayout_chat->addWidget(chatDisplay);

        horizontalLayout_input = new QHBoxLayout();
        horizontalLayout_input->setObjectName(QString::fromUtf8("horizontalLayout_input"));
        inputMsg = new QLineEdit(pageChat);
        inputMsg->setObjectName(QString::fromUtf8("inputMsg"));

        horizontalLayout_input->addWidget(inputMsg);

        btnEnviar = new QPushButton(pageChat);
        btnEnviar->setObjectName(QString::fromUtf8("btnEnviar"));

        horizontalLayout_input->addWidget(btnEnviar);


        verticalLayout_chat->addLayout(horizontalLayout_input);

        horizontalLayout_actions = new QHBoxLayout();
        horizontalLayout_actions->setObjectName(QString::fromUtf8("horizontalLayout_actions"));
        btnAsignar = new QPushButton(pageChat);
        btnAsignar->setObjectName(QString::fromUtf8("btnAsignar"));

        horizontalLayout_actions->addWidget(btnAsignar);

        btnBorrarChat = new QPushButton(pageChat);
        btnBorrarChat->setObjectName(QString::fromUtf8("btnBorrarChat"));

        horizontalLayout_actions->addWidget(btnBorrarChat);


        verticalLayout_chat->addLayout(horizontalLayout_actions);

        stackedWidget->addWidget(pageChat);

        verticalLayout_main->addWidget(stackedWidget);

        MainWindow->setCentralWidget(centralwidget);

        retranslateUi(MainWindow);

        stackedWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "Tutor\303\255a UCO", nullptr));
        labelTitle->setText(QCoreApplication::translate("MainWindow", "Acceso UCO Tutor\303\255as", nullptr));
        inputUser->setPlaceholderText(QCoreApplication::translate("MainWindow", "Usuario (ej: alumno1)", nullptr));
        inputPass->setPlaceholderText(QCoreApplication::translate("MainWindow", "Contrase\303\261a", nullptr));
        btnLogin->setText(QCoreApplication::translate("MainWindow", "Entrar", nullptr));
        labelInfo->setText(QCoreApplication::translate("MainWindow", "Bienvenido", nullptr));
        btnLogout->setText(QCoreApplication::translate("MainWindow", "Cerrar Sesi\303\263n", nullptr));
        inputMsg->setPlaceholderText(QCoreApplication::translate("MainWindow", "Escribe tu mensaje...", nullptr));
        btnEnviar->setText(QCoreApplication::translate("MainWindow", "Enviar", nullptr));
        btnAsignar->setText(QCoreApplication::translate("MainWindow", "Asignar Tutor Autom\303\241tico", nullptr));
        btnBorrarChat->setText(QCoreApplication::translate("MainWindow", "Eliminar Chat Actual", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
