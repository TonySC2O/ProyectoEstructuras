#pragma once
#include <iostream>
#include <string>
#include <stdexcept>
#include "tiempo.h"

using namespace std;

// Estructura de tipos de usuario, posee el nombre del tipo, una descripci�n y su prioridad.
struct TipoUsuario {

	string nombre;
	string descripcion;
	int prioridad;

	// Constructores.
	TipoUsuario() : nombre(""), descripcion(""), prioridad(0) {}
	TipoUsuario(string nom, string desc, int prio) : nombre(nom), descripcion(desc), prioridad(prio) {
		if (prio >= DEFAULT_MAX_PRIORITY)
		{
			prio = DEFAULT_MAX_PRIORITY - 1;
		}
	}
	~TipoUsuario() {}

	// Dicta que se muestra al realizar un console out del objeto.
	friend std::ostream& operator<<(std::ostream& os, const TipoUsuario& tipo) {
		os << tipo.nombre << ", " << tipo.descripcion << ", Prioridad: " << tipo.prioridad << endl;
		return os;
	}

	// Sobrecarga del operador >= para evaluar prioridad.
	bool operator>=(const TipoUsuario& otro) const {
		return prioridad >= otro.prioridad;
	}

	// Sobrecarga del operador >= para evaluar prioridad.
	bool operator==(const TipoUsuario& otro) const {
		return nombre == otro.nombre;
	}
};

struct Tiquete {
	string codigoArea;
	string tipoUsuarioAsociado;
	string tipoServicioAsociado;
	int numGlobal;
	int horaSolicitudEnSegundos;
	int prioridadFinal;

	Tiquete() : codigoArea(""), tipoUsuarioAsociado(""), tipoServicioAsociado(""), numGlobal(0), horaSolicitudEnSegundos(0), prioridadFinal(0) {}
	Tiquete(string codi, string usua, string serv, int nume, int hora, int prio) : codigoArea(codi), tipoUsuarioAsociado(usua), tipoServicioAsociado(serv), numGlobal(nume), horaSolicitudEnSegundos(hora), prioridadFinal(prio) {}

	friend std::ostream& operator<<(std::ostream& os, const Tiquete& tiquete) {
		os << tiquete.codigoArea << tiquete.numGlobal << ", hora de solicitud: " << segundosATiempo(tiquete.horaSolicitudEnSegundos) << ", prioridad: " << tiquete.prioridadFinal;
		return os;
	}

	bool operator>=(const Tiquete& otro) const {
		return prioridadFinal >= otro.prioridadFinal;
	}

	bool operator==(const Tiquete& otro) const {
		return (codigoArea + to_string(numGlobal)) == (otro.codigoArea + to_string(otro.numGlobal));
	}
};

struct Ventanilla {
	string nombre = "";
	string tiqueteAtendido = "";
	int cantidadPersonas = 0;

	Ventanilla() : nombre(""), tiqueteAtendido("None") {}
	Ventanilla(string nomb) : nombre(nomb), tiqueteAtendido("None") {}

	// Dicta que se muestra al realizar un console out del objeto.
	friend std::ostream& operator<<(std::ostream& os, const Ventanilla& ventanilla) {
		os << "(" << ventanilla.nombre << ", " << ventanilla.tiqueteAtendido << ")" << endl;
		return os;
	}

	// Sobrecarga del operador >= para evaluar prioridad.
	bool operator==(const Ventanilla& otro) const {
		return nombre == otro.nombre;
	}
};


struct Servicio {

	string nombre;
	string descripcion;
	int prioridad;
	string codigoArea;

	Servicio() : nombre(""), descripcion(""), prioridad(0), codigoArea("") {}
	Servicio(string nom, string desc, int prio, string cod) : nombre(nom), descripcion(desc), prioridad(prio), codigoArea(cod) {
		if (prio >= DEFAULT_MAX_PRIORITY)
		{
			prio = DEFAULT_MAX_PRIORITY - 1;
		}
	}

	// Dicta que se muestra al realizar un console out del objeto.
	friend std::ostream& operator<<(std::ostream& os, const Servicio& servicio) {
		os << servicio.nombre << ", " << servicio.descripcion << ", Prioridad: " << servicio.prioridad << endl;
		return os;
	}

	// Sobrecarga del operador >= para evaluar prioridad.
	bool operator>=(const Servicio& otro) const {
		return prioridad >= otro.prioridad;
	}
	// Sobrecarga del operador >= para evaluar prioridad.
	bool operator==(const Servicio& otro) const {
		return nombre == otro.nombre;
	}
};

struct Area {

	string descripcion;
	string codigo;
	ArrayList<Ventanilla>* ventanillas;
	LinkedPriorityQueue<Tiquete>* colaTiquetes;

