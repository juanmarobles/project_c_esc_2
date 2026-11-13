#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <ctype.h>
#include <string.h>
#include "validaciones.h"

#define TAM_BUFFER 128

static void limpiarRestoLinea(void) {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {
        /* descartar caracteres sobrantes */
    }
}

int leerEnteroRango(const char *mensaje, int minimo, int maximo) {
    char buffer[TAM_BUFFER];
    char *fin;
    long valor;

    while (1) {
        printf("%s", mensaje);

        if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
            printf("\nNo se pudo leer la entrada. Se finaliza el programa.\n");
            exit(EXIT_FAILURE);
        }

        if (strchr(buffer, '\n') == NULL && !feof(stdin)) {
            limpiarRestoLinea();
            printf("Entrada demasiado larga. Intente nuevamente.\n");
            continue;
        }

        errno = 0;
        valor = strtol(buffer, &fin, 10);

        while (isspace((unsigned char)*fin)) {
            fin++;
        }

        if (fin == buffer || *fin != '\0' || errno == ERANGE) {
            printf("Entrada invalida: debe ingresar un numero entero.\n");
        } else if (valor < minimo || valor > maximo) {
            printf("Fuera de rango. Ingrese un valor entre %d y %d.\n", minimo, maximo);
        } else {
            return (int)valor;
        }
    }
}

double leerDoubleRango(const char *mensaje, double minimo, double maximo) {
    char buffer[TAM_BUFFER];
    char *fin;
    double valor;

    while (1) {
        printf("%s", mensaje);

        if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
            printf("\nNo se pudo leer la entrada. Se finaliza el programa.\n");
            exit(EXIT_FAILURE);
        }

        if (strchr(buffer, '\n') == NULL && !feof(stdin)) {
            limpiarRestoLinea();
            printf("Entrada demasiado larga. Intente nuevamente.\n");
            continue;
        }

        errno = 0;
        valor = strtod(buffer, &fin);

        while (isspace((unsigned char)*fin)) {
            fin++;
        }

        if (fin == buffer || *fin != '\0' || errno == ERANGE) {
            printf("Entrada invalida: debe ingresar un numero.\n");
        } else if (!(valor >= minimo && valor <= maximo)) {
            printf("Valor fuera de rango. Ingrese un valor entre %.6g y %.6g.\n",
                   minimo, maximo);
        } else {
            return valor;
        }
    }
}
