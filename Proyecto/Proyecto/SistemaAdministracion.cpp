#include <iostream>
#include "Proyecto.cpp"
#include <ctime>
#include <cstdlib>
#include <stdexcept>
#include <string>
#include "./Apoyo/SortedArrayList.h"
#include "./Apoyo/LinkedPriorityQueue.h"
#include "./Apoyo/ArrayList.h"
#include "./Apoyo/LinkedList.h"

using namespace std;
using std::runtime_error;


void mostrarColas() {
    areas->goToStart();
    for (int i = 0; i < areas->getSize(); i++) {
        cout << "====================================" << endl;
        cout << "Area " << areas->getElement().codigo << " - Cantidad de ventanillas: " << areas->getElement().ventanillas->getSize() << endl;
        cout << "Cola de tiquetes:" << endl;
        areas->getElement().colaTiquetes->print();
        cout << "Ventanillas: " << endl;
        areas->getElement().ventanillas->goToStart(); // Usar ->
        for (int j = 0; j < areas->getElement().ventanillas->getSize(); j++) {
            cout << areas->getElement().ventanillas->getElement() << endl; // Usar ->
            areas->getElement().ventanillas->next(); // Usar ->
        }
        areas->next();
    }
    cout << "Presione una tecla para regresar al men� principal...";
    cin.ignore();
    cin.get();
}

void generarTiquete() {
    int opcionTipo, opcionServicio;
    string codigoArea, nombreTipoUsuario, nombreServicio;
    int horaSolicitud = 0; // Supongo que la hora de solicitud se mantiene fija en 0 por simplicidad

    // Mostrar lista de tipos de usuario y permitir al usuario elegir uno
    cout << "Tipos de usuario disponibles:" << endl;
    tiposUsuario->goToStart();
    for (int i = 0; i < tiposUsuario->getSize(); i++) {
        cout << (i + 1) << ". " << tiposUsuario->getElement().nombre << endl;
        tiposUsuario->next();
    }
    cout << "Seleccione el tipo de usuario: ";
    cin >> opcionTipo;
    tiposUsuario->goToPos(opcionTipo - 1);
    nombreTipoUsuario = tiposUsuario->getElement().nombre;

    // Mostrar lista de servicios disponibles y permitir al usuario elegir uno
    cout << "Servicios disponibles:" << endl;
    servicios->goToStart();
    for (int i = 0; i < servicios->getSize(); i++) {
        cout << (i + 1) << ". " << servicios->getElement().nombre << endl;
        servicios->next();
    }
    cout << "Seleccione el servicio: ";
    cin >> opcionServicio;
    servicios->goToPos(opcionServicio - 1);
    nombreServicio = servicios->getElement().nombre;
    codigoArea = servicios->getElement().codigoArea;

    // Generar el tiquete y colocarlo en la cola respectiva
    Tiquete nuevoTiquete(codigoArea, nombreTipoUsuario, nombreServicio, 0, horaSolicitud, (tiposUsuario->getElement().prioridad * 10 + servicios->getElement().prioridad));
    colocarTiquete(nuevoTiquete);

    // Mostrar informaci�n del tiquete generado
    cout << "Tiquete generado:" << endl;
    cout << "C�digo de �rea: " << nuevoTiquete.codigoArea << endl;
    cout << "Tipo de usuario: " << nuevoTiquete.tipoUsuarioAsociado << endl;
    cout << "Servicio: " << nuevoTiquete.tipoServicioAsociado << endl;
    cout << "N�mero global: " << nuevoTiquete.numGlobal << endl;
    cout << "Hora de solicitud: " << nuevoTiquete.horaSolicitud << endl;
    cout << "Prioridad final: " << nuevoTiquete.prioridadFinal << endl;

    cout << "Presione una tecla para regresar al men� principal...";
    cin.ignore();
    cin.get();
}

