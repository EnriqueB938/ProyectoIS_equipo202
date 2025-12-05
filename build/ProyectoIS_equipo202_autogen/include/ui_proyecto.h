/********************************************************************************
** Form generated from reading UI file 'proyecto.ui'
**
** Created by: Qt User Interface Compiler version 5.15.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PROYECTO_H
#define UI_PROYECTO_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFrame>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ProyectoWindow
{
public:
    QFrame *frame;
    QLabel *label;
    QLineEdit *inputNombre;
    QPushButton *botonSaludar;

    void setupUi(QWidget *ProyectoWindow)
    {
        if (ProyectoWindow->objectName().isEmpty())
            ProyectoWindow->setObjectName(QString::fromUtf8("ProyectoWindow"));
        ProyectoWindow->resize(400, 250);
        ProyectoWindow->setStyleSheet(QString::fromUtf8("\n"
"     QWidget {\n"
"        background-color: #f2f2f2;\n"
"        font-family: \"Segoe UI\";\n"
"        font-size: 12pt;\n"
"     }\n"
"     QFrame {\n"
"        background-color: white;\n"
"        border-radius: 12px;\n"
"        border: 1px solid #cccccc;\n"
"     }\n"
"     QPushButton {\n"
"        background-color: #4a90e2;\n"
"        color: white;\n"
"        padding: 8px;\n"
"        border-radius: 6px;\n"
"     }\n"
"     QPushButton:hover {\n"
"        background-color: #357ABD;\n"
"     }\n"
"   "));
        frame = new QFrame(ProyectoWindow);
        frame->setObjectName(QString::fromUtf8("frame"));
        frame->setGeometry(QRect(30, 30, 340, 180));
        label = new QLabel(frame);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(20, 20, 300, 30));
        inputNombre = new QLineEdit(frame);
        inputNombre->setObjectName(QString::fromUtf8("inputNombre"));
        inputNombre->setGeometry(QRect(20, 60, 300, 30));
        botonSaludar = new QPushButton(frame);
        botonSaludar->setObjectName(QString::fromUtf8("botonSaludar"));
        botonSaludar->setGeometry(QRect(90, 110, 160, 40));

        retranslateUi(ProyectoWindow);

        QMetaObject::connectSlotsByName(ProyectoWindow);
    } // setupUi

    void retranslateUi(QWidget *ProyectoWindow)
    {
        ProyectoWindow->setWindowTitle(QCoreApplication::translate("ProyectoWindow", "Proyecto IS - Interfaz B\303\241sica", nullptr));
        label->setText(QCoreApplication::translate("ProyectoWindow", "Introduce tu nombre:", nullptr));
        botonSaludar->setText(QCoreApplication::translate("ProyectoWindow", "Saludar", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ProyectoWindow: public Ui_ProyectoWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PROYECTO_H
