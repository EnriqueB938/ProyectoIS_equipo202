#ifndef DATAMANAGER_H
#define DATAMANAGER_H

#include <QString>
#include <QFile>
#include <QTextStream>
#include <QVector>
#include <QStringList>
#include <QDateTime> // Para poner fecha a las notificaciones

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
    QString pathNotif = "notificaciones.txt";

    // --- LOGIN (Igual que antes) ---
    Usuario* validarUsuario(QString user, QString pass) {
        QFile file(pathUsuarios);
        if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) return nullptr;
        QTextStream in(&file);
        while (!in.atEnd()) {
            QStringList datos = in.readLine().split(";");
            if (datos.size() >= 4 && datos[1] == user && datos[2] == pass) {
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
        file.close();
        return nullptr;
    }

    // --- GESTIÓN DE NOTIFICACIONES (NUEVO) ---
    void crearNotificacion(int idDestino, QString mensaje) {
        QFile file(pathNotif);
        if (file.open(QIODevice::Append | QIODevice::Text)) {
            QTextStream out(&file);
            QString fecha = QDateTime::currentDateTime().toString("dd/MM HH:mm");
            // Formato: id_destino;mensaje
            out << idDestino << ";[" << fecha << "] " << mensaje << "\n";
            file.close();
        }
    }

    QStringList leerNotificaciones(int idUsuario) {
        QStringList lista;
        QFile file(pathNotif);
        if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
            QTextStream in(&file);
            while (!in.atEnd()) {
                QStringList partes = in.readLine().split(";");
                if (partes.size() >= 2 && partes[0].toInt() == idUsuario) {
                    lista.append(partes[1]);
                }
            }
            file.close();
        }
        return lista;
    }

    // --- ASIGNAR TUTOR (Actualizado con notificaciones) ---
    bool asignarTutor(Usuario* alumno) {
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

        if (idNuevoTutor == -1) return false;

        if (!file.open(QIODevice::WriteOnly | QIODevice::Text | QIODevice::Truncate)) return false;
        QTextStream out(&file);
        for (QString& linea : todasLasLineas) {
            QStringList datos = linea.split(";");
            if (datos[0].toInt() == alumno->id) {
                out << alumno->id << ";" << alumno->nombre << ";" << alumno->pass << ";alumno;" << idNuevoTutor << "\n";
                alumno->idTutor = idNuevoTutor;
            } else {
                out << linea << "\n";
            }
        }
        file.close();

        // Crear notificaciones
        crearNotificacion(alumno->id, "Has sido asignado a un nuevo tutor.");
        crearNotificacion(idNuevoTutor, "Tienes un nuevo alumno asignado: " + alumno->nombre);
        
        return true;
    }

    // --- OBTENER ALUMNOS DE UN TUTOR (NUEVO) ---
    QStringList obtenerMisAlumnos(int idTutor) {
        QStringList listaAlumnos;
        QFile file(pathUsuarios);
        if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
            QTextStream in(&file);
            while (!in.atEnd()) {
                QStringList datos = in.readLine().split(";");
                // Si es alumno y su columna tutor (index 4) coincide con mi ID
                if (datos.size() >= 5 && datos[3] == "alumno" && datos[4].toInt() == idTutor) {
                    listaAlumnos.append(datos[0] + " - " + datos[1]); // "ID - Nombre"
                }
            }
            file.close();
        }
        return listaAlumnos;
    }

    // --- CHATS (Igual, pero añadiendo notificaciones) ---
    QString cargarChat(int idAlumno, int idTutor) {
        QFile file(pathChats);
        if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) return "";
        QTextStream in(&file);
        while (!in.atEnd()) {
            QStringList partes = in.readLine().split(";");
            if (partes.size() >= 3 && partes[0].toInt() == idAlumno && partes[1].toInt() == idTutor) {
                return partes[2].replace("|", "\n");
            }
        }
        return "";
    }

    void guardarMensaje(int idAlumno, int idTutor, QString nuevoMensaje, QString remitente, int idDestinatarioNotif) {
        QStringList lineas;
        bool existe = false;
        QString msgFormat = remitente + ": " + nuevoMensaje;

        QFile file(pathChats);
        if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
            QTextStream in(&file);
            while (!in.atEnd()) lineas.append(in.readLine());
            file.close();
        }

        QFile fileOut(pathChats);
        fileOut.open(QIODevice::WriteOnly | QIODevice::Text);
        QTextStream out(&fileOut);
        for (QString& linea : lineas) {
            QStringList p = linea.split(";");
            if (p.size() >= 2 && p[0].toInt() == idAlumno && p[1].toInt() == idTutor) {
                out << p[0] << ";" << p[1] << ";" << p[2] << "|" << msgFormat << "\n";
                existe = true;
            } else {
                out << linea << "\n";
            }
        }
        if (!existe) out << idAlumno << ";" << idTutor << ";" << msgFormat << "\n";
        fileOut.close();

        // Notificar al otro usuario
        crearNotificacion(idDestinatarioNotif, "Nuevo mensaje de " + remitente);
    }

    void eliminarChat(int idAlumno, int idTutor, int idQuienBorra) {
        QStringList lineas;
        QFile file(pathChats);
        if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
            QTextStream in(&file);
            while (!in.atEnd()) lineas.append(in.readLine());
            file.close();
        }
        QFile fileOut(pathChats);
        fileOut.open(QIODevice::WriteOnly | QIODevice::Text);
        QTextStream out(&fileOut);
        for (QString& linea : lineas) {
            QStringList p = linea.split(";");
            if (!(p[0].toInt() == idAlumno && p[1].toInt() == idTutor)) {
                out << linea << "\n";
            }
        }
        fileOut.close();
        crearNotificacion(idQuienBorra, "Has eliminado un chat.");
    }
};

#endif