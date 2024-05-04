#define DEFAULT_MAX_PRIORITY 5

#include <iostream>
#include <string>
#include "./Apoyo/SortedArrayList.h"
#include "./Apoyo/LinkedPriorityQueue.h"
#include "./Apoyo/ArrayList.h"
#include "./Apoyo/LinkedList.h"

using namespace std;

// Estructura de tipos de usuario, posee el nombre del tipo, una descripción y su prioridad.
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

	// Dicta que se muestra al realizar un console out del objeto.
	friend std::ostream& operator<<(std::ostream& os, const Tiquete& tiquete) {
		os << tiquete.codigoArea << tiquete.numGlobal << ", hora de solicitud: " << tiquete.horaSolicitud << ", prioridad: " << tiquete.prioridadFinal;
		return os;
	}

	// Sobrecarga del operador >= para evaluar prioridad.
	bool operator>=(const Tiquete& otro) const {
		return prioridadFinal >= otro.prioridadFinal;
	}

	// Sobrecarga del operador >= para evaluar prioridad.
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
void colocarTiquete(Tiquete ticket) {
	areas->goToStart();
	for (int i = 0; i < areas->getSize(); i++)
	{
		if (areas->getElement().codigo == ticket.codigoArea)
		{
			areas->getElement().colaTiquetes->insert(ticket, ticket.prioridadFinal);
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

void mostrarMenuPrincipal() {
	cout << "----- Menú Principal -----" << endl;
	cout << "1. Estado de las colas" << endl;
	cout << "2. Tiquetes" << endl;
	cout << "3. Atender" << endl;
	cout << "4. Administración" << endl;
	cout << "5. Estadísticas del sistema" << endl;
	cout << "6. Salir" << endl;
	cout << "Seleccione una opción: ";
}

void mostrarMenuTiquetes() {
	cout << "----- Menú Tiquetes -----" << endl;
	cout << "1. Seleccionar tipo de cliente y servicio" << endl;
	cout << "2. Regresar" << endl;
	cout << "Seleccione una opción: ";
}

void mostrarMenuAdministracion() {
	cout << "----- Menú Administración -----" << endl;
	cout << "1. Tipos de usuario" << endl;
	cout << "2. Áreas" << endl;
	cout << "3. Servicios disponibles" << endl;
	cout << "4. Limpiar colas y estadísticas" << endl;
	cout << "5. Regresar" << endl;
	cout << "Seleccione una opción: ";
}

void mostrarMenuTiposUsuario() {
	cout << "----- Menú Tipos de Usuario -----" << endl;
	cout << "1. Agregar" << endl;
	cout << "2. Eliminar" << endl;
	cout << "3. Regresar" << endl;
	cout << "Seleccione una opción: ";
}

// Funciones para manejar la lógica de cada opción del menú...

int main() {
	int opcionPrincipal;

	do {
		system("cls"); // Limpia la pantalla (solo funciona en sistemas Windows, para otros sistemas puedes usar "clear")
		mostrarMenuPrincipal();
		cin >> opcionPrincipal;

		switch (opcionPrincipal) {
		case 1:
			// Lógica para mostrar el estado de las colas
			// Esperar a que el usuario presione alguna tecla para regresar al menú principal
			system("pause");
			break;
		case 2:
			int opcionTiquetes;
			do {
				system("cls");
				mostrarMenuTiquetes();
				cin >> opcionTiquetes;

				switch (opcionTiquetes) {
				case 1:
					// Lógica para seleccionar tipo de cliente y servicio
					break;
				case 2:
					// Regresar al menú principal de tiquetes
					break;
				default:
					cout << "Opción inválida. Por favor, seleccione una opción válida." << endl;
					break;
				}
			} while (opcionTiquetes != 2);
			break;
		case 3:
			// Lógica para atender
			break;
		case 4:
			int opcionAdmin;
			do {
				system("cls");
				mostrarMenuAdministracion();
				cin >> opcionAdmin;

				switch (opcionAdmin) {
				case 1:
					int opcionTiposUsuario;
					do {
						system("cls");
						mostrarMenuTiposUsuario();
						cin >> opcionTiposUsuario;

						switch (opcionTiposUsuario) {
						case 1:
							// Lógica para agregar tipo de usuario
							break;
						case 2:
							// Lógica para eliminar tipo de usuario
							break;
						case 3:
							// Regresar al menú principal de administración
							break;
						default:
							cout << "Opción inválida. Por favor, seleccione una opción válida." << endl;
							break;
						}
					} while (opcionTiposUsuario != 3);
					break;
				case 2:
					// Lógica para áreas
					break;
				case 3:
					// Lógica para servicios disponibles
					break;
				case 4:
					// Lógica para limpiar colas y estadísticas
					break;
				case 5:
					// Regresar al menú principal
					break;
				default:
					cout << "Opción inválida. Por favor, seleccione una opción válida." << endl;
					break;
				}
			} while (opcionAdmin != 5);
			break;
		case 5:
			// Lógica para mostrar estadísticas del sistema
			// Esperar a que el usuario presione alguna tecla para regresar al menú principal
			system("pause");
			break;
		case 6:
			cout << "Saliendo del programa..." << endl;
			break;
		default:
			cout << "Opción inválida. Por favor, seleccione una opción válida." << endl;
			break;
		}
	} while (opcionPrincipal != 6);

	return 0;
}

