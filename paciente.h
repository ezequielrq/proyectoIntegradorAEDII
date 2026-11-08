#include <stdio.h>
#include <string.h>
#define MAX 200

//Declaracion de estructuras
typedef char tString [MAX];

typedef struct{
	long dni;
	tString nombreApellido;
	int edad;
	tString telefono;
	tString historialMedico;
}tPaciente;

//Prototipado

tPaciente ingresarPaciente(long, tString, int, tString, tString);
long obtenerDniPaciente(tPaciente p);
void obtenerNombrePaciente(tPaciente p, tString nombre);
int obtenerEdadPaciente(tPaciente p);
void obtenerTelefonoPaciente(tPaciente p, tString telefono);
void obtenerHistorialMedico(tPaciente p, tString historial);
void mostrarPaciente(tPaciente p);
