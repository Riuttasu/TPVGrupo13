#include "Ejemplar.h"
Ejemplar::Ejemplar() : codigo(0), tipo(Libro), nombre("."), disponible(true)
{
}
Ejemplar::Ejemplar(int Codigo, TIPO Tipo, string Nombre) : codigo(Codigo), tipo(Tipo), nombre(Nombre), disponible(true)
{
	
}
int Ejemplar::GetCodigo() const
{
	return codigo;
}
Ejemplar::TIPO Ejemplar::GetTipo() const
{
	return tipo;
}
string Ejemplar::GetNombre() const
{
	return nombre;
}
void Ejemplar::Presta() 
{
	disponible = false;
}
void Ejemplar::Devuelve()
{
	disponible = true;
}
std::istream& operator>>(std::istream& file, Ejemplar& ejem)
{
	// Lee el numero del codigo, si no se puede por mal formato tira exception
	if (!(file >> ejem.codigo)) throw std::exception("Mal formato de codigo");
	// Lee el caracter del tipo
	char c = '.';
	// Si mal formato tira exception
	if (!(file >> c)) throw std::exception("Mal formato en tipo");
	// Establece tipo dependiendo del caracter
	if (c == 'L') ejem.tipo = Ejemplar::TIPO::Libro;
	else if (c == 'A') ejem.tipo = Ejemplar::TIPO::Audiovisual;
	else if (c == 'J') ejem.tipo = Ejemplar::TIPO::Juego;
	// Si no es ninguno tira exception
	else throw std::exception("Tipo de ejemplar no reconocido");
	// Lee el nombre hasta el final de linea
	getline(file, ejem.nombre);
	return file;
}
std::ostream& operator<<(std::ostream& file, const Ejemplar& ejem)
{
	// Codigo
	file << ejem.codigo << "  ";
	// Tipo
	switch (ejem.tipo)
	{
	case Ejemplar::TIPO::Libro: file << "Libro        "; break;
	case Ejemplar::TIPO::Juego: file << "Juego        ";break;
	case Ejemplar::TIPO::Audiovisual: file << "Audiovisual  "; break;
	}
	// Nombre
	file << ejem.nombre;
	return file;
}