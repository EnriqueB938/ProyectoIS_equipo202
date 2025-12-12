#ifndef DATAMANAGER_H
#define DATAMANAGER_H

#include <QString>
#include <QFile>
#include <QTextStream>
#include <QVector>
#include <QStringList>
#include <QDebug>

struct Usuario {
    int id;
    QString nombre;
    QString pass;
    QString rol; // "alumno" o "tutor"
    int idTutor; // 0 si no tiene
};

class DataManager {
public:
    QString pathUsuarios = "usuarios.txt";
    QString pathChats = "chats.txt";

    // --- LOGIN ---
    Usuario* validarUsuario(QString user, QString pass) {
        QFile file(pathUsuarios);
        if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) return nullptr;

        QTextStream in(&file);
        while (!in.atEnd()) {
            QString linea = in.readLine();
            QStringList datos = linea.split(";");
            if (datos.size() >= 4) {
                if (datos[1] == user && datos[2] == pass) {
                    Usuario* u = new Usuario;
                    u->id = datos[0].toInt();
                    u->nombre = datos[1];
                    u->pass = datos[2];
                    u->rol = datos[3];
                    u->idTutor = (datos.size() > 4) ? datos[4].toInt() : 0;
                    file.close();
                    return u;
                }
            }
        }
        file.close();
        return nullptr;
    }

    // --- ASIGNAR TUTOR AUTOMÁTICO ---
    bool asignarTutor(Usuario* alumno) {
        // 1. Buscar un ID de tutor disponible
        int idNuevoTutor = -1;
        QStringList todasLasLineas;
        
        QFile file(pathUsuarios);
        if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) return false;
        QTextStream in(&file);
        
        while (!in.atEnd()) {
            QString linea = in.readLine();
            todasLasLineas.append(linea);
            QStringList datos = linea.split(";");
            if (idNuevoTutor == -1 && datos.size() >= 4 && datos[3] == "tutor") {
                idNuevoTutor = datos[0].toInt();
            }
        }
        file.close();

        if (idNuevoTutor == -1) return false; // No hay tutores en el sistema

        // 2. Reescribir el archivo actualizando al alumno
        if (!file.open(QIODevice::WriteOnly | QIODevice::Text | QIODevice::Truncate)) return false;
        QTextStream out(&file);
        
        for (QString& linea : todasLasLineas) {
            QStringList datos = linea.split(";");
            if (datos[0].toInt() == alumno->id) {
                // Actualizamos la línea del alumno
                out << alumno->id << ";" << alumno->nombre << ";" << alumno->pass << ";alumno;" << idNuevoTutor << "\n";
                alumno->idTutor = idNuevoTutor; // Actualizamos memoria
            } else {
                out << linea << "\n";
            }
        }
        file.close();
        return true;
    }

    // --- LEER CHAT ---
    QString cargarChat(int idAlumno, int idTutor) {
        QFile file(pathChats);
        if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) return "";

        QTextStream in(&file);
        while (!in.atEnd()) {
            QString linea = in.readLine();
            QStringList partes = linea.split(";");
            // Formato: idAlu;idTut;msg1|msg2...
            if (partes.size() >= 3) {
                if (partes[0].toInt() == idAlumno && partes[1].toInt() == idTutor) {
                    // Reemplazamos las barras | por saltos de linea para que se vea bonito
                    return partes[2].replace("|", "\n");
                }
            }
        }
        file.close();
        return ""; // Chat vacío o no existe
    }

    // --- ENVIAR MENSAJE (MODIFICAR/CREAR) ---
    void guardarMensaje(int idAlumno, int idTutor, QString nuevoMensaje, QString remitente) {
        QStringList lineas;
        bool chatEncontrado = false;
        QString mensajeFormateado = remitente + ": " + nuevoMensaje;

        QFile file(pathChats);
        if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
            QTextStream in(&file);
            while (!in.atEnd()) lineas.append(in.readLine());
            file.close();
        }

        QFile fileOut(pathChats);
        if (!fileOut.open(QIODevice::WriteOnly | QIODevice::Text)) return;
        QTextStream out(&fileOut);

        for (QString& linea : lineas) {
            QStringList partes = linea.split(";");
            if (partes.size() >= 2 && partes[0].toInt() == idAlumno && partes[1].toInt() == idTutor) {
                // Chat existe, añadimos mensaje con |
                out << partes[0] << ";" << partes[1] << ";" << partes[2] << "|" << mensajeFormateado << "\n";
                chatEncontrado = true;
            } else {
                out << linea << "\n";
            }
        }

        // Si no existía, creamos la línea nueva
        if (!chatEncontrado) {
            out << idAlumno << ";" << idTutor << ";" << mensajeFormateado << "\n";
        }
        fileOut.close();
    }

    // --- BORRAR CHAT ---
    void eliminarChat(int idAlumno, int idTutor) {
        QStringList lineas;
        QFile file(pathChats);
        if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
            QTextStream in(&file);
            while (!in.atEnd()) lineas.append(in.readLine());
            file.close();
        }

        QFile fileOut(pathChats);
        fileOut.open(QIODevice::WriteOnly | QIODevice::Text); // Truncate borra contenido previo
        QTextStream out(&fileOut);

        for (QString& linea : lineas) {
            QStringList partes = linea.split(";");
            // Si NO es el chat que queremos borrar, lo escribimos
            if (!(partes[0].toInt() == idAlumno && partes[1].toInt() == idTutor)) {
                out << linea << "\n";
            }
        }
        fileOut.close();
    }
};

#endif // DATAMANAGER_H