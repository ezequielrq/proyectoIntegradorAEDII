
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "paciente.h"

// Declaracion de estructuras
typedef struct nodoCola {
    tPaciente paciente;
    int nroTurno;
    struct nodoCola *siguiente;
} tNodoCola;

typedef struct {
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

// Implementacion de funciones
inline void inicializarCola(tColaEspera *c) {
    c->frente = NULL;
    c->fondo = NULL;
    c->cantidadPacientes = 0;
}

inline bool colaVacia(tColaEspera c) {
    return (c.frente == NULL);
}

inline void encolar(tColaEspera *c, tPaciente p, int nroTurno) {
    tNodoCola *nuevoNodo = (tNodoCola *)malloc(sizeof(tNodoCola));
    
    if (nuevoNodo == NULL) {
        printf("Error: Memoria insuficiente para ingresar a la sala de espera.\n");
        exit(EXIT_FAILURE);
    }
    
    nuevoNodo->paciente = p;
    nuevoNodo->nroTurno = nroTurno;
    nuevoNodo->siguiente = NULL;
    
    if (colaVacia(*c)) {
        c->frente = nuevoNodo;
    } else {
        c->fondo->siguiente = nuevoNodo;
    }
    
    c->fondo = nuevoNodo;
    c->cantidadPacientes++;
}

inline bool desencolar(tColaEspera *c, tPaciente *pacienteAtendido, int *nroTurnoAtendido) {
    if (colaVacia(*c)) {
        return false;
    }
    
    tNodoCola *aux = c->frente;
    *pacienteAtendido = aux->paciente;
    *nroTurnoAtendido = aux->nroTurno;
    
    c->frente = c->frente->siguiente;
    
    if (c->frente == NULL) {
        c->fondo = NULL;
    }
    
    free(aux);
    c->cantidadPacientes--;
    return true;
}

inline void mostrarSalaEspera(tColaEspera c) {
    if (colaVacia(c)) {
        printf("\nLa sala de espera se encuentra vacia.\n");
        return;
    }
    
    printf("\n============================================\n");
    printf("               SALA DE ESPERA               \n");
    printf("============================================\n");
    
    tNodoCola *actual = c.frente;
    tString nombreAux; 
    
    while (actual != NULL) {
        obtenerNombrePaciente(actual->paciente, nombreAux); 
        printf("Turno N %02d | DNI: %ld | Nombre: %s \n", actual->nroTurno, obtenerDniPaciente(actual->paciente), nombreAux);
        actual = actual->siguiente;
    }
    
    printf("--------------------------------------------\n");
    printf("Total en espera: %d paciente(s)\n\n", c.cantidadPacientes);
}

inline void liberarCola(tColaEspera *c) {
    tPaciente pAux;
    int tAux;
    
    while (!colaVacia(*c)) {
        desencolar(c, &pAux, &tAux);
    }
}

