/******************************************************************************

Welcome to GDB Online.
GDB online is an online compiler and debugger tool for C, C++, Python, Java, PHP, Ruby, Perl,
C#, OCaml, VB, Swift, Pascal, Fortran, Haskell, Objective-C, Assembly, HTML, CSS, JS, SQLite, Prolog.
Code, Compile, Run and Debug online from anywhere in world.

*******************************************************************************/
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <fstream>
#include <unordered_map>

using namespace std;

// Clase para representar un usuario
class Usuario {
public:
    string nombre;
    int puntos;
    vector<string> recompensas;

    Usuario(string nombre) : nombre(nombre), puntos(0) {}

    void agregarPuntos(int puntosGanados) {
        puntos += puntosGanados;
    }

    void agregarRecompensa(string recompensa) {
        recompensas.push_back(recompensa);
    }

    void mostrarInformacion() {
        cout << "Usuario: " << nombre << ", Puntos: " << puntos << endl;
        cout << "Recompensas: ";
        for (const auto& recompensa : recompensas) {
            cout << recompensa << " ";
        }
        cout << endl;
    }

    // Función para guardar un usuario en un archivo
    void guardarEnArchivo(ofstream& archivo) {
        archivo << nombre << "\n" << puntos << "\n";
        archivo << recompensas.size() << "\n";
        for (const auto& recompensa : recompensas) {
            archivo << recompensa << "\n";
        }
    }

    // Función para cargar un usuario desde un archivo
    void cargarDesdeArchivo(ifstream& archivo) {
        getline(archivo, nombre);
        archivo >> puntos;
        archivo.ignore();
        int numeroRecompensas;
        archivo >> numeroRecompensas;
        archivo.ignore();
        recompensas.clear();
        for (int i = 0; i < numeroRecompensas; ++i) {
            string recompensa;
            getline(archivo, recompensa);
            recompensas.push_back(recompensa);
        }
    }
};

// Clase para representar una tarea pendiente
class Tarea {
public:
    string codigo;
    string descripcion;
    int puntosRecompensa;
    string recompensa;
    string tema;
    string usuario; // Usuario asignado a la tarea

    Tarea(string codigo, string descripcion, int puntosRecompensa, string recompensa, string tema, string usuario)
        : codigo(codigo), descripcion(descripcion), puntosRecompensa(puntosRecompensa), recompensa(recompensa), tema(tema), usuario(usuario) {}

    // Función para guardar una tarea en un archivo
    void guardarEnArchivo(ofstream& archivo) {
        archivo << codigo << "\n" << descripcion << "\n" << puntosRecompensa << "\n" << recompensa << "\n" << tema << "\n" << usuario << "\n";
    }

    // Función para cargar una tarea desde un archivo
    void cargarDesdeArchivo(ifstream& archivo) {
        getline(archivo, codigo);
        getline(archivo, descripcion);
        archivo >> puntosRecompensa;
        archivo.ignore();
        getline(archivo, recompensa);
        getline(archivo, tema);
        getline(archivo, usuario);
    }

    void mostrarTarea() {
        cout << "Codigo: " << codigo << ", Tarea: " << descripcion << ", Puntos: " << puntosRecompensa << ", Recompensa: " << recompensa << ", Tema: " << tema << ", Usuario: " << usuario << endl;
    }
};

// Clase para administrar la plataforma
class Plataforma {
private:
    vector<Usuario> usuarios;
    vector<Tarea> tareas;

    // Función para generar un código único para la tarea
    string generarCodigoTarea() {
        static int numero = 1;
        string codigo = "TA" + to_string(numero);
        numero++;
        return codigo;
    }

    // Función para buscar o registrar un usuario
    Usuario& buscarORegistrarUsuario(const string& nombre) {
        auto it = find_if(usuarios.begin(), usuarios.end(), [&](Usuario& u) { return u.nombre == nombre; });
        if (it == usuarios.end()) {
            // Si el usuario no existe, se crea y se agrega
            usuarios.push_back(Usuario(nombre));
            it = find_if(usuarios.begin(), usuarios.end(), [&](Usuario& u) { return u.nombre == nombre; });
        }
        return *it;
    }

public:
    void agregarTarea(const string& descripcion, int puntosRecompensa, const string& recompensa, const string& tema, const string& nombreUsuario) {
        Usuario& usuario = buscarORegistrarUsuario(nombreUsuario);
        string codigo = generarCodigoTarea();
        tareas.push_back(Tarea(codigo, descripcion, puntosRecompensa, recompensa, tema, nombreUsuario));
        cout << "Tarea registrada con el código: " << codigo << " para el usuario: " << nombreUsuario << endl;
    }

