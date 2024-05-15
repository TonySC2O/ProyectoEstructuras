#pragma once
#include <iostream>
#include "elementos.h"

using namespace std;

void mostrarMenuPrincipal() {
    cout << "----- Menu Principal -----" << endl;
    cout << "1. Estado de las colas" << endl;
    cout << "2. Tiquetes" << endl;
    cout << "3. Atender" << endl;
    cout << "4. Administracion" << endl;
    cout << "5. Estadisticas del sistema" << endl;
    cout << "6. Salir" << endl;
	cout << "Seleccione una opcion: ";
}

void mostrarMenuTiquetes() {
	cout << "----- Menu Tiquetes -----" << endl;
	cout << "1. Colocar Tiquete" << endl;
	cout << "2. Regresar" << endl;
	cout << "Seleccione una opcion: ";
}

void mostrarMenuAdministracion() {
	cout << "----- Menu Administracion -----" << endl;
	cout << "1. Submenu Tipos de Usuario" << endl;
	cout << "2. Submenu areas" << endl;
	cout << "3. Submenu Servicios Disponibles" << endl;
	cout << "4. Limpiar Colas y Estadisticas" << endl;
	cout << "5. Regresar" << endl;
	cout << "Seleccione una opcion: ";
}
void mostrarSubmenuTiposUsuario() {
	cout << "----- Submenu Tipos de Usuario -----" << endl;
	cout << "1. Agregar" << endl;
	cout << "2. Eliminar" << endl;
	cout << "3. Regresar" << endl;
	cout << "Seleccione una opcion: ";
}

void mostrarSubmenuAreas() {
	cout << "----- Submenu areas -----" << endl;
	cout << "1. Agregar" << endl;
	cout << "2. Modificar Cantidad de Ventanillas" << endl;
	cout << "3. Eliminar" << endl;
	cout << "4. Regresar" << endl;
	cout << "Seleccione una opcion: ";
}

void mostrarSubmenuServiciosDisponibles() {
	cout << "----- Submenu Servicios Disponibles -----" << endl;
	cout << "1. Agregar" << endl;
	cout << "2. Eliminar" << endl;
	cout << "3. Reordenar" << endl;
	cout << "4. Regresar" << endl;
	cout << "Seleccione una opcion: ";
}

void menuTiquetes() {
	int opcionTiquetes = 0;
	string codigoArea = "", tipoUsuario = "", tipoServicio = "";
	int prioridadFinal = 0, horaSolicitud = 0, opcionEliminar = 0, posicion = 0, opcionServicio = 0, opcionUsuario = 0;
	time_t t;
	struct tm* tiempo;
	bool existe = false;

	do {
		mostrarMenuTiquetes();
		cin >> opcionTiquetes;
		verificarCin();

		switch (opcionTiquetes) {
		case 1:
			// Solicitar información para colocar un tiquete...
			if (servicios->getSize() == 0)
			{
				throw runtime_error("No existen servicios.");
			}

			listaTipoUsuarios();
			cout << "Seleccione tipo de usuario: ";
			cin >> opcionUsuario;
			verificarCin();
			tiposUsuario->goToPos(opcionUsuario - 1);
			tipoUsuario = tiposUsuario->getElement().nombre;
			
			listaServicios();
			cout << "Seleccione un servicio: ";
			cin >> opcionServicio;
			verificarCin();
			servicios->goToPos(opcionServicio - 1);
			tipoServicio = servicios->getElement().nombre;
			codigoArea = servicios->getElement().codigoArea;

			t = time(0);
			tiempo = localtime(&t);
			horaSolicitud = tiempoASegundos(tiempo->tm_hour, tiempo->tm_min, tiempo->tm_sec);

			prioridadFinal = (tiposUsuario->getElement().prioridad * 10) + servicios->getElement().prioridad;

			colocarTiquete(codigoArea, tipoUsuario, tipoServicio, numGlobal, horaSolicitud, prioridadFinal);

			cout << "Tiquete generado con exito" << endl;
			cout << "Codigo de tiquete: " << (codigoArea + to_string(numGlobal)) << endl;
			cout << "Hora de llegada: " << segundosATiempo(horaSolicitud) << endl;
			cout << "Prioridad final: " << prioridadFinal << endl;
			cout << "Tipo de cliente: " << tipoUsuario << endl;
			cout << "Servicio Solicitado: " << tipoServicio << endl;
			cout << "Area asignada: Area " << codigoArea << endl;

			numGlobal++;
			break;
		case 2:
			// Regresar al menú principal
			break;
		default:
			cout << "Opción inválida. Por favor, seleccione una opción válida." << endl;
			break;
		}
	} while (opcionTiquetes != 2);
}

