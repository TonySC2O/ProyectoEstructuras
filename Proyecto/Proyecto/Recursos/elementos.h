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
		os << tiquete.codigoArea << tiquete.numGlobal << ", " << segundosATiempo(tiquete.horaSolicitudEnSegundos);
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
	string ultimoTiqueteAtendido = "None";
	int horaUltimoTiqueteAtendido = 0;
	int cantidadPersonas = 0;
	Tiquete tiquete;

	Ventanilla() : nombre(""), ultimoTiqueteAtendido("None"), horaUltimoTiqueteAtendido(0), cantidadPersonas(0) {}
	Ventanilla(string nomb) : nombre(nomb), ultimoTiqueteAtendido("None"), horaUltimoTiqueteAtendido(0), cantidadPersonas(0) {}

	// Dicta que se muestra al realizar un console out del objeto.
	friend std::ostream& operator<<(std::ostream& os, const Ventanilla& ventanilla) {
		os << "(" << ventanilla.nombre << ", " << ventanilla.ultimoTiqueteAtendido << ", " << segundosATiempo(ventanilla.horaUltimoTiqueteAtendido) << ")";
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
	int tiempoEspera = 0;
	int tiquetesAtendidos = 0;
	ArrayList<Ventanilla>* ventanillas;
	LinkedPriorityQueue<Tiquete>* colaTiquetes;

	Area() : descripcion(""), codigo(""), tiempoEspera(0), tiquetesAtendidos(0), ventanillas(new ArrayList<Ventanilla>()), colaTiquetes(new LinkedPriorityQueue<Tiquete>(DEFAULT_MAX_PRIORITY * 10 + DEFAULT_MAX_PRIORITY)) {}
	Area(string desc, string codi, int vent) : descripcion(desc), codigo(codi), tiempoEspera(0), tiquetesAtendidos(0), ventanillas(new ArrayList<Ventanilla>(vent)), colaTiquetes(new LinkedPriorityQueue<Tiquete>(DEFAULT_MAX_PRIORITY * 10 + DEFAULT_MAX_PRIORITY)) {
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

void verificarCin() {
	if (cin.fail())
	{
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		throw runtime_error("opcion no valida.");
	}
}

bool areaExiste(string codigo) {
	areas->goToStart();
	for (int i = 0; i < areas->getSize(); i++)
	{
		if (areas->getElement().codigo == codigo)
		{
			return true;
		}
		areas->next();
	}
	return false;
}

void listaServicios() {
	cout << "Lista de servicios disponibles:" << endl;
	servicios->goToStart();
	for (int i = 0; i < servicios->getSize(); i++) {
		cout << i + 1 << ". " << servicios->getElement();
		servicios->next();
	}
}

void listaTipoUsuarios() {
	cout << "Lista de tipos de usuario:" << endl;
	tiposUsuario->goToStart();
	for (int i = 0; i < tiposUsuario->getSize(); i++) {
		cout << i + 1 << ". " << tiposUsuario->getElement();
		tiposUsuario->next();
	}
}

void verColas() {
	areas->goToStart();
	for (int i = 0; i < areas->getSize(); i++)
	{
		cout << "====================================" << endl;
		cout << "Area " << areas->getElement().codigo << ":" << endl;
		cout << "Ventanillas: " << endl;
		areas->getElement().ventanillas->print();
		cout << "Cola de espera: " << endl;
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

	tiposUsuario->goToStart();
	for (int i = 0; i < tiposUsuario->getSize(); i++)
	{
		if (tiposUsuario->getElement().nombre == nombre)
		{
			throw runtime_error("Otro tipo de usuario ya posee ese nombre.");
		}
		tiposUsuario->next();
	}

	cout << "Ingrese la descripcion del tipo de usuario: ";
	getline(cin, descripcion);
	cout << "Ingrese la prioridad del tipo de usuario: ";
	cin >> prioridad;
	verificarCin();

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
	getline(cin, descripcion);
	cout << "Ingrese la prioridad del servicio: ";
	cin >> prioridad;
	verificarCin();
	cout << "Ingrese el codigo del area asociada al servicio: ";
	cin >> codigoArea;
	verificarCin();

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

	if (!areaExiste(codigoArea))
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
	verificarCin();
	
	if (codigo.size() > 1)
	{
		throw runtime_error("El codigo de area debe ser una letra.");
	}

	areas->goToStart();
	for (int i = 0; i < areas->getSize(); i++)
	{
		if (areas->getElement().codigo == codigo)
		{
			throw runtime_error("Codigo de area ya utilizado");
		}
		areas->next();
	}

	cout << "Ingrese la descripcion del area: ";
	cin.ignore();
	getline(cin, descripcion);

	cout << "Ingrese la cantidad de ventanillas: ";
	cin >> cantidadVentanillas;
	verificarCin();
	Area nuevaArea(descripcion, codigo, cantidadVentanillas);
	areas->append(nuevaArea);
}

void eliminarTipoUsuario() {
	int opcion = 0;
	listaTipoUsuarios();
	cout << "Seleccione el tipo de usuario a eliminar: ";
	cin >> opcion;
	verificarCin();

	tiposUsuario->goToPos(opcion - 1);
	TipoUsuario tempUsuario = tiposUsuario->remove();

	areas->goToStart();
	for (int i = 0; i < areas->getSize(); i++) {
		int sizeCola = areas->getElement().colaTiquetes->getSize(); 
		if (areas->getElement().colaTiquetes->isEmpty())
			continue;
		for (int j = 0; j < sizeCola; j++) {
			Tiquete tiquetTemp = areas->getElement().colaTiquetes->removeMin();
			if (tiquetTemp.tipoUsuarioAsociado != tempUsuario.nombre) {
				areas->getElement().colaTiquetes->insert(tiquetTemp, tiquetTemp.prioridadFinal);
			}
		}
		areas->next();
	}
	tiposUsuario->goToStart();
}

void eliminarServicio() {
	listaServicios();
	int opcion;
	cout << "Seleccione el servicio que desea eliminar: ";
	cin >> opcion;
	verificarCin();
	servicios->goToPos(opcion - 1);
	Servicio tempServicio = servicios->remove();

	areas->goToStart();
	for (int i = 0; i < areas->getSize(); i++) {
		int sizeCola = areas->getElement().colaTiquetes->getSize();
		if (areas->getElement().colaTiquetes->isEmpty())
			continue;
		
		for (int j = 0; j < sizeCola; j++) {
			Tiquete tiquetTemp = areas->getElement().colaTiquetes->removeMin();
			if (tiquetTemp.tipoServicioAsociado != tempServicio.nombre) {
				areas->getElement().colaTiquetes->insert(tiquetTemp, tiquetTemp.prioridadFinal);
			}
		}
		areas->next();
	}
	servicios->goToStart(); // Regresar al inicio de la lista
}

void eliminarArea(string codigo) {

	if (!areaExiste(codigo))
	{
		throw runtime_error("area no encontrada en el sistema.");
	}

	int opcion;
	cout << "Desea eliminar esta area? 1. Si, 2. No";
	cin >> opcion;

	if (opcion == 1)
	{
		Area areaTemp = areas->remove();

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

void modificarCantidadVentanillas(string codigo, int nuevaCantidad) {

	if (!areaExiste(codigo))
	{
		throw runtime_error("area no encontrada en el sistema.");
	}

	Area area = areas->getElement(); // Obtener el elemento directamente, no como referencia
	int cantidadVentanillas = area.ventanillas->getSize();

	// Eliminar las ventanillas actuales
	area.ventanillas->goToStart();
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
	listaServicios();
	int numServicio, nuevaPosicion;
	cout << "Ingrese el numero del servicio que desea reordenar: ";
	cin >> numServicio;
	verificarCin();
	cout << "Ingrese la nueva posicion del servicio: ";
	cin >> nuevaPosicion;
	verificarCin();
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
	verificarCin();

	if (!areaExiste(codigo))
	{
		throw runtime_error("area no encontrada en el sistema.");
	}

	area = areas->getElement();
	cout << "El area tiene " << area.ventanillas->getSize() << " ventanillas, ingrese la ventanilla a atender. " << endl;
	cout << "El indice inicia en 1" << endl;
	cin >> indiceVentanilla;
	verificarCin();
	if (indiceVentanilla > area.ventanillas->getSize() || indiceVentanilla < 0) {
		cout << "La ventanilla ingresada no es valida. " << endl;
	}
	else {
		area.ventanillas->goToPos(indiceVentanilla - 1);
		Ventanilla ventana = area.ventanillas->getElement();
		Tiquete tiquete = area.colaTiquetes->removeMin();
		ventana.tiquete = tiquete;
		ventana.ultimoTiqueteAtendido = (tiquete.codigoArea + to_string(tiquete.numGlobal));
		time_t t = time(0);
		struct tm* tiempo = localtime(&t);
		ventana.horaUltimoTiqueteAtendido = tiempoASegundos(tiempo->tm_hour, tiempo->tm_min, tiempo->tm_sec);
		ventana.cantidadPersonas++;

		int espera = ventana.horaUltimoTiqueteAtendido - tiquete.horaSolicitudEnSegundos;
		cout << espera << endl;
		area.tiempoEspera = (area.tiempoEspera * area.tiquetesAtendidos + espera) / (area.tiquetesAtendidos + 1);
		area.tiquetesAtendidos++;
		cout << area.tiempoEspera << endl;
		cout << "Se asigno el tiquete al area pedido en la ventanilla ingresado. " << endl;
		cout << "cantidad de personas atendidas: " << ventana.cantidadPersonas << endl;
		cout << "Tiquete atendido: " << ventana.ultimoTiqueteAtendido << endl;
		cout << "Hora atendido: " << segundosATiempo(ventana.horaUltimoTiqueteAtendido) << endl;
	}
	
}
void obtenerEstadisticas() {
	// 1. Tiempo promedio de espera por area.
	cout << "1. Tiempo promedio de espera por area:" << endl;
	areas->goToStart();
	for (int i = 0; i < areas->getSize(); i++) {
		cout << "Area " << areas->getElement().codigo << ": " << segundosATiempo(areas->getElement().tiempoEspera) << " de espera" << endl;
		areas->next();
	}

	// 2. Cantidad de tiquetes dispensados por área.
	cout << "\n2. Cantidad de tiquetes dispensados por área:" << endl;
	areas->goToStart();
	for (int i = 0; i < areas->getSize(); i++) {
		cout << "Area " << areas->getElement().codigo << ": " << areas->getElement().colaTiquetes->getSize() << " tiquetes dispensados" << endl;
		areas->next();
	}

	// 3. Cantidad de tiquetes atendidos por ventanilla.
	cout << "\n3. Cantidad de tiquetes atendidos por ventanilla:" << endl;
	areas->goToStart();
	for (int i = 0; i < areas->getSize(); i++) {
		cout << "Area " << areas->getElement().codigo << ":" << endl;
		areas->getElement().ventanillas->goToStart();
		for (int j = 0; j < areas->getElement().ventanillas->getSize(); j++) {
			cout << "Ventanilla " << areas->getElement().ventanillas->getElement().nombre << ": " << areas->getElement().ventanillas->getElement().cantidadPersonas << " tiquetes atendidos." << endl;
			areas->getElement().ventanillas->next();
		}
		areas->next();
	}

	// 4. Cantidad de tiquetes solicitados por servicio.
	cout << "\n4. Cantidad de tiquetes solicitados por servicio:" << endl;
	servicios->goToStart();
	for (int i = 0; i < servicios->getSize(); i++) {
		int count = 0;
		areas->goToStart();
		for (int j = 0; j < areas->getSize(); j++) {
			LinkedPriorityQueue<Tiquete>* colaTiquetes = areas->getElement().colaTiquetes;
			colaTiquetes->print();
			for (int k = 0; k < colaTiquetes->getSize(); k++) {
				if (colaTiquetes->min().tipoServicioAsociado == servicios->getElement().nombre) {
					count++;
				}
			}
			areas->next();
		}
		cout << "Servicio " << servicios->getElement().nombre << ": " << count << " tiquetes solicitados." << endl;
		servicios->next();
	}

	// 5. Cantidad de tiquetes emitidos por cada tipo de usuario.
	cout << "\n5. Cantidad de tiquetes emitidos por cada tipo de usuario:" << endl;
	tiposUsuario->goToStart();
	for (int i = 0; i < tiposUsuario->getSize(); i++) {
		int count = 0;
		areas->goToStart();
		for (int j = 0; j < areas->getSize(); j++) {
			LinkedPriorityQueue<Tiquete>* colaTiquetes = areas->getElement().colaTiquetes;
			for (int k = 0; k < colaTiquetes->getSize(); k++) {
				if (colaTiquetes->min().tipoUsuarioAsociado == tiposUsuario->getElement().nombre) {
					count++;
				}
			}
			areas->next();
		}
		cout << "Tipo de Usuario " << tiposUsuario->getElement().nombre << ": " << count << " tiquetes emitidos." << endl;
		tiposUsuario->next();
	}
}
