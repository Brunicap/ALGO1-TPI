#ifndef TRANSPORTEURBANO_AUXILIARES_H
#define TRANSPORTEURBANO_AUXILIARES_H

#include "definiciones.h"


double obtenerLatitud(gps posicion);
double obtenerLongitud(gps posicion);
gps obtenerPosicion(tuple<tiempo, gps> medicion);
tiempo obtenerTiempo(tuple<tiempo, gps> medicion);
double distEnKM(gps posicion1, gps posicion2);
gps desviarPunto(gps p, double desvioMtsLatitud, double desvioMtsLongitud);
double distMts(gps posicion1, gps posicion2);
gps puntoGps(double latitud, double longitud);
tuple<tiempo, gps> medicion(tiempo t, gps g);








viaje ordenarViajeBurbuja(viaje v);


tiempo maximoTiempo (viaje& v);
tiempo minimoTiempo (viaje& v);


bool viajeEnFranjaHoraria(viaje& v, tiempo t0, tiempo tf);


double velocidad(tuple<tiempo,gps> p1 , tuple<tiempo,gps> p2);


nombre nombreEnGrilla (gps posicion, grilla g);


bool puntoCubierto(viaje vOrd, distancia u, gps p);

vector<gps> recorridoDeV(viaje vOrd);

int distanciaEntreCeldas(nombre n1, nombre n2);

nombre encontrarNombreEnGrilla(gps posicion);


int distanciaEntreCeldas(nombre n1, nombre n2);


vector<nombre> obtenerPalabra(recorrido t, grilla g);


recorrido obtenerRecorrido(viaje v);


#endif //TRANSPORTEURBANO_AUXILIARES_H
