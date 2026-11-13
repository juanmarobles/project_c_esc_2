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

static void guardarResultado(EstadoMision *e, const ResultadoMision *r) {
    if (e == NULL || r == NULL) return;

    e->ultimoResultado = *r;
    e->tieneCalculos = 1;

    if (e->cantidadResultados < HISTORIAL_MAX) {
        e->historial[e->cantidadResultados] = *r;
        e->cantidadResultados++;
    } else {
        /* Cuando el historial se llena, se conserva una ventana de los ultimos resultados. */
        int i;
        for (i = 1; i < HISTORIAL_MAX; i++) {
            e->historial[i - 1] = e->historial[i];
        }
        e->historial[HISTORIAL_MAX - 1] = *r;
    }
}

static ResultadoMision calcularResultadosBase(const ParametrosOrbitales *p) {
    ResultadoMision r;
    r.radioOrbital = calcularRadioOrbital(p);
    r.velocidadOrbital = calcularVelocidadOrbital(p);
    r.periodoSegundos = calcularPeriodoOrbital(p);
    r.aceleracionCentripeta = calcularAceleracionCentripeta(p);
    r.fuerzaGravitatoria = calcularFuerzaGravitatoria(p);
    r.fuerzaCentripeta = p->masaOrion * r.aceleracionCentripeta;
    r.desviacionLateral = 0.0;
    r.velocidadLateralFinal = 0.0;
    r.calculosRealizados = 1;
    return r;
}

void inicializarParametros(ParametrosOrbitales *p) {
    if (p == NULL) return;
    p->masaTierra = 5.972e24;
    p->radioTierra = 6371000.0;
    p->altitud = 192000.0;
    p->constanteG = 6.674e-11;
    p->masaOrion = 33000.0;
    p->aceleracionLateral = 0.50;
    p->duracionPulso = 10.0;
}

void inicializarEstado(EstadoMision *e) {
    if (e == NULL) return;
    e->cantidadResultados = 0;
    e->tieneCalculos = 0;
    e->ultimoResultado.calculosRealizados = 0;
}

void mostrarMenu(void) {
    printf("\n");
    printf("====================================================\n");
    printf("          NASA - SIMULADOR DE MISION ARTEMIS\n");
    printf("             ORION - ORBITA TERRESTRE LEO\n");
    printf("====================================================\n");
    printf(" 1. Configurar parametros de la mision\n");
    printf(" 2. Calcular velocidad orbital y fuerzas\n");
    printf(" 3. Calcular periodo orbital\n");
    printf(" 4. Calcular aceleracion centripeta\n");
    printf(" 5. Simular pulso del propulsor lateral\n");
    printf(" 6. Ejecutar simulacion completa\n");
    printf(" 7. Consultar reporte e historial\n");
    printf(" 8. Restaurar valores originales del escenario\n");
    printf(" 0. Salir\n");
    printf("----------------------------------------------------\n");
}

void configurarParametros(ParametrosOrbitales *p) {
    if (p == NULL) return;

    printf("\n--- CONFIGURACION DE PARAMETROS ---\n");
    printf("Los valores deben ser positivos y se ingresan en unidades SI.\n");
    p->masaTierra = leerDoubleRango("Masa terrestre (kg): ", MIN_MASA, MAX_MASA);
    p->radioTierra = leerDoubleRango("Radio terrestre (m): ", 1.0, MAX_LONGITUD);
    p->altitud = leerDoubleRango("Altitud orbital (m): ", 0.0, MAX_LONGITUD);
    p->constanteG = leerDoubleRango("Constante G (N m^2/kg^2): ", 1.0e-20, 1.0);
    p->masaOrion = leerDoubleRango("Masa de Orion (kg): ", MIN_MASA, MAX_MASA);
    p->aceleracionLateral = leerDoubleRango("Aceleracion lateral (m/s^2): ", 0.0, MAX_ACELERACION);
    p->duracionPulso = leerDoubleRango("Duracion del pulso (s): ", 0.0, MAX_TIEMPO);

    printf("\nParametros actualizados correctamente.\n");
}