	Area() : descripcion(""), codigo(""), ventanillas(new ArrayList<Ventanilla>()), colaTiquetes(new LinkedPriorityQueue<Tiquete>(DEFAULT_MAX_PRIORITY * 10 + DEFAULT_MAX_PRIORITY)) {}
	Area(string desc, string codi, int vent) : descripcion(desc), codigo(codi), ventanillas(new ArrayList<Ventanilla>(vent)), colaTiquetes(new LinkedPriorityQueue<Tiquete>(DEFAULT_MAX_PRIORITY * 10 + DEFAULT_MAX_PRIORITY)) {
		ventanillas->goToStart();
		for (int i = 0; i < vent; i++)
		{
			Ventanilla ventana((codigo + to_string(i + 1)));
			ventanillas->append(ventana);
			ventanillas->next();
		}
	}

	// Dicta que se muestra al realizar un console out del objeto.
	friend std::ostream& operator<<(std::ostream& os, const Area& area) {
		os << "(Area " << area.codigo << ")";
		return os;
	}

	// Sobrecarga del operador >= para evaluar prioridad.
	bool operator==(const Area& otro) const {
		return codigo == otro.codigo;
	}

};

int numGlobal = 100;

// Inicializa todas las listas
ArrayList<TipoUsuario>* tiposUsuario = new SortedArrayList<TipoUsuario>;
ArrayList<Servicio>* servicios = new ArrayList<Servicio>;
ArrayList<Area>* areas = new ArrayList<Area>;

void verColas() {
	areas->goToStart();
	for (int i = 0; i < areas->getSize(); i++)
	{
		cout << "====================================" << endl;
		cout << "Area " << areas->getElement().codigo << ":" << endl;
		areas->getElement().colaTiquetes->print();
		areas->next();
	}
}

void agregarTipoUsuario() {
	string nombre, descripcion;
	int prioridad;
	cout << "Ingrese el nombre del tipo de usuario: ";
	cin.ignore();
	getline(cin, nombre);
	cout << "Ingrese la descripcion del tipo de usuario: ";
	cin.ignore();
	getline(cin, descripcion);
	cout << "Ingrese la prioridad del tipo de usuario: ";
	cin >> prioridad;
	TipoUsuario nuevoTipo(nombre, descripcion, prioridad);
	tiposUsuario->append(nuevoTipo);
}

void agregarServicio() {
	if (areas->getSize() == 0)
	{
		throw runtime_error("No existen areas para asignar a servicio.");
	}
	string nombre, descripcion, codigoArea;
	int prioridad;
	cout << "Ingrese el nombre del servicio: ";
	cin.ignore();
	getline(cin, nombre);
	cout << "Ingrese la descripcion del servicio: ";
	cin.ignore();
	getline(cin, descripcion);
	cout << "Ingrese la prioridad del servicio: ";
	cin >> prioridad;
	cout << "Ingrese el codigo del area asociada al servicio: ";
	cin >> codigoArea;

	servicios->goToStart();
	for (int i = 0; i < servicios->getSize(); i++)
	{
		if (servicios->getElement().codigoArea == codigoArea)
		{
			throw runtime_error("Otro servicio ya es tratado en esta area.");
		}
		if (servicios->getElement().nombre == nombre)
		{
			throw runtime_error("Otro servicio ya posee ese nombre.");
		}
		servicios->next();
	}
	bool existe = false;
	areas->goToStart();
	for (int i = 0; i < areas->getSize(); i++)
	{
		if (areas->getElement().codigo == codigoArea)
		{
			existe = true;
		}
		areas->next();
	}
	if (!existe)
	{
		throw runtime_error("Area digitada no existe.");
	}

	Servicio nuevoServicio(nombre, descripcion, prioridad, codigoArea);
	servicios->append(nuevoServicio);
}

void agregarArea() {
	string descripcion, codigo;
	int cantidadVentanillas;

	cout << "Ingrese el codigo del area: ";
	cin >> codigo;

	areas->goToStart();
	for (int i = 0; i < areas->getSize(); i++)
	{
		if (areas->getElement().codigo == codigo)
		{
			throw runtime_error("Codigo de servicio ya utilizado");
		}
		areas->next();
	}

	cout << "Ingrese la descripcion del area: ";
	cin.ignore();
	getline(cin, descripcion);

	cout << "Ingrese la cantidad de ventanillas: ";
	cin >> cantidadVentanillas;
	Area nuevaArea(descripcion, codigo, cantidadVentanillas);
	areas->append(nuevaArea);
}

void eliminarTipoUsuario(int pos) {
	tiposUsuario->goToPos(pos);
	TipoUsuario tempUsuario = tiposUsuario->remove();

	areas->goToStart();
	for (int i = 0; i < areas->getSize(); i++) {
		int sizeCola = areas->getElement().colaTiquetes->getSize();
		for (int j = 0; j < sizeCola; j++) {
			Tiquete tiquetTemp = areas->getElement().colaTiquetes->removeMin();
			if (tiquetTemp.tipoUsuarioAsociado != tempUsuario.nombre) {
				areas->getElement().colaTiquetes->insert(tiquetTemp, tiquetTemp.prioridadFinal);
			}
		}
		areas->next();
	}
}