void atenderTiquete() {
    string area;
    int numVentanilla;
    bool tiqueteEncontrado = false;

    // Mostrar lista de �reas y permitir al usuario elegir una
    cout << "�reas disponibles:" << endl;
    areas->goToStart();
    for (int i = 0; i < areas->getSize(); i++) {
        cout << (i + 1) << ". " << areas->getElement().codigo << endl;
        areas->next();
    }
    cout << "Seleccione el �rea: ";
    cin >> area;

    // Buscar el �rea seleccionada
    areas->goToStart();
    for (int i = 0; i < areas->getSize(); i++) {
        if (areas->getElement().codigo == area) {
            // Mostrar lista de ventanillas y permitir al usuario elegir una
            cout << "Ventanillas disponibles en el �rea " << area << ":" << endl;
            areas->getElement().ventanillas->goToStart(); // Usar ->
            for (int j = 0; j < areas->getElement().ventanillas->getSize(); j++) {
                cout << (j + 1) << ". " << areas->getElement().ventanillas->getElement().nombre << endl; // Usar ->
                areas->getElement().ventanillas->next(); // Usar ->
            }
            cout << "Seleccione el n�mero de ventanilla: ";
            cin >> numVentanilla;

            // Obtener el tiquete m�s prioritario de la cola respectiva y mostrarlo como el tiquete atendido
            if (!areas->getElement().colaTiquetes->isEmpty()) {
                Tiquete tiqueteAtendido = areas->getElement().colaTiquetes->removeMin();
                areas->getElement().ventanillas->goToPos(numVentanilla - 1); // Usar ->
                areas->getElement().ventanillas->getElement().tiqueteAtendido = tiqueteAtendido.codigoArea + to_string(tiqueteAtendido.numGlobal); // Usar ->
                tiqueteEncontrado = true;
                cout << "Tiquete atendido:" << endl;
                cout << "C�digo de �rea: " << tiqueteAtendido.codigoArea << endl;
                cout << "N�mero global: " << tiqueteAtendido.numGlobal << endl;
                cout << "Hora de solicitud: " << tiqueteAtendido.horaSolicitud << endl;
                cout << "Prioridad final: " << tiqueteAtendido.prioridadFinal << endl;
            }
            else {
                cout << "No hay tiquetes en espera en esta �rea." << endl;
            }
            break;
        }
        areas->next();
    }

    if (!tiqueteEncontrado) {
        cout << "No se encontr� el �rea especificada." << endl;
    }

    cout << "Presione una tecla para regresar al men� principal...";
    cin.ignore();
    cin.get();
}

void agregarTipoUsuario() {
    string nombre;
    string descripcion;
    int prioridad;

    cout << "Ingrese el nombre del tipo de usuario: ";
    cin >> nombre;
    cout << "Ingrese la descripci�n del tipo de usuario: ";
    cin >> descripcion;
    cout << "Ingrese la prioridad del tipo de usuario: ";
    cin >> prioridad;

    TipoUsuario nuevoTipoUsuario(nombre, descripcion, prioridad);
    tiposUsuario->insert(nuevoTipoUsuario);
}

void eliminarTipoUsuario() {
    string nombre;
    cout << "Ingrese el nombre del tipo de usuario a eliminar: ";
    cin >> nombre;

    TipoUsuario tipoUsuarioAEliminar;
    tipoUsuarioAEliminar.nombre = nombre;

    tiposUsuario->goToStart();
    for (int i = 0; i < tiposUsuario->getSize(); i++) {
        if (tiposUsuario->getElement() == tipoUsuarioAEliminar) {
            tiposUsuario->remove();
            cout << "Tipo de usuario eliminado exitosamente." << endl;
            return;
        }
        tiposUsuario->next();
    }

    cout << "Tipo de usuario no encontrado." << endl;
}

void agregarArea() {
    string descripcion;
    string codigo;
    int cantidadVentanillas;

    cout << "Ingrese la descripci�n del �rea: ";
    cin >> descripcion;
    cout << "Ingrese el c�digo del �rea: ";
    cin >> codigo;
    cout << "Ingrese la cantidad de ventanillas del �rea: ";
    cin >> cantidadVentanillas;

    Area nuevaArea(descripcion, codigo, cantidadVentanillas);
    areas->append(nuevaArea);
}