void restaurarParametros(ParametrosOrbitales *p, EstadoMision *e) {
    inicializarParametros(p);
    inicializarEstado(e);
    printf("\nSe restauraron los valores originales del escenario 2.\n");
}

double calcularRadioOrbital(const ParametrosOrbitales *p) {
    return p->radioTierra + p->altitud;
}

double calcularVelocidadOrbital(const ParametrosOrbitales *p) {
    double r = calcularRadioOrbital(p);
    return sqrt((p->constanteG * p->masaTierra) / r);
}

double calcularPeriodoOrbital(const ParametrosOrbitales *p) {
    double r = calcularRadioOrbital(p);
    double v = calcularVelocidadOrbital(p);
    return (2.0 * PI * r) / v;
}

double calcularAceleracionCentripeta(const ParametrosOrbitales *p) {
    double r = calcularRadioOrbital(p);
    double v = calcularVelocidadOrbital(p);
    return (v * v) / r;
}

double calcularFuerzaGravitatoria(const ParametrosOrbitales *p) {
    double r = calcularRadioOrbital(p);
    return (p->constanteG * p->masaTierra * p->masaOrion) / (r * r);
}

double calcularDesviacionLateral(const ParametrosOrbitales *p) {
    return 0.5 * p->aceleracionLateral *
           p->duracionPulso * p->duracionPulso;
}

void calcularYMostrarVelocidad(const ParametrosOrbitales *p, EstadoMision *e) {
    ResultadoMision r = calcularResultadosBase(p);
    printf("\n--- VELOCIDAD ORBITAL Y FUERZAS ---\n");
    printf("Radio orbital:                 %.3f m\n", r.radioOrbital);
    printf("Velocidad orbital:             %.3f m/s\n", r.velocidadOrbital);
    printf("Fuerza gravitatoria:           %.3f N\n", r.fuerzaGravitatoria);
    printf("Fuerza centripeta:             %.3f N\n", r.fuerzaCentripeta);
    printf("\nDemostracion:\n");
    printf("Fg = G * MT * m / r^2\n");
    printf("Fc = m * v^2 / r\n");
    printf("Igualando Fg = Fc y simplificando m:\n");
    printf("v = sqrt(G * MT / r)\n");
    printf("La masa de Orion se cancela: la velocidad orbital no depende\n");
    printf("de la masa de la nave en este modelo.\n");
    printf("Diferencia numerica entre fuerzas: %.9f N\n",
           fabs(r.fuerzaGravitatoria - r.fuerzaCentripeta));
    guardarResultado(e, &r);
}

void calcularYMostrarPeriodo(const ParametrosOrbitales *p, EstadoMision *e) {
    ResultadoMision r = calcularResultadosBase(p);
    printf("\n--- PERIODO ORBITAL ---\n");
    printf("Periodo: %.3f segundos\n", r.periodoSegundos);
    printf("Periodo: %.3f minutos\n", r.periodoSegundos / 60.0);
    printf("Formula: T = 2 * PI * r / v\n");
    guardarResultado(e, &r);
}

void calcularYMostrarAceleracion(const ParametrosOrbitales *p, EstadoMision *e) {
    ResultadoMision r = calcularResultadosBase(p);
    printf("\n--- ACELERACION CENTRIPETA ---\n");
    printf("Aceleracion centripeta: %.6f m/s^2\n", r.aceleracionCentripeta);
    printf("Formula: ac = v^2 / r = G * MT / r^2\n");
    printf("En el modelo ideal de orbita, esta es la aceleracion gravitatoria\n");
    printf("que curva continuamente la trayectoria de la nave.\n");
    guardarResultado(e, &r);
}

