#include<stdio.h>
#include<string.h>
#include<stdlib.h>>
#include<ctype.h>

typedef char tString[100];

typedef struct{
    int nroTurno;
    long dniPaciente;
    tString fechaHora;
    int areaAtencion;
    tString observacionMedica;
    float importe;
}tRegistroTurno;


FILE* registrosTurnos;
tRegistroTurno registro, registroAnterior;
int pacientesArea, pacientesGeneral, codAreaMasPacientes, codAreaMasImporte, cantAreaMasPacientes;
float importeArea, importeGeneral, importePromedioDelDia, importeTotalDelDia, cantAreaMasImporte;


//Prototipado;


void inicializacion();
void principioCorte();
void procesoCorte();
void unGrupo();
void finCorte();
void finalizacion();

//Implementacion de Funciones

void inicializacion(){
    registrosTurnos =  fopen("registroPaciente.dat", "rb");
    if(registrosTurnos == NULL){
        printf("No se pudo abrir el archivo\n");
        exit(1);
    }else{
        fread(&registro, sizeof(tRegistroTurno), 1, registrosTurnos);
        registroAnterior = registro;
        codAreaMasPacientes = 0;
        cantAreaMasPacientes = 0;
        codAreaMasImporte = 0;
        cantAreaMasImporte = 0.0;
        importeTotalDelDia = 0.0;
        importePromedioDelDia = 0.0;
        importeGeneral = 0;
        pacientesGeneral = 0;
        printf("***Registro de Pacientes en el Dia***\n");
        printf("AREAS: 104-Cardiologia | 201-Dermatologia | 311-Pediatria | 568-Odontologia\n");
        printf("============================================================================\n");
    }
}

void principioCorte(){
    pacientesArea = 0;
    importeArea = 0;
}

void procesoCorte(){
    while(!feof(registrosTurnos)){
        principioCorte();
        while(!feof(registrosTurnos) && registro.dniPaciente == registroAnterior.dniPaciente){
            unGrupo();
            fread(&registro, sizeof(tRegistroTurno), 1, registrosTurnos);
        }
        finCorte();
        }
    finalizacion();
}

void unGrupo(){
    pacientesArea++;
    importeArea += registro.importe;
}

void finCorte(){
    pacientesGeneral++;
    importeGeneral += importeArea;
    if(importeArea > cantAreaMasImporte){
        cantAreaMasImporte = importeArea;
        codAreaMasImporte = registroAnterior.areaAtencion;
    }
    if(pacientesArea > cantAreaMasPacientes){
        cantAreaMasPacientes = pacientesArea;
        codAreaMasPacientes = registroAnterior.areaAtencion;
    }
    importeTotalDelDia += importeArea;
    pacientesGeneral += pacientesArea;

    if(registroAnterior.areaAtencion == 104){
        printf("Area de Cardiologia:\n");
    }else{
        if(registroAnterior.areaAtencion == 201){
            printf("Area de Dermatologia:\n");
        }else{
            if(registroAnterior.areaAtencion == 311){
                printf("Area de pediatria:\n");
            }else{
                printf("Area de Odontologia:\n");
            }
        }
    }
    printf("Pacientes atendidos: %d | Importe total: %.2f \n", pacientesArea, importeArea);
    printf("============================================================================\n");
    registroAnterior = registro;
}

void finalizacion(){
    importePromedioDelDia = (float) importeGeneral / pacientesGeneral;
    printf("El area con mas pacientes fue %d (%d pacientes)\n", codAreaMasPacientes, cantAreaMasPacientes);
    printf("El area con mas importe fue: %d (%.2f)\n", codAreaMasImporte, cantAreaMasImporte);
    printf("El importe promdio en el dia fue de: %.2f\n", importePromedioDelDia);
    printf("Total de pacientes atendidos en el dia: %d\n", pacientesGeneral);
    printf("Importe total del dia: %.2f\n", importeGeneral);
    fclose(registrosTurnos);
}