void modificarCantidadVentanillas() {
    string codigo;
    int nuevaCantidad;

    cout << "Ingrese el c�digo del �rea a modificar: ";
    cin >> codigo;
    cout << "Ingrese la nueva cantidad de ventanillas: ";
    cin >> nuevaCantidad;

    areas->goToStart();
    for (int i = 0; i < areas->getSize(); i++) {
        if (areas->getElement().codigo == codigo) {
            // Modificamos la cantidad de ventanillas directamente en el objeto ventanillas
            areas->getElement().ventanillas->clear(); // Limpiamos la lista actual
            for (int j = 0; j < nuevaCantidad; j++) {
                Ventanilla ventana((codigo + to_string(j + 1)));
                areas->getElement().ventanillas->append(ventana); // Usar ->
            }
            cout << "Cantidad de ventanillas modificada exitosamente." << endl;
            return;
        }
        areas->next();
    }

    cout << "�rea no encontrada." << endl;
}

void eliminarAreas() {
    string codigo;
    cout << "Ingrese el c�digo del �rea a eliminar: ";
    cin >> codigo;

    Area areaAEliminar;
    areaAEliminar.codigo = codigo;

    areas->goToStart();
    for (int i = 0; i < areas->getSize(); i++) {
        if (areas->getElement() == areaAEliminar) {
            areas->remove();
            cout << "�rea eliminada exitosamente." << endl;
            return;
        }
        areas->next();
    }

    cout << "�rea no encontrada." << endl;
}

