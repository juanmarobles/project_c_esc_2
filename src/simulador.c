#include <stdio.h>
#include <math.h>
#include "simulador.h"
#include "validaciones.h"

#define PI 3.14159265358979323846
#define MIN_MASA 1.0
#define MAX_MASA 1.0e30
#define MAX_LONGITUD 1.0e12
#define MAX_ACELERACION 1.0e6
#define MAX_TIEMPO 1.0e6


// void inicializarParametros(ParametrosOrbitales *p) {
//     if (p == NULL) return;
//     p->masaTierra = 5.972e24;
//     p->radioTierra = 6371000.0;
//     p->altitud = 192000.0;
//     p->constanteG = 6.674e-11;
//     p->masaOrion = 33000.0;
//     p->aceleracionLateral = 0.50;
//     p->duracionPulso = 10.0;
// }

// void inicializarEstado(EstadoMision *e) {
//     if (e == NULL) return;
//     e->cantidadResultados = 0;
//     e->tieneCalculos = 0;
//     e->ultimoResultado.calculosRealizados = 0;
// }