
#include <iostream>
#include <string>
#include "./Apoyo/SortedArrayList.h"
#include "./Apoyo/LinkedPriorityQueue.h"

using namespace std;

// Estructura de tipos de usuario, posee el nombre del tipo, una descripción y su prioridad.
struct TipoUsuario {

	string nombre;
	string descripcion;
	int prioridad;

	// Constructores.
	TipoUsuario() : nombre(""), descripcion(""), prioridad(0) {}
	TipoUsuario(string nom, string desc, int prio) : nombre(nom), descripcion(desc), prioridad(prio) {}
	
	// Dicta que se muestra al realizar un console out del objeto.
	friend std::ostream& operator<<(std::ostream& os, const TipoUsuario& tipo) {
		os << tipo.nombre << ", " << tipo.descripcion << ", Prioridad: " << tipo.prioridad <<  endl;
		return os;
	}

	// Sobrecarga del operador >= para evaluar prioridad.
	bool operator>=(const TipoUsuario& otro) const {
		return prioridad >= otro.prioridad;
	}
};

struct Tiquete {
	string codigoArea;
	int numGlobal;
	int horaSolicitud;
	int prioridadFinal;

	Tiquete() : codigoArea(""), numGlobal(0), horaSolicitud(0), prioridadFinal(0) {}
	Tiquete(string codi, int nume, int hora, int prio) : codigoArea(codi), numGlobal(nume), horaSolicitud(hora), prioridadFinal(prio) {}

	// Dicta que se muestra al realizar un console out del objeto.
	friend std::ostream& operator<<(std::ostream& os, const Tiquete& tiquete) {
		os << tiquete.codigoArea << tiquete.numGlobal << ", hora de  solicitud: " << tiquete.horaSolicitud << ", prioridad: " << tiquete.prioridadFinal << endl;
		return os;
	}

	// Sobrecarga del operador >= para evaluar prioridad.
	bool operator>=(const Tiquete& otro) const {
		return prioridadFinal >= otro.prioridadFinal;
	}
};

struct Area {

	string descripcion;
	string codigo;
	int ventanillas;
	LinkedPriorityQueue<Tiquete>* colaTiquetes;

	Area() : descripcion(""), codigo(""), ventanillas(0) , colaTiquetes(new LinkedPriorityQueue<Tiquete>(5)){}
	Area(string desc, string codi, int vent, int prio) : descripcion(desc), codigo(codi), ventanillas(vent), colaTiquetes(new LinkedPriorityQueue<Tiquete>(prio)) {}
	Area(int prio) : descripcion(""), codigo(""), ventanillas(0), colaTiquetes(new LinkedPriorityQueue<Tiquete>(prio)) {}

	// Dicta que se muestra al realizar un console out del objeto.
	friend std::ostream& operator<<(std::ostream& os, const Area& area) {
		os << "Area " << area.codigo << endl;
		return os;
	}
};

struct Servicio {

	string nombre;
	string descripcion;
	int prioridad;
	string codigoArea;

	Servicio() : nombre(""), descripcion(""), prioridad(0), codigoArea("") {}
	Servicio(string nom, string desc, int prio, string cod) : nombre(nom), descripcion(desc), prioridad(prio), codigoArea(cod) {}

	// Dicta que se muestra al realizar un console out del objeto.
	friend std::ostream& operator<<(std::ostream& os, const Servicio& servicio) {
		os << servicio.nombre << ", " << servicio.descripcion << ", Prioridad: " << servicio.prioridad << endl;
		return os;
	}

	// Sobrecarga del operador >= para evaluar prioridad.
	bool operator>=(const Servicio& otro) const {
		return prioridad >= otro.prioridad;
	}
};


int main()
{

	int numGlobal = 100;

	// Inicializa todas las listas
    ArrayList<TipoUsuario>* tiposUsuario = new SortedArrayList<TipoUsuario>;
	ArrayList<Servicio>* servicios = new ArrayList<Servicio>;
	ArrayList<Area>* areas = new ArrayList<Area>;

	try
	{
		// Se llenan los tipos de usuario
		TipoUsuario tipo1("Adulto Mayor", "Persona de la tercera edad", 1);
		TipoUsuario tipo2("Persona con Necesidades Especiales", "Usuario con requerimientos especiales", 2);
		tiposUsuario->insert(tipo2);
		tiposUsuario->insert(tipo1);
		TipoUsuario tipo = tiposUsuario->getElement();
		cout << tipo.nombre << endl;


		// Se llenan los servicios
		Servicio serv1("Visita", "Permite acceder a las instalaciones", 2, "C");
		Servicio serv2("Entrega", "Entrega de un objeto en las instalaciones", 1, "D");
		servicios->append(serv1);
		servicios->append(serv2);
		Servicio serv = servicios->getElement();
		cout << serv.nombre << endl;


		// Esto hace que los servicios sean ordenados por orden de prioridad
		ArrayList<Servicio>* servicios2 = new SortedArrayList<Servicio>;
		servicios->goToStart();
		for (int i = 0; i < servicios->getSize(); i++){
			servicios2->insert(servicios->getElement());
			servicios->next();
		}
		delete servicios;
		serv = servicios2->getElement();
		cout << serv.nombre << endl;

		// Sistema de areas y tiquetes
		Tiquete tiquete("C", numGlobal, 7, (1 * 10 + 2));
		numGlobal++;
		Area areaA("Manejo de visitas", "V", 3, 5);
		areas->append(areaA);
		areas->getElement().colaTiquetes->insert(tiquete, tiquete.prioridadFinal);

	}
	catch (const std::exception&)
	{

	}
}
