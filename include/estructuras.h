
#ifndef ESTRUCTURAS_H
#define ESTRUCTURAS_H

/*
 * Parametros fisicos de la mision Orion.
 */
typedef struct {
    double masaTierra;
    double radioTierra;
    double altitud;
    double constanteG;
    double masaOrion;
    double aceleracionLateral;
    double duracionPulso;
} ParametrosOrbitales;

/*
 * Resultados de los calculos del propulsor lateral.
 */
typedef struct {
    double velocidadLateral;
    double desviacionLateral;
    double duracionSimulacion;
    int calculosRealizados;
} ResultadoSimulacion;

/*
 * Estado general de la mision.
 */
typedef struct {
    int cantidadResultados;
    int tieneCalculos;
    ResultadoSimulacion ultimoResultado;
} EstadoMision;

#endif