void agregarServicio() {
    string nombre;
    string descripcion;
    int prioridad;
    string codigoArea;

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

void eliminarServicio() {
    string nombre;
    cout << "Ingrese el nombre del servicio a eliminar: ";
    cin >> nombre;

    Servicio servicioAEliminar;
    servicioAEliminar.nombre = nombre;

    servicios->goToStart();
    for (int i = 0; i < servicios->getSize(); i++) {
        if (servicios->getElement() == servicioAEliminar) {
            servicios->remove();
            cout << "Servicio eliminado exitosamente." << endl;
            return;
        }
        servicios->next();
    }

    cout << "Servicio no encontrado." << endl;
}

void reordenarServicios() {
    int numServicio;
    int posicionDestino;

    cout << "Ingrese el n�mero de servicio a reordenar: ";
    cin >> numServicio;
    cout << "Ingrese la posici�n destino del servicio: ";
    cin >> posicionDestino;

    if (posicionDestino < 1 || posicionDestino > servicios->getSize()) {
        cout << "Posici�n destino inv�lida." << endl;
        return;
    }

    // Avanzamos al servicio deseado
    servicios->goToStart();
    for (int i = 1; i < numServicio; ++i) {
        servicios->next();
    }

    // Obtenemos el servicio a reordenar
    Servicio servicioAReordenar = servicios->getElement();

    // Eliminamos el servicio de su posici�n original
    Servicio servicioEliminado = servicios->remove();

    // Insertamos el servicio eliminado en la posici�n destino
    servicios->goToPos(posicionDestino - 1);
    servicios->insert(servicioEliminado);
}

void administrarTiposUsuario() {
    int opcion;
    do {
        cout << "=== Men� de Administraci�n de Tipos de Usuario ===" << endl;
        cout << "1. Agregar tipo de usuario" << endl;
        cout << "2. Eliminar tipo de usuario" << endl;
        cout << "3. Regresar" << endl;
        cout << "Seleccione una opci�n: ";
        cin >> opcion;

        switch (opcion) {
        case 1:
            agregarTipoUsuario();
            break;
        case 2:
            eliminarTipoUsuario();
            break;
        case 3:
            cout << "Regresando al men� de administraci�n..." << endl;
            break;
        default:
            cout << "Opci�n no v�lida. Por favor, seleccione una opci�n v�lida." << endl;
        }
    } while (opcion != 3);
}

void administrarAreas() {
    int opcion;
    do {
        cout << "=== Men� de Administraci�n de �reas ===" << endl;
        cout << "1. Agregar �rea" << endl;
        cout << "2. Modificar cantidad de ventanillas" << endl;
        cout << "3. Eliminar �rea" << endl;
        cout << "4. Regresar" << endl;
        cout << "Seleccione una opci�n: ";
        cin >> opcion;

        switch (opcion) {
        case 1:
            agregarArea();
            break;
        case 2:
            modificarCantidadVentanillas();
            break;
        case 3:
            eliminarAreas();
            break;
        case 4:
            cout << "Regresando al men� de administraci�n..." << endl;
            break;
        default:
            cout << "Opci�n no v�lida. Por favor, seleccione una opci�n v�lida." << endl;
        }
    } while (opcion != 4);
}

void administrarServicios() {
    int opcion;
    do {
        cout << "=== Men� de Administraci�n de Servicios ===" << endl;
        cout << "1. Agregar servicio" << endl;
        cout << "2. Eliminar servicio" << endl;
        cout << "3. Reordenar servicios" << endl;
        cout << "4. Regresar" << endl;
        cout << "Seleccione una opci�n: ";
        cin >> opcion;

        switch (opcion) {
        case 1:
            agregarServicio();
            break;
        case 2:
            eliminarServicio();
            break;
        case 3:
            reordenarServicios();
            break;
        case 4:
            cout << "Regresando al men� de administraci�n..." << endl;
            break;
        default:
            cout << "Opci�n no v�lida. Por favor, seleccione una opci�n v�lida." << endl;
        }
    } while (opcion != 4);
}

void limpiarColasYEstadisticas() {
    // L�gica para limpiar las colas y estad�sticas
    // (Por implementar)
    cout << "Colas y estad�sticas limpiadas." << endl;
}

void administracion() {
    int opcion;

    do {
        cout << "=== Men� de Administraci�n ===" << endl;
        cout << "1. Tipos de usuario" << endl;
        cout << "2. �reas" << endl;
        cout << "3. Servicios disponibles" << endl;
        cout << "4. Limpiar colas y estad�sticas" << endl;
        cout << "5. Regresar" << endl;
        cout << "Seleccione una opci�n: ";
        cin >> opcion;

        switch (opcion) {
        case 1:
            administrarTiposUsuario();
            break;
        case 2:
            administrarAreas();
            break;
        case 3:
            administrarServicios();
            break;
        case 4:
            limpiarColasYEstadisticas();
            break;
        case 5:
            cout << "Regresando al men� principal..." << endl;
            break;
        default:
            cout << "Opci�n no v�lida. Por favor, seleccione una opci�n v�lida." << endl;
        }
    } while (opcion != 5);
}


void mostrarEstadisticas() {
    // L�gica para mostrar estad�sticas del sistema
    // (Por implementar)

    cout << "Presione una tecla para regresar al men� principal...";
    cin.ignore();
    cin.get();
}

int menuPrincipal() {

    int opcion;

    do {
        cout << "=== Men� Principal ===" << endl;
        cout << "1. Estado de las colas" << endl;
        cout << "2. Tiquetes" << endl;
        cout << "3. Atender" << endl;
        cout << "4. Administraci�n" << endl;
        cout << "5. Estad�sticas del sistema" << endl;
        cout << "6. Salir" << endl;
        cout << "Seleccione una opci�n: ";
        cin >> opcion;

        switch (opcion) {
        case 1:
            mostrarColas();
            break;
        case 2:
            generarTiquete();
            break;
        case 3:
            atenderTiquete();
            break;
        case 4:
            administracion();
            break;
        case 5:
            mostrarEstadisticas();
            break;
        case 6:
            cout << "Saliendo del programa..." << endl;
            break;
        default:
            cout << "Opci�n no v�lida. Por favor, seleccione una opci�n v�lida." << endl;
        }
    } while (opcion != 6);

    return 0;
}