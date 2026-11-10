#include<stdio.h>
#include<stdlib.h>
#include<string.h>


typedef char tString[100];

typedef struct{
    int nroTurno;
    long dniPaciente;
    tString fechaHora;
    int areaAtencion;
    tString observacionMedica;
    float importe;
}tRegistroTurno;

//prototipado
void archivoPacientes();
void agregarPacientes();
void guardarPacientes();
void historialTurnos();
void buscarPaciente();