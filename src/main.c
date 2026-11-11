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

        switch (opcion) {
            case 1:
                configurarParametros(&parametros);
                break;
            case 2:
                calcularYMostrarVelocidad(&parametros, &estado);
                break;
            case 3:
                calcularYMostrarPeriodo(&parametros, &estado);
                break;
            case 4:
                calcularYMostrarAceleracion(&parametros, &estado);
                break;
            case 5:
                simularPropulsorLateral(&parametros, &estado);
                break;
            case 6:
                ejecutarSimulacionCompleta(&parametros, &estado);
                break;
            case 7:
                mostrarReporte(&parametros, &estado);
                break;
            case 8:
                restaurarParametros(&parametros, &estado);
                break;
            case 0:
                printf("\nCierre de simulador. Mision finalizada.\n");
                break;
        }
    } while (opcion != 0);

    return 0;
}
