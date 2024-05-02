
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

int main()
{
	int numGlobal = 100;

	try
	{

		//Administración del sistema.
		
		// Agregar nuevo tipo de Usuario:
		// Se crea nuevo usuario (string nombre, string descripción, int prioridad)
		TipoUsuario nuevoUsuario("Nombre1", "Descripción", 1);
		TipoUsuario nuevoUsuario2("Nombre2", "Descripción", 0);
		TipoUsuario nuevoUsuario3("Nombre3", "Descripción", 2);

		// Se añade a la listas de tipos de usuario:
		tiposUsuario->insert(nuevoUsuario);
		tiposUsuario->insert(nuevoUsuario2);
		tiposUsuario->insert(nuevoUsuario3);

		// Agregar nueva Area:
		// Se crea Area (string descricpion, string codigo, int cantidadVentanas)
		Area nuevaArea("Descripción", "C", 4);
		Area nuevaArea2("Descripción", "B", 3);
		Area nuevaArea3("Descripción", "A", 2);
		// Se añade a la listas de areas:
		areas->append(nuevaArea);
		areas->append(nuevaArea2);
		areas->append(nuevaArea3);

		// Agregar nuevo Servicio:
		// Se crea Servicio (string nombre, string descripcion, int prioridad, string codigoArea)
		Servicio nuevoServicio("Servicio1", "Descripción", 1, nuevaArea.codigo);
		Servicio nuevoServicio2("Servicio2", "Descripción", 0, nuevaArea2.codigo);
		Servicio nuevoServicio3("Servicio3", "Descripción", 2, nuevaArea3.codigo);

		// Se añade a la listas de Servicios:
		servicios->append(nuevoServicio);
		servicios->append(nuevoServicio2);
		servicios->append(nuevoServicio3);

		// Para generar un tiquete debe preguntarle al usuario el tipo de usuario y el servicio
		// (string codigoArea, string TipoUsuario, string Servicio, int NumeroGlobal, int HoraSolicitada, int PrioridadFinal)
		// Cada que se crea un tiquete el numero global incrementa.
		// Al preguntarle al usuario se puede utilizar el input para usar .goToPos(input - 1) para encontrar usuario y servicio.
		Tiquete ticket(nuevoServicio.codigoArea, nuevoUsuario.nombre, nuevoServicio.nombre, numGlobal, 7, (nuevoUsuario.prioridad * 10 + nuevoServicio.prioridad));
		numGlobal++;
		Tiquete ticket2(nuevoServicio2.codigoArea, nuevoUsuario3.nombre, nuevoServicio2.nombre, numGlobal, 7, (nuevoUsuario3.prioridad * 10 + nuevoServicio2.prioridad));
		numGlobal++;

		// Luego se inserta en la cola del area en la que se da ese servicio.
		colocarTiquete(ticket);
		colocarTiquete(ticket2);


		// Eliminar Area:
		// Cuando se elimina un area todos los servicios que pertenecen a la misma son
		// borrados, por lo que hay que guardar el codigo del area eliminada para buscar
		// en la lista de servicios cuales eliminar.

		// se dispersa un menu con las opciones
		areas->goToStart();
		for (int i = 0; i < areas->getSize(); i++)
		{
			cout << (i + 1) << ". Area " << areas->getElement().codigo << endl;
			areas->next();
		}
		cout << endl;

		// con el output del usuario - 1 se elimina el area
		eliminarArea(2 - 1);

		areas->print();

		// Eliminar servicio:
		// mediante el menú se le pide al usuario que seleccione
		// un usuario a eliminar mediante una lista.

		// Código para generar la lista:
		servicios->goToStart();
		for (int i = 0; i < servicios->getSize(); i++)
		{
			cout << (i + 1) << ". " << servicios->getElement().nombre << endl;
			servicios->next();
		}
		cout << endl;

		eliminarTicketsCola(2, 2-1);
		verColas();

		// Eliminar usuario:
		// mediante el menú se le pide al usuario que seleccione
		// un usuario a eliminar mediante una lista.
		
		// Código para generar la lista:
		tiposUsuario->goToStart();
		for (int i = 0; i < tiposUsuario->getSize(); i++)
		{
			cout << (i + 1) << ". " << tiposUsuario->getElement().nombre << endl;
			tiposUsuario->next();
		}
		cout << endl;

		eliminarTicketsCola(1, 2-1);
		verColas();


	}
	catch (const std::exception& ex)
	{
		cout << "Error: " << ex.what() << endl;
	}
}

