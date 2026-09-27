// Grupo 13
// Leo Reyes y Lune Redondo
#include "ListaPrestamos.h"
#include <algorithm>

// contructora
ListaPrestamos::ListaPrestamos(const Catalogo& catalogo, std::istream& file){
	// lee el numero de prestamos
	file >> numElems;
	// crea el array dinamico
	elems = new Prestamo[numElems];
	// rellena el array
	for (size_t i = 0; i < numElems; i++) {
		// rellena cada prestamo con la funcion leerPrestamo
		try
		{
			elems[i].leerPrestamo(catalogo, file);
		}
		catch (const std::exception e)
		{
			throw;
		}
	}
}

// destructora
ListaPrestamos::~ListaPrestamos() {
	numElems = 0;
	delete[] elems;
}

// operador para el orden
bool ListaPrestamos::operator<(const Prestamo& otro) const {
	return elems->GetDevolucion() < otro.GetDevolucion();
	// devuelve true si el prestamo actual tiene fecha de devolucion menor que el otro
}

// función que ordena la lista de prestamos por fecha de devolucion
void ListaPrestamos::Ordenar() {
	// ordena el array de prestamos usando el operador <
	std::sort(elems, elems + numElems, [](const Prestamo& a, const Prestamo& b) {
		return a.GetDevolucion() < b.GetDevolucion();
		});
}

// función que muestra la lista de prestamos
void ListaPrestamos::Mostrar(std::ostream& out) {
	// recorre el array de prestamos y muestra cada uno
	for (size_t i = 0; i < numElems; i++) {
		out << elems[i] << std::endl;
	}
}