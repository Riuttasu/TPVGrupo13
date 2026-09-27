#include "Catalogo.h"
#include <algorithm>
Catalogo::Catalogo(istream& file)
{
	// Lee el número de ejemplares
	file >> numElems;
	// Crea el array dinamico
	elems = new Ejemplar[numElems];
	// Rellena el array
	for (int i = 0; i < numElems;i++)
	{
		try
		{
			// Creacion uno por uno de los ejemplares, si hay error de formato tiran exception
			file >> elems[i];
		}
		catch(const std::exception& e)
		{
			// Si ha habido errores en la lectura de los ejemplares se aborta la creacion
			// Borra de memoria dinamica para evitar memory leaks
			delete[] elems;
			elems = nullptr;
			numElems = 0;
			// Vuelve a tirar la excepcion
			throw;
		}
	}
}
/// <summary>
/// Destructora
/// </summary>
Catalogo::~Catalogo()
{
	delete[] elems;
	elems = nullptr;
	numElems = 0;
}
/// <summary>
/// Funcion para buscar un ejemplar mediante su codigo identificador dentro del catalogo
/// </summary>
/// <param name="Codigo">Codigo del ejemplar a buscar</param>
/// <returns>Puntero al ejemplar, si no existe dentro del catalogo nullptr</returns>
Ejemplar* Catalogo::BuscaEjemplar(int Codigo) const
{
	// Uso de busqueda binaria
	Ejemplar* ejem = lower_bound(elems, elems+numElems, Codigo, comparaCodigo);
	// La busqueda binaria devuelve last si no se ha encontrado, comprobamos que no es el caso
	if (ejem != elems + numElems && ejem->GetCodigo() == Codigo) return ejem;
	// Si es el caso, devuelve nullptr
	else return nullptr;
}
/// <summary>
/// Funcion para comparar codigo de ejemplar en la busqueda binaria
/// </summary>
bool Catalogo::comparaCodigo(const Ejemplar& ejemplar, const int codigo) {
	return ejemplar.GetCodigo() < codigo;
}
void Catalogo::Mostrar(ostream& file)
{
	file << "  ID | Tipo | Nombre" << endl;
	for (int i = 0;i < numElems;i++)
	{
		file << elems[i] << std::endl;
	}
}
