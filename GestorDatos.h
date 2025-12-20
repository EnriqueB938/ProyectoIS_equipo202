#ifndef GESTORDATOS_H
#define GESTORDATOS_H

#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <string>
#include <algorithm> // Necesario para transformar a minúsculas

using namespace std;

// Estructuras de datos
struct Usuario {
    int id;
    string username;
    string password;
    string rol; 
    int idTutor; 
};

struct ChatInfo {
    int idChat;
    vector<string> mensajes;
    bool existe;
};

class GestorDatos {
private:
    string archivoUsuarios = "usuarios.txt";
    string archivoChats = "chats.txt";
    
    // LISTA DE PALABRAS PROHIBIDAS
    vector<string> insultos = {"tonto", "idiota", "estupido", "inutil", "bobo", "suspenso", "imbecil"};

public:
    // --- FUNCIÓN DE SEGURIDAD: FILTRO DE INSULTOS ---
    bool esMensajeSeguro(string mensaje) {
        string msgLower = mensaje;
        // Convertir a minúsculas para detectar "TONTO" igual que "tonto"
        transform(msgLower.begin(), msgLower.end(), msgLower.begin(), ::tolower);

        for (const string& malaPalabra : insultos) {
            if (msgLower.find(malaPalabra) != string::npos) {
                return false; // Contiene un insulto
            }
        }
        return true; // Mensaje limpio
    }

    // --- LOGIN ---
    Usuario* login(string user, string pass) {
        ifstream file(archivoUsuarios);
        string linea;
        
        while (getline(file, linea)) {
            stringstream ss(linea);
            string segmento;
            vector<string> datos;

            while(getline(ss, segmento, ',')) {
                datos.push_back(segmento);
            }

            if (datos.size() >= 4 && datos[1] == user && datos[2] == pass) {
                Usuario* u = new Usuario();
                u->id = stoi(datos[0]);
                u->username = datos[1];
                u->password = datos[2];
                u->rol = datos[3];
                u->idTutor = (datos.size() > 4) ? stoi(datos[4]) : 0;
                return u;
            }
        }
        return nullptr;
    }

    // --- ASIGNAR TUTOR ---
    bool asignarTutorAutomatico(Usuario* alumno) {
        if (alumno->rol != "alumno") return false;
        vector<string> lineas;
        ifstream fileIn(archivoUsuarios);
        string linea;
        int idTutorEncontrado = -1;

        while (getline(fileIn, linea)) {
            lineas.push_back(linea);
            if (idTutorEncontrado == -1 && linea.find("tutor") != string::npos) {
                stringstream ss(linea);
                string idStr;
                getline(ss, idStr, ',');
                idTutorEncontrado = stoi(idStr);
            }
        }
        fileIn.close();

        if (idTutorEncontrado != -1) {
            ofstream fileOut(archivoUsuarios);
            for (string& l : lineas) {
                stringstream ss(l);
                string idStr;
                getline(ss, idStr, ',');
                
                if (stoi(idStr) == alumno->id) {
                    fileOut << alumno->id << "," << alumno->username << "," 
                            << alumno->password << ",alumno," << idTutorEncontrado << endl;
                    alumno->idTutor = idTutorEncontrado; 
                } else {
                    fileOut << l << endl;
                }
            }
            fileOut.close();
            return true;
        }
        return false;
    }

    // --- OBTENER CHAT ---
    ChatInfo obtenerChat(int idAlumno, int idTutor) {
        ifstream file(archivoChats);
        string linea;
        ChatInfo chat;
        chat.existe = false;
        chat.idChat = -1;

        while (getline(file, linea)) {
            stringstream ss(linea);
            string segmento;
            vector<string> datos;
            while(getline(ss, segmento, ',')) datos.push_back(segmento);

            if (datos.size() >= 4) {
                int regAlumno = stoi(datos[1]);
                int regTutor = stoi(datos[2]);

                if (regAlumno == idAlumno && regTutor == idTutor) {
                    chat.existe = true;
                    chat.idChat = stoi(datos[0]);
                    
                    stringstream ssMsg(datos[3]);
                    string unMensaje;
                    while(getline(ssMsg, unMensaje, '|')) {
                        chat.mensajes.push_back(unMensaje);
                    }
                    return chat;
                }
            }
        }
        return chat;
    }

    // --- ENVIAR MENSAJE ---
    void enviarMensaje(int idAlumno, int idTutor, string nuevoMensaje) {
        vector<string> lineas;
        ifstream fileIn(archivoChats);
        string linea;
        bool encontrado = false;
        int maxId = 0;

        while (getline(fileIn, linea)) {
            stringstream ss(linea);
            string idStr, aluStr, tutStr;
            getline(ss, idStr, ',');
            getline(ss, aluStr, ',');
            getline(ss, tutStr, ',');
            
            if (!idStr.empty()) maxId = max(maxId, stoi(idStr));

            if (stoi(aluStr) == idAlumno && stoi(tutStr) == idTutor) {
                linea += "|" + nuevoMensaje;
                encontrado = true;
            }
            lineas.push_back(linea);
        }
        fileIn.close();

        if (!encontrado) {
            string nuevaLinea = to_string(maxId + 1) + "," + 
                                to_string(idAlumno) + "," + 
                                to_string(idTutor) + "," + 
                                nuevoMensaje;
            lineas.push_back(nuevaLinea);
        }

        ofstream fileOut(archivoChats);
        for (const string& l : lineas) fileOut << l << endl;
        fileOut.close();
    }

    // --- ELIMINAR CHAT ---
    void eliminarChat(int idAlumno, int idTutor) {
        vector<string> lineas;
        ifstream fileIn(archivoChats);
        string linea;

        while (getline(fileIn, linea)) {
            stringstream ss(linea);
            string trash, aluStr, tutStr;
            getline(ss, trash, ','); 
            getline(ss, aluStr, ',');
            getline(ss, tutStr, ',');

            // Solo guardamos las líneas que NO sean la que queremos borrar
            if (stoi(aluStr) != idAlumno || stoi(tutStr) != idTutor) {
                lineas.push_back(linea);
            }
        }
        fileIn.close();

        ofstream fileOut(archivoChats);
        for (const string& l : lineas) fileOut << l << endl;
        fileOut.close();
    }
};

#endif // GESTORDATOS_H