void eliminarServicio() {
	cout << "Lista de servicios disponibles:" << endl;
	for (int i = 0; i < servicios->getSize(); i++) {
		cout << i + 1 << ". " << servicios->getElement() << endl;
		servicios->next();
	}
	int opcion;
	cout << "Seleccione el numero del servicio que desea eliminar: ";
	cin >> opcion;
	servicios->goToPos(opcion - 1);
	servicios->remove();
	servicios->goToStart(); // Regresar al inicio de la lista
}

void eliminarArea(int pos) {
	areas->goToPos(pos);
	Area areaTemp = areas->remove();
	cout << "e" << endl;

	//ahora se busca en servicios
	servicios->goToStart();
	for (int i = 0; i < servicios->getSize(); i++)
	{
		if (servicios->getElement().codigoArea == areaTemp.codigo)
		{
			servicios->remove();
			break;
		}
		servicios->next();
	}

	areaTemp.colaTiquetes->~LinkedPriorityQueue();
	areaTemp.ventanillas->~ArrayList();
}

// Este codigo recorre cada area para ver cual coincide con el codigo del area del tiquete
void colocarTiquete(string codigoArea, string tipoUsuario, string tipoServicio, int numGlobal, int horaSolicitud, int prioridadFinal) {
	Tiquete nuevoTiquete(codigoArea, tipoUsuario, tipoServicio, numGlobal, horaSolicitud, prioridadFinal);
	areas->goToStart();
	for (int i = 0; i < areas->getSize(); i++) {
		if (areas->getElement().codigo == codigoArea) {
			areas->getElement().colaTiquetes->insert(nuevoTiquete, nuevoTiquete.prioridadFinal);
			break;
		}
		areas->next();
	}
}

void eliminarTicketsCola(int opcion, int pos) {

	TipoUsuario tempUsuario;
	Servicio tempServicio;

	if (opcion == 1)
	{
		tiposUsuario->goToPos(pos);
		tempUsuario = tiposUsuario->remove();
	}
	else if (opcion == 2) {
		servicios->goToPos(pos);
		tempServicio = servicios->remove();
	}

	areas->goToStart();
	for (int i = 0; i < areas->getSize(); i++)
	{
		int sizeCola = areas->getElement().colaTiquetes->getSize();
		for (int j = 0; j < sizeCola; j++)
		{
			if (opcion != 0)
			{
				Tiquete tiquetTemp = areas->getElement().colaTiquetes->removeMin();
				if (opcion == 1 && tiquetTemp.tipoUsuarioAsociado != tempUsuario.nombre) {
					areas->getElement().colaTiquetes->insert(tiquetTemp, tiquetTemp.prioridadFinal);
				}
				else if (opcion == 2 && tiquetTemp.tipoServicioAsociado != tempServicio.nombre) {
					areas->getElement().colaTiquetes->insert(tiquetTemp, tiquetTemp.prioridadFinal);
				}
			}
			else {
				areas->getElement().colaTiquetes->removeMin();
			}

		}
		areas->next();
	}


}
void modificarCantidadVentanillas(int pos, int nuevaCantidad) {
	areas->goToPos(pos);
	Area area = areas->getElement(); // Obtener el elemento directamente, no como referencia
	int cantidadVentanillas = area.ventanillas->getSize();

	// Eliminar las ventanillas actuales
	for (int i = 0; i < cantidadVentanillas; i++) {
		area.ventanillas->remove();
	}

	// Crear nuevas ventanillas
	for (int i = 0; i < nuevaCantidad; i++) {
		Ventanilla ventana((area.codigo + to_string(i + 1)));
		area.ventanillas->append(ventana);
	}
}

void limpiarColasYEstadisticas() {
	areas->goToStart();
	for (int i = 0; i < areas->getSize(); i++) {
		areas->getElement().colaTiquetes->clear();
	}
}

void reordenarServicios() {
	cout << "Lista de servicios disponibles:" << endl;
	for (int i = 0; i < servicios->getSize(); i++) {
		cout << i + 1 << ". " << servicios->getElement() << endl;
		servicios->next();
	}
	int numServicio, nuevaPosicion;
	cout << "Ingrese el numero del servicio que desea reordenar: ";
	cin >> numServicio;
	cout << "Ingrese la nueva posicion del servicio: ";
	cin >> nuevaPosicion;
	servicios->goToPos(numServicio - 1);
	Servicio servicio = servicios->remove();
	servicios->goToPos(nuevaPosicion - 1);
	servicios->insert(servicio);
}

void atenderTiquete() {
	string codigo;
	Area area;
	int indiceVentanilla;

	int i = 0;
	cout << "Ingrese el codigo del area: ";
	cin >> codigo;

	areas->goToStart();
	for (i = 0; i < areas->getSize(); i++) {
		if (areas->getElement().codigo == codigo) {
			area = areas->getElement();
		}
		areas->next();

	}

	if (i < areas->getSize()) {
		cout << "El area tiene " << area.ventanillas->getSize() << "ventanillas, ingrese la ventanilla a atender. " << endl;
		cout << "El indice inicia en 1" << endl;
		cin >> indiceVentanilla;
		area.ventanillas->goToPos(indiceVentanilla - 1);
		Ventanilla ventana = area.ventanillas->getElement();



	}
		
}