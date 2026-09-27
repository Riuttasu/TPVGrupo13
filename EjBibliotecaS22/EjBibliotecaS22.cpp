
#include <fstream>
#include <iostream>
#include <windows.h>
#include "Ejemplar.h"
#include "Catalogo.h"
using namespace std;
int main()
{
    SetConsoleOutputCP(CP_UTF8);
    ifstream catalogofile("catalogo.txt");
    Catalogo catalogo(catalogofile);

    return 0;
}