// Los métodos para los submenús mantienen la misma estructura y opciones que especificaste.
// Ahora implementaré los submenús restantes.

void submenuTiposUsuario() {
	int opcionSubmenuTiposUsuario = 0;
	string codigoUsuarioEliminar = "";

	do {
		mostrarSubmenuTiposUsuario();
		cin >> opcionSubmenuTiposUsuario;
		verificarCin();

		switch (opcionSubmenuTiposUsuario) {
		case 1:
			agregarTipoUsuario();
			break;
		case 2:
			// Solicitar información para eliminar un tipo de usuario...
			eliminarTipoUsuario();
			break;
		case 3:
			// Regresar al menú anterior
			break;
		default:
			cout << "Opción inválida. Por favor, seleccione una opción válida." << endl;
			break;
		}
	} while (opcionSubmenuTiposUsuario != 3);
}

void submenuAreas() {
	int opcionSubmenuAreas = 0;
	int nuevaCantidad = 0;
	string codigoAreaModificar = "", codigoAreaEliminar = "";

	do {
		mostrarSubmenuAreas();
		cin >> opcionSubmenuAreas;
		verificarCin();

		switch (opcionSubmenuAreas) {
		case 1:
			agregarArea();
			break;
		case 2:
			// Solicitar información para modificar la cantidad de ventanillas...
			cout << "Ingrese el codigo del área a modificar: ";
			cin >> codigoAreaModificar;
			cout << "Ingrese la nueva cantidad de ventanillas: ";
			cin >> nuevaCantidad;
			modificarCantidadVentanillas(codigoAreaModificar, nuevaCantidad);
			break;
		case 3:
			// Solicitar información para eliminar un área...
			cout << "Ingrese el indice del área que se encuentra a eliminar: ";
			cin >> codigoAreaEliminar;
			eliminarArea(codigoAreaEliminar);
			break;
		case 4:
			// Regresar al menú anterior
			break;
		default:
			cout << "Opción inválida. Por favor, seleccione una opción válida." << endl;
			break;
		}
	} while (opcionSubmenuAreas != 4);
}

void submenuServiciosDisponibles() {
	int opcionSubmenuServicios = 0;

	do {
		mostrarSubmenuServiciosDisponibles();
		cin >> opcionSubmenuServicios;
		verificarCin();

		switch (opcionSubmenuServicios) {
		case 1:
			agregarServicio();
			break;
		case 2:
			// Solicitar información para eliminar un servicio...
			eliminarServicio();
			break;
		case 3:
			// Lógica para reordenar servicios...
			reordenarServicios();
			break;
		case 4:
			// Regresar al menú anterior
			break;
		default:
			cout << "Opción inválida. Por favor, seleccione una opción válida." << endl;
			break;
		}
	} while (opcionSubmenuServicios != 4);
}

void menuAdministracion() {
	int opcionAdmin;
	do {
		mostrarMenuAdministracion();
		cin >> opcionAdmin;
		verificarCin();

		switch (opcionAdmin) {
		case 1:
			// Abre el submenú de tipos de usuario
			submenuTiposUsuario();
			break;
		case 2:
			// Abre el submenú de áreas
			submenuAreas();
			break;
		case 3:
			// Abre el submenú de servicios disponibles
			submenuServiciosDisponibles();
			break;
		case 4:
			limpiarColasYEstadisticas(); // Llamar a la función para limpiar colas y estadísticas
			break;
		case 5:
			// Regresar al menú principal
			break;
		default:
			cout << "Opción inválida. Por favor, seleccione una opción válida." << endl;
			break;
		}
	} while (opcionAdmin != 5);
}

void atender() {
	atenderTiquete();
}