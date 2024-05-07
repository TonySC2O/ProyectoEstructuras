#define DEFAULT_MAX_PRIORITY 5

#include <iostream>
#include <string>
#include <cstdlib>
#include "./Apoyo/SortedArrayList.h"
#include "./Apoyo/LinkedPriorityQueue.h"
#include "./Apoyo/ArrayList.h"
#include "./Apoyo/LinkedList.h"
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
		os << tipo.nombre << ", " << tipo.descripcion << ", Prioridad: " << tipo.prioridad <<  endl;
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
	int horaSolicitud;
	int prioridadFinal;

	Tiquete() : codigoArea(""), tipoUsuarioAsociado(""), tipoServicioAsociado(""), numGlobal(0), horaSolicitud(0), prioridadFinal(0) {}
	Tiquete(string codi, string usua, string serv, int nume, int hora, int prio) : codigoArea(codi), tipoUsuarioAsociado(usua), tipoServicioAsociado(serv), numGlobal(nume), horaSolicitud(hora), prioridadFinal(prio) {}

	friend std::ostream& operator<<(std::ostream& os, const Tiquete& tiquete) {
		os << tiquete.codigoArea << tiquete.numGlobal << ", hora de solicitud: " << tiquete.horaSolicitud << ", prioridad: " << tiquete.prioridadFinal;
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
			Ventanilla ventana((codigo + to_string(i+1)));
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

void limpiarColasYEstadisticas() {
	areas->goToStart();
	for (int i = 0; i < areas->getSize(); i++) {
		areas->getElement().colaTiquetes->clear();
	}
}
void agregarTipoUsuario() {
	string nombre, descripcion;
	int prioridad;
	cout << "Ingrese el nombre del tipo de usuario: ";
	cin >> nombre;
	cout << "Ingrese la descripci�n del tipo de usuario: ";
	cin >> descripcion;
	cout << "Ingrese la prioridad del tipo de usuario: ";
	cin >> prioridad;
	TipoUsuario nuevoTipo(nombre, descripcion, prioridad);
	tiposUsuario->append(nuevoTipo);
}

void agregarServicio() {
	string nombre, descripcion, codigoArea;
	int prioridad;
	cout << "Ingrese el nombre del servicio: ";
	cin >> nombre;
	cout << "Ingrese la descripci�n del servicio: ";
	cin >> descripcion;
	cout << "Ingrese la prioridad del servicio: ";
	cin >> prioridad;
	cout << "Ingrese el c�digo del �rea asociada al servicio: ";
	cin >> codigoArea;
	Servicio nuevoServicio(nombre, descripcion, prioridad, codigoArea);
	servicios->append(nuevoServicio);
}
void agregarArea() {
	string descripcion, codigo;
	int cantidadVentanillas;
	cout << "Ingrese la descripci�n del �rea: ";
	cin >> descripcion;
	cout << "Ingrese el c�digo del �rea: ";
	cin >> codigo;
	cout << "Ingrese la cantidad de ventanillas: ";
	cin >> cantidadVentanillas;
	Area nuevaArea(descripcion, codigo, cantidadVentanillas);
	areas->append(nuevaArea);
}
void eliminarServicio() {
	cout << "Lista de servicios disponibles:" << endl;
	for (int i = 0; i < servicios->getSize(); i++) {
		cout << i + 1 << ". " << servicios->getElement() << endl;
		servicios->next();
	}
	int opcion;
	cout << "Seleccione el n�mero del servicio que desea eliminar: ";
	cin >> opcion;
	servicios->goToPos(opcion - 1);
	servicios->remove();
	servicios->goToStart(); // Regresar al inicio de la lista
}

void reordenarServicios() {
	cout << "Lista de servicios disponibles:" << endl;
	for (int i = 0; i < servicios->getSize(); i++) {
		cout << i + 1 << ". " << servicios->getElement() << endl;
		servicios->next();
	}
	int numServicio, nuevaPosicion;
	cout << "Ingrese el n�mero del servicio que desea reordenar: ";
	cin >> numServicio;
	cout << "Ingrese la nueva posici�n del servicio: ";
	cin >> nuevaPosicion;
	servicios->goToPos(numServicio - 1);
	Servicio servicio = servicios->remove();
	servicios->goToPos(nuevaPosicion - 1);
	servicios->insert(servicio);
}
void mostrarMenuPrincipal() {
	cout << "----- Men� Principal -----" << endl;
	cout << "1. Estado de las colas" << endl;
	cout << "2. Tiquetes" << endl;
	cout << "3. Atender" << endl;
	cout << "4. Administraci�n" << endl;
	cout << "5. Estad�sticas del sistema" << endl;
	cout << "6. Salir" << endl;
	cout << "Seleccione una opci�n: ";
}

void mostrarMenuTiquetes() {
	cout << "----- Men� Tiquetes -----" << endl;
	cout << "1. Colocar Tiquete" << endl;
	cout << "2. Eliminar Tiquetes de la Cola" << endl;
	cout << "3. Regresar" << endl;
	cout << "Seleccione una opci�n: ";
}

void mostrarMenuAdministracion() {
	cout << "----- Men� Administraci�n -----" << endl;
	cout << "1. Submen� Tipos de Usuario" << endl;
	cout << "2. Submen� �reas" << endl;
	cout << "3. Submen� Servicios Disponibles" << endl;
	cout << "4. Limpiar Colas y Estad�sticas" << endl;
	cout << "5. Regresar" << endl;
	cout << "Seleccione una opci�n: ";
}
void mostrarSubmenuTiposUsuario() {
	cout << "----- Submen� Tipos de Usuario -----" << endl;
	cout << "1. Agregar" << endl;
	cout << "2. Eliminar" << endl;
	cout << "3. Regresar" << endl;
	cout << "Seleccione una opci�n: ";
}

void mostrarSubmenuAreas() {
	cout << "----- Submen� �reas -----" << endl;
	cout << "1. Agregar" << endl;
	cout << "2. Modificar Cantidad de Ventanillas" << endl;
	cout << "3. Eliminar" << endl;
	cout << "4. Regresar" << endl;
	cout << "Seleccione una opci�n: ";
}

void mostrarSubmenuServiciosDisponibles() {
	cout << "----- Submen� Servicios Disponibles -----" << endl;
	cout << "1. Agregar" << endl;
	cout << "2. Eliminar" << endl;
	cout << "3. Reordenar" << endl;
	cout << "4. Regresar" << endl;
	cout << "Seleccione una opci�n: ";
}
int main() {
	int opcionPrincipal, numGlobal, prioridadFinal, horaSolicitud, opcionTiquetes, opcionAdmin, opcionEliminar, posicion, opcionModificarVentanillas, codigoAreaModificar, nuevaCantidad, codigoAreaEliminar, codigoUsuarioEliminar;
	string tipoUsuario, tipoServicio, codigoArea;
	do {
		mostrarMenuPrincipal();
		cin >> opcionPrincipal;

		switch (opcionPrincipal) {
		case 1:
			verColas(); // Llamar a la funci�n para mostrar el estado de las colas
			break;
		case 2:
			opcionTiquetes = 0; // Reiniciar opcionTiquetes
			do {
				mostrarMenuTiquetes();
				cin >> opcionTiquetes;

				switch (opcionTiquetes) {
				case 1:
					// Solicitar informaci�n para colocar un tiquete...
					cout << "Ingrese c�digo de �rea: ";
					cin >> codigoArea;
					cout << "Ingrese tipo de usuario: ";
					cin >> tipoUsuario;
					cout << "Ingrese tipo de servicio: ";
					cin >> tipoServicio;
					cout << "Ingrese n�mero global: ";
					cin >> numGlobal;
					cout << "Ingrese hora de solicitud: ";
					cin >> horaSolicitud;
					cout << "Ingrese prioridad final: ";
					cin >> prioridadFinal;
					colocarTiquete(codigoArea, tipoUsuario, tipoServicio, numGlobal, horaSolicitud, prioridadFinal);
					break;
				case 2:
					// Solicitar informaci�n para eliminar tiquetes de las colas...
					cout << "�Qu� desea eliminar?" << endl;
					cout << "1. Tipo de usuario" << endl;
					cout << "2. Tipo de servicio" << endl;
					cout << "Seleccione una opci�n: ";
					cin >> opcionEliminar;
					cout << "Ingrese la posici�n del elemento: ";
					cin >> posicion;
					eliminarTicketsCola(opcionEliminar, posicion);
					break;
				case 3:
					// Regresar al men� principal
					break;
				default:
					cout << "Opci�n inv�lida. Por favor, seleccione una opci�n v�lida." << endl;
					break;
				}
			} while (opcionTiquetes != 3);
			break;
		case 3:
			// L�gica para atender tiquetes...
			break;
		case 4:
			opcionAdmin = 0; // Reiniciar opcionAdmin
			do {
				mostrarMenuAdministracion();
				cin >> opcionAdmin;

				switch (opcionAdmin) {
				case 1:
					// Abre el submen� de tipos de usuario
					int opcionSubmenuTiposUsuario;
					do {
						mostrarSubmenuTiposUsuario();
						cin >> opcionSubmenuTiposUsuario;

						switch (opcionSubmenuTiposUsuario) {
						case 1:
							agregarTipoUsuario();
							break;
						case 2:
							// Solicitar informaci�n para eliminar un tipo de usuario...
							cout << "Ingrese el nombre del tipo de usuario a eliminar: ";
							cin >> codigoUsuarioEliminar;
							eliminarTipoUsuario(codigoUsuarioEliminar);
							break;
						case 3:
							// Regresar al men� anterior
							break;
						default:
							cout << "Opci�n inv�lida. Por favor, seleccione una opci�n v�lida." << endl;
							break;
						}
					} while (opcionSubmenuTiposUsuario != 3);
					break;
				case 2:
					// Abre el submen� de �reas
					int opcionSubmenuAreas;
					do {
						mostrarSubmenuAreas();
						cin >> opcionSubmenuAreas;

						switch (opcionSubmenuAreas) {
						case 1:
							agregarArea();
							break;
						case 2:
							// Solicitar informaci�n para modificar la cantidad de ventanillas...
							cout << "Ingrese el c�digo del �rea a modificar: ";
							cin >> codigoAreaModificar;
							cout << "Ingrese la nueva cantidad de ventanillas: ";
							cin >> nuevaCantidad;
							modificarCantidadVentanillas(codigoAreaModificar, nuevaCantidad);
							break;
						case 3:
							// Solicitar informaci�n para eliminar un �rea...
							cout << "Ingrese el c�digo del �rea a eliminar: ";
							cin >> codigoAreaEliminar;
							eliminarArea(codigoAreaEliminar);
							break;
						case 4:
							// Regresar al men� anterior
							break;
						default:
							cout << "Opci�n inv�lida. Por favor, seleccione una opci�n v�lida." << endl;
							break;
						}
					} while (opcionSubmenuAreas != 4);
					break;
				case 3:
					// Abre el submen� de servicios disponibles
					int opcionSubmenuServicios;
					do {
						mostrarSubmenuServiciosDisponibles();
						cin >> opcionSubmenuServicios;

						switch (opcionSubmenuServicios) {
						case 1:
							agregarServicio();
							break;
						case 2:
							// Solicitar informaci�n para eliminar un servicio...
							eliminarServicio();
							break;
						case 3:
							// L�gica para reordenar servicios...
							reordenarServicios();
							break;
						case 4:
							// Regresar al men� anterior
							break;
						default:
							cout << "Opci�n inv�lida. Por favor, seleccione una opci�n v�lida." << endl;
							break;
						}
					} while (opcionSubmenuServicios != 4);
					break;
				case 4:
					limpiarColasYEstadisticas(); // Llamar a la funci�n para limpiar colas y estad�sticas
					break;
				case 5:
					// Regresar al men� principal
					break;
				default:
					cout << "Opci�n inv�lida. Por favor, seleccione una opci�n v�lida." << endl;
					break;
				}
			} while (opcionAdmin != 5);
			break;
		case 5:
			// L�gica para mostrar estad�sticas del sistema...
			break;
		case 6:
			cout << "Saliendo del programa..." << endl;
			break;
		default:
			cout << "Opci�n inv�lida. Por favor, seleccione una opci�n v�lida." << endl;
			break;
		}
	} while (opcionPrincipal != 6);

	return 0;
}

