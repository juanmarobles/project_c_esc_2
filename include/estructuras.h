#ifndef ESTRUCTURAS_H
#define ESTRUCTURAS_H

#define HISTORIAL_MAX 100

typedef struct {
    double masaTierra;          /* kg */
    double radioTierra;         /* m */
    double altitud;             /* m */
    double constanteG;          /* N m^2 / kg^2 */
    double masaOrion;           /* kg */
    double aceleracionLateral;  /* m/s^2 */
    double duracionPulso;       /* s */
} ParametrosOrbitales;

typedef struct {
    double radioOrbital;        /* m */
    double velocidadOrbital;    /* m/s */
    double periodoSegundos;     /* s */
    double aceleracionCentripeta; /* m/s^2 */
    double fuerzaGravitatoria;  /* N */
    double fuerzaCentripeta;    /* N */
    double desviacionLateral;   /* m */
    double velocidadLateralFinal; /* m/s */
    int calculosRealizados;
} ResultadoMision;

typedef struct {
    ResultadoMision historial[HISTORIAL_MAX];
    int cantidadResultados;
    int tieneCalculos;
    ResultadoMision ultimoResultado;
} EstadoMision;

#endif
