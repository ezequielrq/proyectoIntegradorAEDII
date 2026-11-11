#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "paciente.h"
#include "colaEspera.h"
#include "persistencia.h"

// Prototipos de funciones
void mostrarMenu();

// Programa principal
int main() {
    tColaEspera salaEspera;
    inicializarCola(&salaEspera);

    int opcion = 0;
    int contadorTurno = 1;

    long dni;
    tString nombre, telefono, historial, fechaHora, observacion;
    int edad, area;
    float importe;

    tPaciente pacienteAux;
    int nroTurnoAux;
    tRegistroTurno regTurno;

    do {
        mostrarMenu();
        if (scanf("%d", &opcion) != 1) {
            printf("\nOpcion invalida. Intente de nuevo.\n");
            while (getchar() != '\n'); 
            continue;
        }
        getchar(); 

        switch (opcion) {
            case 1:
                printf("\n--- REGISTRO DE PACIENTE Y SOLICITUD DE TURNO ---\n");
                printf("DNI: ");
                scanf("%ld", &dni);
                getchar();

                printf("Nombre y Apellido: ");
                fgets(nombre, MAX, stdin);
                nombre[strcspn(nombre, "\n")] = 0;

                printf("Edad: ");
                scanf("%d", &edad);
                getchar();

                printf("Telefono: ");
                fgets(telefono, MAX, stdin);
                telefono[strcspn(telefono, "\n")] = 0;

                printf("Historial Medico / Antecedentes: ");
                fgets(historial, MAX, stdin);
                historial[strcspn(historial, "\n")] = 0;

                pacienteAux = ingresarPaciente(dni, nombre, edad, telefono, historial);
                encolar(&salaEspera, pacienteAux, contadorTurno);

                printf("\n[EXITO] Paciente encolado correctamente. Asignado Turno N %02d.\n", contadorTurno);
                contadorTurno++;
                break;

            case 2:
                printf("\n--- ATENCION MEDICA ---\n");
                if (desencolar(&salaEspera, &pacienteAux, &nroTurnoAux)) {
                    printf("\nAtendiendo al Turno N %02d:\n", nroTurnoAux);
                    mostrarPaciente(pacienteAux);
                    
                    printf("\nComplete los datos de la consulta para guardar en historial:\n");
                    printf("Fecha y Hora (ej: 10/11/2026 10:30): ");
                    fgets(fechaHora, 100, stdin);
                    fechaHora[strcspn(fechaHora, "\n")] = 0;

                    printf("Codigo de Area (104-Cardiologia | 201-Dermatologia | 311-Pediatria | 568-Odontologia): ");
                    scanf("%d", &area);
                    getchar();

                    printf("Observacion medica / Diagnostico: ");
                    fgets(observacion, 100, stdin);
                    observacion[strcspn(observacion, "\n")] = 0;

                    printf("Importe de la consulta ($): ");
                    scanf("%f", &importe);
                    getchar();

                    regTurno.nroTurno = nroTurnoAux;
                    regTurno.dniPaciente = obtenerDniPaciente(pacienteAux);
                    strcpy(regTurno.fechaHora, fechaHora);
                    regTurno.areaAtencion = area;
                    strcpy(regTurno.observacionMedica, observacion);
                    regTurno.importe = importe;

                    guardarRegistroTurno(regTurno);
                    printf("\n[EXITO] Consulta registrada y guardada en 'registroPaciente.dat'.\n");
                } else {
                    printf("\nNo hay pacientes en la sala de espera.\n");
                }
                break;

            case 3:
                mostrarSalaEspera(salaEspera);
                break;

            case 4:
                printf("\n--- INFORME HISTORICO DE ATENCIONES (CORTE DE CONTROL) ---\n");
                inicializacion();
                procesoCorte();
                break;

            case 5:
                liberarCola(&salaEspera);
                printf("\nMemoria de la cola liberada. Saliendo del sistema...\n");
                break;

            default:
                printf("\nOpcion no valida. Ingrese un numero entre 1 y 5.\n");
                break;
        }

    } while (opcion != 5);

    return 0;
}

// Implementacion de funciones
void mostrarMenu() {
    printf("\n============================================\n");
    printf("   SISTEMA DE GESTION DE TURNOS MEDICOS     \n");
    printf("              FaCENA - UNNE                 \n");
    printf("============================================\n");
    printf("1. Registrar paciente y solicitar turno\n");
    printf("2. Atender siguiente paciente\n");
    printf("3. Consultar estado de la Sala de Espera\n");
    printf("4. Generar Informe Historico (Corte de Control)\n");
    printf("5. Salir del sistema\n");
    printf("--------------------------------------------\n");
    printf("Ingrese una opcion: ");
}