void simularPropulsorLateral(const ParametrosOrbitales *p, EstadoMision *e) {
    ResultadoMision r = calcularResultadosBase(p);
    r.desviacionLateral = calcularDesviacionLateral(p);
    r.velocidadLateralFinal = p->aceleracionLateral * p->duracionPulso;

    printf("\n--- SIMULACION DEL PROPULSOR LATERAL ---\n");
    printf("Aceleracion perpendicular: %.3f m/s^2\n", p->aceleracionLateral);
    printf("Duracion del pulso:         %.3f s\n", p->duracionPulso);
    printf("Velocidad lateral adquirida: %.3f m/s\n", r.velocidadLateralFinal);
    printf("Desviacion lateral:          %.3f m\n", r.desviacionLateral);
    printf("\nCon aceleracion constante perpendicular a la velocidad inicial:\n");
    printf("v_lateral = a * dt\n");
    printf("desviacion = 1/2 * a * dt^2\n");
    printf("La nave deja de seguir la orbita circular nominal. En el modelo\n");
    printf("ideal, el impulso cambia el vector velocidad y la trayectoria\n");
    printf("pasa a ser una orbita perturbada, aproximadamente eliptica.\n");
    printf("La desviacion calculada es local e instantanea durante el pulso;\n");
    printf("no modela la evolucion orbital posterior ni perturbaciones reales.\n");
    guardarResultado(e, &r);
}

void ejecutarSimulacionCompleta(const ParametrosOrbitales *p, EstadoMision *e) {
    ResultadoMision r = calcularResultadosBase(p);
    r.desviacionLateral = calcularDesviacionLateral(p);
    r.velocidadLateralFinal = p->aceleracionLateral * p->duracionPulso;

    printf("\n============== SIMULACION COMPLETA ==============\n");
    printf("Radio orbital total:          %.3f m\n", r.radioOrbital);
    printf("Velocidad orbital:            %.3f m/s\n", r.velocidadOrbital);
    printf("Periodo orbital:              %.3f s (%.3f min)\n",
           r.periodoSegundos, r.periodoSegundos / 60.0);
    printf("Aceleracion centripeta:       %.6f m/s^2\n", r.aceleracionCentripeta);
    printf("Fuerza gravitatoria:          %.3f N\n", r.fuerzaGravitatoria);
    printf("Fuerza centripeta:            %.3f N\n", r.fuerzaCentripeta);
    printf("Desviacion lateral:           %.3f m\n", r.desviacionLateral);
    printf("Velocidad lateral final:      %.3f m/s\n", r.velocidadLateralFinal);
    printf("=================================================\n");
    guardarResultado(e, &r);
}

void mostrarReporte(const ParametrosOrbitales *p, const EstadoMision *e) {
    int i;

    printf("\n=============== REPORTE DE MISION ===============\n");
    printf("Escenario: Insercion y estabilidad en orbita LEO\n");
    printf("Masa de la Tierra: %.6e kg\n", p->masaTierra);
    printf("Radio terrestre:  %.3f m\n", p->radioTierra);
    printf("Altitud:          %.3f m\n", p->altitud);
    printf("Masa Orion:       %.3f kg\n", p->masaOrion);
    printf("Constante G:      %.6e N m^2/kg^2\n", p->constanteG);
    printf("Pulso lateral:    %.3f m/s^2 durante %.3f s\n",
           p->aceleracionLateral, p->duracionPulso);

    if (!e->tieneCalculos) {
        printf("\nTodavia no se realizaron calculos.\n");
    } else {
        const ResultadoMision *r = &e->ultimoResultado;
        printf("\nUltimo resultado calculado:\n");
        printf("Velocidad orbital:       %.3f m/s\n", r->velocidadOrbital);
        printf("Periodo orbital:         %.3f s\n", r->periodoSegundos);
        printf("Aceleracion centripeta:  %.6f m/s^2\n", r->aceleracionCentripeta);
        printf("Fuerza gravitatoria:     %.3f N\n", r->fuerzaGravitatoria);
        printf("Fuerza centripeta:       %.3f N\n", r->fuerzaCentripeta);
        printf("Desviacion lateral:      %.3f m\n", r->desviacionLateral);
        printf("Velocidad lateral final: %.3f m/s\n", r->velocidadLateralFinal);
    }

    printf("\nCantidad de registros en historial: %d\n", e->cantidadResultados);
    for (i = 0; i < e->cantidadResultados; i++) {
        printf("%d) v=%.2f m/s | T=%.2f s | desvio=%.2f m\n",
               i + 1,
               e->historial[i].velocidadOrbital,
               e->historial[i].periodoSegundos,
               e->historial[i].desviacionLateral);
    }
    printf("=================================================\n");
}
