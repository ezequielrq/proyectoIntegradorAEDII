#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#include "paciente.h"

// Declaracion de estructuras

typedef struct nodoCola{
	
	tPaciente paciente;
	int nroTurno;
	struct nodoCola *siguente;
	
} tNodoCola;

typedef struct{
	
	tNodoCola *frente;
	tNodoCola *fondo;
	int cantidadPacientes;
	
} tColaEspera;

// Declaracion de prototipos de funciones

void inicializarCola(tColaEspera *c);
bool colaVacia(tColaEspera c);
void encolar(tColaEspera *c, tPaciente p, int nroTurno);
bool desencolar(tColaEspera *c, tPaciente *pacienteAtendido, int *nroTurnoAtendido);
void mostrarSalaEspera(tColaEspera c);
void liberarCola(tColaEspera *c);

