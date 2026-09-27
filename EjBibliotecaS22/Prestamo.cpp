#include "Prestamo.h"


// constructora sin argumentos
Prestamo::Prestamo() : codigoUsuario(0), fechaPrestamo(), ejemplar(nullptr)
{
}
// constructora con argumentos
Prestamo::Prestamo(int codigoUsuario, Date fechaPrestamo, Ejemplar* ejemplar) : codigoUsuario(codigoUsuario), fechaPrestamo(fechaPrestamo), ejemplar(ejemplar)
{
}


// geters básicos

int Prestamo::GetCodigoUsuario() const
{
	return codigoUsuario;
}
Date Prestamo::GetFechaPrestamo() const
{
	return fechaPrestamo;
}
Ejemplar* Prestamo::GetEjemplar() const
{
	return ejemplar;
}


// conseguir la fecha de devolución
// 30 para libros, 7 para audiovisuales y 14 para juegos
Date Prestamo::GetDevolucion() const
{
	int dias = 0;
	// se consulta el tipo para ver cuantos dias le corresponden
	switch (ejemplar->GetTipo())
	{
	case Ejemplar::TIPO::Libro:
		dias = 30;
		break;
	case Ejemplar::TIPO::Audiovisual:
		dias = 7;
		break;
	case Ejemplar::TIPO::Juego:
		dias = 14;
		break;
	default:
		dias = 0;
		break;
	}
	return fechaPrestamo + dias;
}

// leer archivo de prestamos
void Prestamo::leerPrestamo(const Catalogo& catalogo, std::istream& file)
{
	// lee el codigo de usuario
	file >> codigoUsuario;
	// lee la fecha de prestamo
	file >> fechaPrestamo;
	// lee el codigo del ejemplar
	int codigoEjemplar;
	file >> codigoEjemplar;
	// busca el ejemplar en el catalogo
	ejemplar = catalogo.BuscaEjemplar(codigoEjemplar);
}

// operador de salida
std::ostream& operator <<(std::ostream& out, const Prestamo& prestamo)
{
	// parámetro auxiliares para la salida
	Date diaActual = Date(); // date cpp tiene metodo para obtener la fecha actual
	int diasPrestamo = prestamo.fechaPrestamo.diff(diaActual); // dias que han pasado desde el prestamo

	if (diasPrestamo > 0)
	{
		out << prestamo.fechaPrestamo << " (en " << diasPrestamo << "días) " << prestamo.ejemplar->GetNombre() << std::endl;
	}
	else
	{
		int penalizacion = diasPrestamo * 2; // dias que han pasado desde el prestamo
		out << prestamo.fechaPrestamo << " (en " << diasPrestamo << "días) " << prestamo.ejemplar->GetNombre() << " (" << penalizacion << " días de penalización";
	}
	return out;
}