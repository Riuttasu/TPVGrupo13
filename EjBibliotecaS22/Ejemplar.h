#pragma once
#ifndef EJEMPLAR_H
#define EJEMPLAR_H
#include <string>
#include <fstream>
using namespace std;
class Ejemplar
{
public:
	enum TIPO
	{
		Libro, Audiovisual, Juego, DESCONOCIDO
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
private:
	int codigo;
	TIPO tipo;
	string nombre;
	bool disponible;
};

#endif // !EJEMPLAR_H


