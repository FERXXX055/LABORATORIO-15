#include <iostream>
#include <string>
#include <fstream>
using namespace std;

// Funcion estilo formal
string estiloFormal(string r) {
    return "Estimado usuario: " + r;
}

// Funcion estilo amistoso
string estiloAmistoso(string r) {
    return "Hey! " + r;
}

// Estructura de nodo para lista enlazada
struct Nodo {
    string texto;
    Nodo* siguiente;
};

// Crear nodo con new
Nodo* crearNodo(const string& texto) {
    Nodo* nuevo = new Nodo;
    nuevo->texto = texto;
    nuevo->siguiente = nullptr;
    return nuevo;
}

// Insertar al final de la lista
void insertarAlFinal(Nodo*& cabeza, const string& texto) {
    Nodo* nuevo = crearNodo(texto);
    if (!cabeza) {
        cabeza = nuevo;
    }
    else {
        Nodo* actual = cabeza;
        while (actual->siguiente) {
            actual = actual->siguiente;
        }
        actual->siguiente = nuevo;
    }
}

// Mostrar lista
void mostrarLista(Nodo* cabeza) {
    Nodo* actual = cabeza;
    while (actual) {
        cout << actual->texto << endl;
        actual = actual->siguiente;
    }
}

// Liberar memoria de la lista
void liberarMemoria(Nodo*& cabeza) {
    while (cabeza) {
        Nodo* temp = cabeza;
        cabeza = cabeza->siguiente;
        delete temp;
    }
}

// Buscar una palabra clave en las frases
string buscarFrase(Nodo* cabeza, const string& clave) {
    Nodo* actual = cabeza;
    while (actual) {
        if (actual->texto.find(clave) != string::npos) {
            return actual->texto;
        }
        actual = actual->siguiente;
    }
    return "";
}

// Cargar frases desde un archivo
void cargarFrasesDesdeArchivo(Nodo*& cabeza, const string& nombreArchivo) {
    ifstream archivo(nombreArchivo);
    if (!archivo.is_open()) {
        cout << "No se pudo abrir el archivo." << endl;
        return;
    }
    string linea;
    while (getline(archivo, linea)) {
        insertarAlFinal(cabeza, linea);
    }
    archivo.close();
}

int main() {
    cout << "=== Mini Chatbot con frases ===" << endl;

    // Declaracion de punteros
    int numero = 5;
    int* ptr = &numero;
    cout << "Valor de numero: " << numero << ", valor apuntado por ptr: " << *ptr << endl;

    // sizeof
    cout << "sizeof(int): " << sizeof(int) << " bytes, sizeof(ptr): " << sizeof(ptr) << " bytes" << endl;

    // Arreglo de punteros
    const char* respuestas[] = {
        "Hola", "Como estas?", "Adios"
    };
    const char** p = respuestas;
    for (int i = 0; i < 3; ++i) {
        cout << *(p + i) << endl;
    }

    // Lista enlazada cargada desde archivo
    Nodo* lista = nullptr;
    cargarFrasesDesdeArchivo(lista, "frases.txt");

    // Mostrar las frases
    cout << "\nFrases cargadas:" << endl;
    mostrarLista(lista);

    // Seleccionar estilo
    bool modoFormal = false;
    string(*responder)(string);
    responder = modoFormal ? estiloFormal : estiloAmistoso;

    // Buscar y responder
    cout << "\nIngresa una palabra clave: ";
    string clave;
    getline(cin, clave);
    string respuesta = buscarFrase(lista, clave);

    if (respuesta != "") {
        cout << "Chatbot responde: " << responder(respuesta) << endl;
    }
    else {
        cout << "No se encontro una frase para esa palabra." << endl;
    }

    // Liberar memoria usada
    liberarMemoria(lista);

    return 0;
}