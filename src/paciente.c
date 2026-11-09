#include "paciente.h"

// Implementacion de funciones

tPaciente ingresarPaciente(long pDni, tString pNombreApellido, int pEdad, tString pTelefono, tString pHistorialMedico){
	
	tPaciente nuevoPaciente;
	
	nuevoPaciente.dni = pDni;
	strcpy(nuevoPaciente.nombreApellido, pNombreApellido);
	nuevoPaciente.edad = pEdad;
	strcpy(nuevoPaciente.telefono, pTelefono);
	strcpy(nuevoPaciente.historialMedico, pHistorialMedico);
	
	return nuevoPaciente;
}

long obtenerDniPaciente(tPaciente p){
	
	return p.dni;
}

void obtenerNombrePaciente(tPaciente p, tString nombre){
	
	strcpy(nombre, p.nombreApellido);
}

int obtenerEdadPaciente(tPaciente p){
	
	return p.edad;
}

void obtenerTelefonoPaciente(tPaciente p, tString telefono){
	
	strcpy(telefono, p.telefono);
}

void obtenerHistorialMedico(tPaciente p, tString historial){
	
	strcpy(historial, p.historialMedico);
}

void mostrarPaciente(tPaciente p){
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
