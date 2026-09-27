#pragma once
#ifndef LISTAPRESTAMOS_H
#define LISTAPRESTAMOS_H
#include "Prestamo.h"
class ListaPrestamos
{
private:
	Prestamo* elems;
	size_t numElems;
public:
	// contructora
	ListaPrestamos(const Catalogo&, std::istream&);
	// destructora
	~ListaPrestamos();
	// ordenar la lista por fecha de devolución
	void Ordenar();
	// mostrar la lista de prestamos
	void Mostrar(std::ostream&);
private:
	// operador para el orden
	bool operator<(const Prestamo&) const;
};
#endif // !LISTAPRESTAMOS_H


