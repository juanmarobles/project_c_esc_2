#ifndef SIMULADOR_H
#define SIMULADOR_H

#include "estructuras.h"

void inicializarParametros(ParametrosOrbitales *p);
void inicializarEstado(EstadoMision *e);
void mostrarMenu(void);
void configurarParametros(ParametrosOrbitales *p);
void restaurarParametros(ParametrosOrbitales *p, EstadoMision *e);
double calcularRadioOrbital(const ParametrosOrbitales *p);
double calcularVelocidadOrbital(const ParametrosOrbitales *p);
double calcularPeriodoOrbital(const ParametrosOrbitales *p);
double calcularAceleracionCentripeta(const ParametrosOrbitales *p);
double calcularFuerzaGravitatoria(const ParametrosOrbitales *p);
double calcularDesviacionLateral(const ParametrosOrbitales *p);
void calcularYMostrarVelocidad(const ParametrosOrbitales *p, EstadoMision *e);
void calcularYMostrarPeriodo(const ParametrosOrbitales *p, EstadoMision *e);
void calcularYMostrarAceleracion(const ParametrosOrbitales *p, EstadoMision *e);
void simularPropulsorLateral(const ParametrosOrbitales *p, EstadoMision *e);
void ejecutarSimulacionCompleta(const ParametrosOrbitales *p, EstadoMision *e);
void mostrarReporte(const ParametrosOrbitales *p, const EstadoMision *e);

#endif
