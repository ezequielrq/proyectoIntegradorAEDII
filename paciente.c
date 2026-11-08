#include "paciente.h"

// Implementacion de funciones

tPaciente altaPaciente(long pDni, tString pNombreApellido, int pEdad, tString pTelefono, tString pHistorialMedico){
	
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

void guardarPaciente(tPaciente p) {

    FILE *archivoPacientes;

    archivoPacientes = fopen("pacientes.dat", "ab");

    if(archivoPacientes == NULL) {
        printf("Error al abrir el archivo");
        exit(1);
    }

    fwrite(&p, sizeof(tPaciente), 1, archivoPacientes);

    fclose(archivoPacientes);
}

void mostrarPacientes() {

    FILE *archivoPacientes;
    tPaciente paciente;

    archivoPacientes = fopen("pacientes.dat", "rb");

    if(archivoPacientes == NULL) {
        printf("No se pudo abrir el archivo");
        return;
    }

    while(fread(&paciente, sizeof(tPaciente), 1, archivoPacientes) == 1) {
        mostrarPaciente(paciente);
    }

    fclose(archivoPacientes);
}
