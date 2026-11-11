#ifndef PACIENTE_H
#define PACIENTE_H

#include <stdio.h>
#include <string.h>

#define MAX 200

// Declaracion de estructuras
typedef char tString[MAX];

typedef struct {
    long dni;
    tString nombreApellido;
    int edad;
    tString telefono;
    tString historialMedico;
} tPaciente;

// Prototipado
static inline tPaciente ingresarPaciente(long pDni, tString pNombreApellido, int pEdad, tString pTelefono, tString pHistorialMedico);
static inline long obtenerDniPaciente(tPaciente p);
static inline void obtenerNombrePaciente(tPaciente p, tString nombre);
static inline int obtenerEdadPaciente(tPaciente p);
static inline void obtenerTelefonoPaciente(tPaciente p, tString telefono);
static inline void obtenerHistorialMedico(tPaciente p, tString historial);
static inline void mostrarPaciente(tPaciente p);

// Implementacion de funciones
static inline tPaciente ingresarPaciente(long pDni, tString pNombreApellido, int pEdad, tString pTelefono, tString pHistorialMedico) {
    tPaciente nuevoPaciente;
    nuevoPaciente.dni = pDni;
    strcpy(nuevoPaciente.nombreApellido, pNombreApellido);
    nuevoPaciente.edad = pEdad;
    strcpy(nuevoPaciente.telefono, pTelefono);
    strcpy(nuevoPaciente.historialMedico, pHistorialMedico);
    return nuevoPaciente;
}

static inline long obtenerDniPaciente(tPaciente p) {
    return p.dni;
}

static inline void obtenerNombrePaciente(tPaciente p, tString nombre) {
    strcpy(nombre, p.nombreApellido);
}

static inline int obtenerEdadPaciente(tPaciente p) {
    return p.edad;
}

static inline void obtenerTelefonoPaciente(tPaciente p, tString telefono) {
    strcpy(telefono, p.telefono);
}

static inline void obtenerHistorialMedico(tPaciente p, tString historial) {
    strcpy(historial, p.historialMedico);
}

static inline void mostrarPaciente(tPaciente p) {
    printf("\n===========================================\n");
    printf("            DATOS DEL PACIENTE             \n");
    printf("-------------------------------------------\n");
    printf("Nombre y Apellido: %s\n", p.nombreApellido);
    printf("DNI: %ld\n", p.dni);
    printf("Edad: %d\n", p.edad);
    printf("Numero de telefono: %s\n", p.telefono);
    printf("Historial Medico: %s\n", p.historialMedico);
    printf("===========================================\n");
}

#endif
