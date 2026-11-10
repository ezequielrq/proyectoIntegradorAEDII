#include<stdio.h>
#include "archivoPaciente.h"

FILE *registrosTurnos;
tRegistroTurno dato;



//implementacion de las funciones
void archivoPacientes(){
    registrosTurnos = fopen("registroPaciente.dat","ab");
    if(registrosTurnos == NULL){
        printf("Error! no se pudo abrir el archivo\n");
        exit(1);
    }else{
        printf("Archivo abierto para agregar paciente: \n");
    }
    
}

void agregarPacientes(){
    char opcion = 's';

    while(opcion == 's'){
        printf("Ingrese numero del Turno: \n");
        scanf(" %d", &dato.nroTurno);

        printf("Ingrese DNI del paciente: \n");
        scanf(" %ld", &dato.dniPaciente);

        printf("Ingrese fecha y hora del Turno: \n");
        scanf(" %99[^\n]", dato.fechaHora);

        printf("Ingrese el area en el que fue atendido: \n");
        printf("\n--- AREAS MEDICAS ---\n");
        printf("104 - Cardiologia\n");
        printf("201 - Dermatologia\n");
        printf("311 - Pediatria\n");
        printf("568 - Odontologia\n");
        scanf(" %d", &dato.areaAtencion);

        printf("Ingrese observacion medica: \n");
        scanf(" %99[^\n]", dato.observacionMedica);

        printf("Ingrese importe de atencion: \n");
        scanf(" %f", &dato.importe);

        fwrite(&dato, sizeof(tRegistroTurno), 1, registrosTurnos);

        printf("¿Desea agregar otro paciente?: (s/n)\n");
        scanf(" %c", &opcion);

    }
    
    fclose(registrosTurnos);

}

void buscarPaciente(){

    long dniBuscar;
    int encontrado = 0;

    registrosTurnos = fopen("registroPaciente.dat", "rb");

    if(registrosTurnos == NULL){
        printf("Error al abrir el archivo\n");
        return;
    }

    printf("Ingrese el DNI del paciente: ");
    scanf("%ld", &dniBuscar);

    while(fread(&dato, sizeof(tRegistroTurno), 1, registrosTurnos) == 1){

        if(dato.dniPaciente == dniBuscar){

            printf("\nPaciente encontrado\n");
            printf("Numero de turno: %d\n", dato.nroTurno);
            printf("DNI: %ld\n", dato.dniPaciente);
            printf("Fecha y hora: %s\n", dato.fechaHora);
            printf("Observacion: %s\n", dato.observacionMedica);

            encontrado = 1;
        }
    }

    if(encontrado == 0){
        printf("No se encontraron turnos para ese DNI\n");
    }

    fclose(registrosTurnos);
}

void historialTurnos(){

    registrosTurnos = fopen("registroPaciente.dat", "rb");

    if(registrosTurnos == NULL){
        printf("Error al abrir el archivo\n");
        return;
    }

    while(fread(&dato, sizeof(tRegistroTurno), 1, registrosTurnos) == 1){

        printf("\n--- HISTORIAL DE TURNOS ---\n");
        printf("Numero de turno: %d\n", dato.nroTurno);
        printf("DNI del paciente: %ld\n", dato.dniPaciente);
        printf("Fecha y hora: %s\n", dato.fechaHora);
        printf("Observacion medica: %s\n", dato.observacionMedica);
    }

    fclose(registrosTurnos);
}