    void completarTarea(const string& codigoTarea) {
        auto itTarea = find_if(tareas.begin(), tareas.end(), [&](Tarea& t) { return t.codigo == codigoTarea; });

        if (itTarea != tareas.end()) {
            Usuario& usuario = buscarORegistrarUsuario(itTarea->usuario);
            usuario.agregarPuntos(itTarea->puntosRecompensa);
            usuario.agregarRecompensa(itTarea->recompensa);
            cout << "Tarea completada por " << usuario.nombre << ":D! Ha ganado " << itTarea->puntosRecompensa << " puntos y la recompensa: " << itTarea->recompensa << endl;
            tareas.erase(itTarea); // Eliminar tarea completada
        } else {
            cout << "Tarea no encontrada." << endl;
        }
    }

    void mostrarInformacionUsuarios() {
        cout << "Información de Usuarios:" << endl;
        for (auto& usuario : usuarios) {
            usuario.mostrarInformacion();
        }
    }

    void mostrarTareasPendientes() {
        cout << "Tareas Pendientes:" << endl;
        for (auto& tarea : tareas) {
            tarea.mostrarTarea();
        }
    }

    // Función para guardar toda la plataforma en un archivo
    void guardarEnArchivo(const string& nombreArchivo) {
        ofstream archivo(nombreArchivo);
        if (archivo.is_open()) {
            archivo << usuarios.size() << "\n";
            for (auto& usuario : usuarios) {
                usuario.guardarEnArchivo(archivo);
            }

            archivo << tareas.size() << "\n";
            for (auto& tarea : tareas) {
                tarea.guardarEnArchivo(archivo);
            }

            archivo.close();
            cout << "Datos guardados correctamente en " << nombreArchivo << endl;
        } else {
            cout << "Error al abrir el archivo para guardar datos." << endl;
        }
    }

    // Función para cargar toda la plataforma desde un archivo
    void cargarDesdeArchivo(const string& nombreArchivo) {
        ifstream archivo(nombreArchivo);
        if (archivo.is_open()) {
            int numeroUsuarios, numeroTareas;

            archivo >> numeroUsuarios;
            archivo.ignore();
            usuarios.clear();
            for (int i = 0; i < numeroUsuarios; ++i) {
                Usuario usuario("");
                usuario.cargarDesdeArchivo(archivo);
                usuarios.push_back(usuario);
            }

            archivo >> numeroTareas;
            archivo.ignore();
            tareas.clear();
            for (int i = 0; i < numeroTareas; ++i) {
                Tarea tarea("", "", 0, "", "", "");
                tarea.cargarDesdeArchivo(archivo);
                tareas.push_back(tarea);
            }

            archivo.close();
            cout << "Datos cargados correctamente desde " << nombreArchivo << endl;
        } else {
            cout << "Error al abrir el archivo para cargar datos :c." << endl;
        }
    }
};

int main() {
    Plataforma plataforma;

    // Cargar datos desde archivo
    plataforma.cargarDesdeArchivo("datos_plataforma.txt");

    int opcion;
    do {
        cout << "\n--- Menu de la Plataforma ---\n";
        cout << "1. Registrar una nueva tarea\n";
        cout << "2. Revisar tareas pendientes\n";
        cout << "3. Completar una tarea :b\n";
        cout << "4. Revisar puntos y recompensas\n";
        cout << "5. Guardar y salir\n";
        cout << "Seleccione una opcion: ";
        cin >> opcion;
        cin.ignore();

        switch(opcion) {
            case 1: {
                string descripcion, recompensa, tema, nombreUsuario;
                int puntos;
                cout << "Ingrese la descripcion de la tarea: ";
                getline(cin, descripcion);
                cout << "Ingrese los puntos de recompensa: ";
                cin >> puntos;
                cin.ignore();
                cout << "Ingrese la recompensa: ";
                getline(cin, recompensa);
                cout << "Ingrese el tema de la tarea (por ejemplo: ingles, matematicas, biologia): ";
                getline(cin, tema);
                cout << "Ingrese el nombre del usuario que completará la tarea: ";
                getline(cin, nombreUsuario);
                plataforma.agregarTarea(descripcion, puntos, recompensa, tema, nombreUsuario);
                break;
            }
            case 2: {
                plataforma.mostrarTareasPendientes();
                break;
            }
            case 3: {
                string codigoTarea;
                cout << "Ingrese el codigo de la tarea a completar: ";
                getline(cin, codigoTarea);
                plataforma.completarTarea(codigoTarea);
                break;
            }
            case 4: {
                plataforma.mostrarInformacionUsuarios();
                break;
            }
            case 5: {
                plataforma.guardarEnArchivo("datos_plataforma.txt");
                cout << "Saliendo y guardando datos...\n";
                break;
            }
            default: {
                cout << "Opcion no válida :(. Intenta de nuevo.\n";
                break;
            }
        }
    } while(opcion != 5);

    return 0;
}

