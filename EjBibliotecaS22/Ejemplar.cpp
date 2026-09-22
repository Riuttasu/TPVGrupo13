#include "Ejemplar.h"
Ejemplar::Ejemplar() : codigo(0), tipo(DESCONOCIDO), nombre("."), disponible(true)
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