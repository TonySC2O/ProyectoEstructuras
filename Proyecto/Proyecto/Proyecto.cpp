//Esto es para usar localtime sin problemas
#pragma warning(disable : 4996)

#define DEFAULT_MAX_PRIORITY 5

#include <iostream>
#include <string>
#include <cstdlib>
#include <stdexcept>
#include "./Apoyo/SortedArrayList.h"
#include "./Apoyo/LinkedPriorityQueue.h"
#include "./Apoyo/ArrayList.h"
#include "./Apoyo/LinkedList.h"
#include "./Recursos/menus.h"
#include "./Recursos/elementos.h"
#include "./Recursos/tiempo.h"

using namespace std;

int main() {
	int opcionPrincipal;
	do {
		try
		{
			mostrarMenuPrincipal();
			cin >> opcionPrincipal;

			switch (opcionPrincipal) {
			case 1:
				verColas(); // Llamar a la función para mostrar el estado de las colas
				break;
			case 2:
				menuTiquetes();
				break;
			case 3:
				atenderTiquete();
				break;
			case 4:
				menuAdministracion();
				break;
			case 5:
				obtenerEstadisticas();// Lógica para mostrar estadísticas del sistema...
				break;
			case 6:
				cout << "Saliendo del programa..." << endl;
				break;
			default:
				cout << "Opción inválida. Por favor, seleccione una opción válida." << endl;
				break;
			}
		}
		catch (const std::exception& e)
		{
			cout << "Error: " << e.what() << endl;
		}
	} while (opcionPrincipal != 6);
}

