
#include <stdio.h>
#include <math.h>
#include "simulador.h"
#include "estructuras.h"

/*
 * Inicializa los parametros fisicos de la mision Orion.
 */
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

/*
 * Inicializa el estado general de la mision.
 */
void inicializarEstado(EstadoMision *e) {
    if (e == NULL) return;

    e->cantidadResultados = 0;
    e->tieneCalculos = 0;

    e->ultimoResultado.velocidadLateral = 0.0;
    e->ultimoResultado.desviacionLateral = 0.0;
    e->ultimoResultado.duracionSimulacion = 0.0;
    e->ultimoResultado.calculosRealizados = 0;
}

/*
 * Calcula la velocidad lateral adquirida por el propulsor.
 *
 * Formula: velocidad = aceleracion * tiempo
 *
 * Retorna 1 si el calculo fue exitoso y 0 si hubo un error.
 */
int calcularVelocidadLateral(
    double aceleracion,
    double tiempo,
    double *velocidad
) {
    if (velocidad == NULL) return 0;

    if (!isfinite(aceleracion) || !isfinite(tiempo))
        return 0;

    if (aceleracion < 0.0 || tiempo < 0.0)
        return 0;

    *velocidad = aceleracion * tiempo;

    if (!isfinite(*velocidad))
        return 0;

    return 1;
}

/*
 * Calcula el desplazamiento lateral durante el impulso.
 *
 * Formula: desviacion = 0.5 * aceleracion * tiempo^2
 *
 * Retorna 1 si el calculo fue exitoso y 0 si hubo un error.
 */
int calcularDesviacionLateral(
    double aceleracion,
    double tiempo,
    double *desviacion
) {
    if (desviacion == NULL) return 0;

    if (!isfinite(aceleracion) || !isfinite(tiempo))
        return 0;

    if (aceleracion < 0.0 || tiempo < 0.0)
        return 0;

    *desviacion = 0.5 * aceleracion * tiempo * tiempo;

    if (!isfinite(*desviacion))
        return 0;

    return 1;
}

/*
 * Ejecuta la simulacion del propulsor lateral
 * y guarda los resultados en el estado de la mision.
 */
int simularPropulsorLateral(
    const ParametrosOrbitales *p,
    EstadoMision *e
) {
    ResultadoSimulacion resultado;

    if (p == NULL || e == NULL)
        return 0;

    if (!isfinite(p->aceleracionLateral) ||
        !isfinite(p->duracionPulso))
        return 0;

    if (p->aceleracionLateral < 0.0 ||
        p->duracionPulso < 0.0)
        return 0;

    if (!calcularVelocidadLateral(
            p->aceleracionLateral,
            p->duracionPulso,
            &resultado.velocidadLateral))
        return 0;

    if (!calcularDesviacionLateral(
            p->aceleracionLateral,
            p->duracionPulso,
            &resultado.desviacionLateral))
        return 0;

    resultado.duracionSimulacion = p->duracionPulso;
    resultado.calculosRealizados = 1;

    e->ultimoResultado = resultado;
    e->cantidadResultados++;
    e->tieneCalculos = 1;

    return 1;
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

/*
 * Muestra en pantalla el reporte detallado del estado actual de la mision.
 */
void mostrarReporte(const ParametrosOrbitales *p, const EstadoMision *e) {
    if (p == NULL || e == NULL) return;

    double radioOrbital = p->radioTierra + p->altitud;
    double velocidadOrbital = 0.0;
    double aceleracionCentripeta = 0.0;
    double fuerzaGravitatoria = 0.0;
    double periodoSegundos = 0.0;
    double periodoMinutos = 0.0;

    if (radioOrbital > 0.0) {
        velocidadOrbital = sqrt((p->constanteG * p->masaTierra) / radioOrbital);
        aceleracionCentripeta = (velocidadOrbital * velocidadOrbital) / radioOrbital;
        fuerzaGravitatoria = p->masaOrion * aceleracionCentripeta;
        if (velocidadOrbital > 0.0) {
            periodoSegundos = (2.0 * 3.14159265 * radioOrbital) / velocidadOrbital;
            periodoMinutos = periodoSegundos / 60.0;
        }
    }

    printf("\n====================================================\n");
    printf("         REPORTE FINAL DE MISION - ORION LEO        \n");
    printf("====================================================\n");
    printf(" [1] PARAMETROS CONFIGURADOS:\n");
    printf("  - Masa de la Tierra (MT)   : %.3e kg\n", p->masaTierra);
    printf("  - Radio Terrestre (RT)     : %.2f m (%.2f km)\n", p->radioTierra, p->radioTierra / 1000.0);
    printf("  - Altitud Orbital (h)      : %.2f m (%.2f km)\n", p->altitud, p->altitud / 1000.0);
    printf("  - Radio Orbital Total (r)  : %.2f m (%.2f km)\n", radioOrbital, radioOrbital / 1000.0);
    printf("  - Masa de la Nave Orion    : %.2f kg\n", p->masaOrion);
    printf("----------------------------------------------------\n");
    printf(" [2] ANALISIS ORBITAL (MCU Y GRAVITACION):\n");
    printf("  - Velocidad Orbital (v)    : %.2f m/s (%.2f km/h)\n", velocidadOrbital, velocidadOrbital * 3.6);
    printf("  - Periodo Orbital (T)      : %.2f s (%.2f min)\n", periodoSegundos, periodoMinutos);
    printf("  - Aceleracion Centripeta   : %.4f m/s^2\n", aceleracionCentripeta);
    printf("  - Fuerza Gravitatoria (Fg) : %.2f N (Equivalente a Fc)\n", fuerzaGravitatoria);
    printf("----------------------------------------------------\n");
    printf(" [3] ESTADO DEL PROPULSOR LATERAL:\n");
    if (e->tieneCalculos && e->ultimoResultado.calculosRealizados) {
        printf("  - Aceleracion aplicada (a) : %.2f m/s^2\n", p->aceleracionLateral);
        printf("  - Duracion del pulso (dt)  : %.2f s\n", e->ultimoResultado.duracionSimulacion);
        printf("  - Velocidad lateral (vL)   : %.2f m/s\n", e->ultimoResultado.velocidadLateral);
        printf("  - Desviacion lateral       : %.2f m\n", e->ultimoResultado.desviacionLateral);
        printf("  - Diagnostico de orbita    : Trayectoria perturbada por impulso lateral.\n");
    } else {
        printf("  - No se registran maniobras de propulsor lateral aun.\n");
    }
    printf("====================================================\n");
}
