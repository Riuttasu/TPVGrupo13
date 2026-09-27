// Grupo 13
// Leo Reyes y Lune Redondo
#include <fstream>
#include <iostream>
#include <windows.h> // Para tildes
#include "Catalogo.h"
#include "ListaPrestamos.h"
using namespace std;
int main()
{
    // tildes
    SetConsoleOutputCP(CP_UTF8);
    try
    {
        // Inicio
        // catalogo
        ifstream catalogofile("catalogo.txt");
        Catalogo catalogo(catalogofile);
        // prestamos
        ifstream prestamosfile("prestamos.txt");
        ListaPrestamos listaprestamos(catalogo,prestamosfile);
        listaprestamos.Ordenar(); // ordenacion de la lista
        // Opcion que tome el usuario
        int opt = 0;
        // Bucle
        bool hayprograma = true;
        while (hayprograma)
        {
        // Texto inicial
        cout << "Elige una opción:\n" << "1. Mostrar el catálogo.\n" << "2. Mostrar préstamos.\n" << "3. Salir\n";
        if (!(cin >> opt))
        {
            // Si se ha introducido un caracter no numerico
            cout << "Pon un numerico anda\n";
            // Quita el estado fail
            cin.clear();
            // Ignora la entrada anterior hasta 1000 caracteres, si ha puesto mas el usuario es muy tonto
            cin.ignore(1000, '\n');
        }
        else
        {
            switch (opt)
            {
            case 1: catalogo.Mostrar(cout); break;
            case 2: listaprestamos.Mostrar(cout); break;
            case 3: hayprograma = false; break;
            default: cout << "Comando no reconocido" << endl; break;
            }
        }
        }
    }
    catch(const std::exception& e)
    {
        cout << e.what() << endl;
        return 1;
    }
    cout << "Gracias por usar la biblioteca (como en c++ uff referencia), vuelva pronto" << endl;
    return 0;
}