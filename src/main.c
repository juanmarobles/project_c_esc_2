#include <stdio.h>
#include "simulador.h"
#include "validaciones.h"

int main(void) {
    ParametrosOrbitales parametros;
    EstadoMision estado;
    int opcion;

    inicializarParametros(&parametros);
    inicializarEstado(&estado);

    do {
        mostrarMenu();
        opcion = leerEnteroRango("Seleccione una opcion: ", 0, 8);

    } while (opcion != 0);

    return 0;
}