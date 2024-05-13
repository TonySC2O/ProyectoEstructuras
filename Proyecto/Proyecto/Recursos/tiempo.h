#pragma once
#include <iostream>
#include <string>

using namespace std;

// Transforma una hora compuesta por horas, minutos y segundos a segundos en total.
int tiempoASegundos(int hora, int min, int seg) {
	return hora * 3600 + min * 60 + seg;
}

// Agrega un 0 a la izquierda al string de una medida de hora si este es menor a 10.
string darFormato(int tiempo) {
	return tiempo > 9 ? to_string(tiempo) : ("0" + to_string(tiempo));
}

// Da la hora en un string en base a un tiempo dado en segundos.
string segundosATiempo(int tiempo) {
	int hora = int(tiempo / 3600);
	int min = int((tiempo / 60) % 60);
	int seg = int(tiempo % 60);

	return darFormato(hora) + ":" + darFormato(min) + ":" + darFormato(seg);
}