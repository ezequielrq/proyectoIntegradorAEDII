
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#include "paciente.h"

typedef struct {
    int nroTurno;
    long dniPaciente;
    tString fechaHora;
    int areaAtencion;
    tString observacionMedica;
    float importe;
} tRegistroTurno;

static FILE* registrosTurnos;
static tRegistroTurno registro, registroAnterior;
static int pacientesArea, pacientesGeneral, codAreaMasPacientes, codAreaMasImporte, cantAreaMasPacientes;
static float importeArea, importeGeneral, importePromedioDelDia, importeTotalDelDia, cantAreaMasImporte;

// Prototipado
void guardarRegistroTurno(tRegistroTurno reg); 
void inicializacion();
void principioCorte();
void procesoCorte();
void unGrupo();
void finCorte();
void finalizacion();

// Implementacion de Funciones
void guardarRegistroTurno(tRegistroTurno reg) {
    FILE *f = fopen("registroPaciente.dat", "ab");
    if (f == NULL) {
        printf("Error al abrir el archivo para guardar la atencion.\n");
        return;
    }
    fwrite(&reg, sizeof(tRegistroTurno), 1, f);
    fclose(f);
}

void inicializacion() {
    registrosTurnos = fopen("registroPaciente.dat", "rb");
    if (registrosTurnos == NULL) {
        printf("No se pudo abrir el archivo registroPaciente.dat o esta vacio.\n");
        return;
    } else {
        fread(&registro, sizeof(tRegistroTurno), 1, registrosTurnos);
        registroAnterior = registro;
        codAreaMasPacientes = 0;
        cantAreaMasPacientes = 0;
        codAreaMasImporte = 0;
        cantAreaMasImporte = 0.0;
        importeTotalDelDia = 0.0;
        importePromedioDelDia = 0.0;
        importeGeneral = 0.0;
        pacientesGeneral = 0;
        printf("*** Registro de Pacientes en el Dia ***\n");
        printf("AREAS: 104-Cardiologia | 201-Dermatologia | 311-Pediatria | 568-Odontologia\n");
        printf("============================================================================\n");
    }
}

void principioCorte() {
    pacientesArea = 0;
    importeArea = 0.0;
}

void procesoCorte() {
    if (registrosTurnos == NULL) return;

    while (!feof(registrosTurnos)) {
        principioCorte();
        
        while (!feof(registrosTurnos) && registro.areaAtencion == registroAnterior.areaAtencion) {
            unGrupo();
            fread(&registro, sizeof(tRegistroTurno), 1, registrosTurnos);
        }
        finCorte();
    }
    finalizacion();
}

void unGrupo() {
    pacientesArea++;
    importeArea += registro.importe;
}

void finCorte() {
    pacientesGeneral += pacientesArea;
    importeGeneral += importeArea;

    if (importeArea > cantAreaMasImporte) {
        cantAreaMasImporte = importeArea;
        codAreaMasImporte = registroAnterior.areaAtencion;
    }
    
    if (pacientesArea > cantAreaMasPacientes) {
        cantAreaMasPacientes = pacientesArea;
        codAreaMasPacientes = registroAnterior.areaAtencion;
    }

    if (registroAnterior.areaAtencion == 104) {
        printf("Area de Cardiologia:\n");
    } else if (registroAnterior.areaAtencion == 201) {
        printf("Area de Dermatologia:\n");
    } else if (registroAnterior.areaAtencion == 311) {
        printf("Area de Pediatria:\n");
    } else {
        printf("Area de Odontologia (%d):\n", registroAnterior.areaAtencion);
    }
    
    printf("Pacientes atendidos: %d | Importe total: $%.2f \n", pacientesArea, importeArea);
    printf("============================================================================\n");
    
    registroAnterior = registro;
}

void finalizacion() {
    if (pacientesGeneral > 0) {
        importePromedioDelDia = (float)importeGeneral / pacientesGeneral;
    } else {
        importePromedioDelDia = 0.0;
    }
    
    printf("\n--- RESUMEN GENERAL --- \n");
    printf("El area con mas pacientes fue: %d (%d pacientes)\n", codAreaMasPacientes, cantAreaMasPacientes);
    printf("El area con mas importe fue: %d ($%.2f)\n", codAreaMasImporte, cantAreaMasImporte);
    printf("El importe promedio del dia fue de: $%.2f\n", importePromedioDelDia);
    printf("Total de pacientes atendidos en el dia: %d\n", pacientesGeneral);
    printf("Importe total del dia: $%.2f\n", importeGeneral);
    
    fclose(registrosTurnos);
}


