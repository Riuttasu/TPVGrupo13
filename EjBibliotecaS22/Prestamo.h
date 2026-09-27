#pragma once
#ifndef PRESTAMO_H
#define PRESTAMO_H
#include "Date.hpp"
#include "Catalogo.h"
class Prestamo
{
private:
	int codigoUsuario;
	Date fechaPrestamo;
	Ejemplar* ejemplar;
public:
	// constructora sin argumentos
	Prestamo();
	// constructora con argumentos
	Prestamo(int codigoUsuario, Date fechaPrestamo, Ejemplar* ejemplar);
	// getters básicos
	int GetCodigoUsuario() const;
	Date GetFechaPrestamo() const;
	Ejemplar* GetEjemplar() const;
	// conseguir la fecha de devolución
	Date GetDevolucion() const;
	// leer archivo de prestamos
	void leerPrestamo(const Catalogo&, std::istream&);
	//operadores
	friend std::ostream& operator <<(std::ostream&, const Prestamo&);
};

#endif // !PRESTAMO_H