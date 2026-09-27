// Grupo 13
// Leo Reyes y Lune Redondo
#pragma once
#ifndef EJEMPLAR_H
#define EJEMPLAR_H
#include <string>
#include <fstream>
using namespace std;
class Ejemplar
{
public:
	// Diferentes tipos de ejemplar que existen
	enum TIPO
	{
		Libro, Audiovisual, Juego
	};
	Ejemplar(); // Constructora sin argumentos
	Ejemplar(int Codigo, TIPO Tipo, string Nombre); // Constructora con argumentos
	// Getters
	int GetCodigo() const;
	TIPO GetTipo() const;
	string GetNombre() const;
	// Disponibilidad
	void Presta();
	void Devuelve();
	// operadores
	friend std::istream& operator>>(std::istream&, Ejemplar&);
	friend std::ostream& operator<<(std::ostream&, const Ejemplar&);
private:
	int codigo;
	TIPO tipo;
	string nombre;
	bool disponible;
};

#endif // !EJEMPLAR_H


