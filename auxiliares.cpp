#include <algorithm>
#include "auxiliares.h"

const double pi = 3.14;
double radioTierra = 6378;

double obtenerLatitud(gps posicion) {
    return get<0>(posicion);
}

double obtenerLongitud(gps posicion) {
    return get<1>(posicion);
}

gps obtenerPosicion(tuple<tiempo, gps> medicion) {
    return get<1>(medicion);
}

tiempo obtenerTiempo(tuple<tiempo, gps> medicion) {
    return get<0>(medicion);
}

gps obtenerEsquinaSuperior(celda c) {
    return get<1>(c);
}

gps obtenerEsquinaInferior(celda c) {
    return get<0>(c);
}

nombre obtenerNombre(celda c) {
    return get<2>(c);
}

double distMts(gps posicion1, gps posicion2){
    return distEnKM(posicion1, posicion2) * 1000;
}


double distEnKM(gps posicion1, gps posicion2) {
    double latitud1 = obtenerLatitud(posicion1);
    double latitud2 = obtenerLatitud(posicion2);
    double longitud1 = obtenerLongitud(posicion1);
    double longitud2 = obtenerLongitud(posicion2);

    // obtengo la distancia
    double distanciaLatitud = (latitud2 - latitud1) * pi / 180.0;
    double distanciaLongitud = (longitud2 - longitud1) * pi / 180.0;

    // paso las latitudes a radianes
    latitud1 = (latitud1) * pi / 180.0;
    latitud2 = (latitud2) * pi / 180.0;

    // aplico la formula
    double a = pow(sin(distanciaLatitud / 2), 2) +
               pow(sin(distanciaLongitud / 2), 2) *
               cos(latitud1) * cos(latitud2);

    double c = 2 * asin(sqrt(a));
    return radioTierra * c;
}

gps desviarPunto(gps p, double desvioMtsLatitud, double desvioMtsLongitud){
    double lat = obtenerLatitud(p);
    double lon = obtenerLongitud(p);

    double dx = desvioMtsLatitud / 1000;
    double dy = desvioMtsLongitud / 1000;
    double new_latitude = lat + (dx / radioTierra) * (180 / pi);
    double new_longitude = lon + (dy / radioTierra) * (180 / pi) / cos(lat * pi / 180);
    return puntoGps(new_latitude, new_longitude);

}


gps puntoGps(double latitud, double longitud) {
    return make_tuple(latitud, longitud);
}

tuple<tiempo, gps> medicion(tiempo t, gps g) {
    return make_tuple(t, g);
}











viaje ordenarViajeBurbuja(viaje v)
{
    //ordeno por burbuja
    for (int i = 0; i < v.size(); i++)
        for (int h = 0; h < v.size()-1; h++)
        {
            if (obtenerTiempo(v[h]) > obtenerTiempo(v[h+1]))
            {
                tuple<tiempo, gps> swapAux = v[h];
                v[h] = v[h+1];
                v[h+1] = swapAux;
            }
        }
    return v;
}


tiempo maximoTiempo (viaje& v){
    double Tmax = obtenerTiempo(v[0]);

    for (int i = 1; i < v.size(); ++i) {
        if(obtenerTiempo(v[i]) > Tmax){
            Tmax = obtenerTiempo(v[i]);
        }
    }
    return Tmax;
}

tiempo minimoTiempo (viaje& v){
    double Tmin = obtenerTiempo(v[0]);

    for (int i = 1; i < v.size(); ++i) {
        if(obtenerTiempo(v[i]) < Tmin){
            Tmin= obtenerTiempo(v[i]);
        }
    }
    return Tmin;
}






bool viajeEnFranjaHoraria(viaje& v, tiempo t0, tiempo tf) {
    return !(maximoTiempo(v) < t0 || minimoTiempo(v) > tf);
}



bool puntoCubierto(viaje v, distancia u, gps p){
    int i = 0;
    while (i < v.size() &&  (distMts(obtenerPosicion(v[i]),p) >= u)) {
        i++;
    }
    return (i < v.size());
}


nombre nombreEnGrilla (gps posicion, grilla g){

    //nombre en grilla puede tener problemas. Debatir:
        //retorna basura si no encuentra el nombre (el recorrido siempre está en la grilla? discutir)
        //la forma de chequeo está mal, debería ser un rango? No un == (además siempre es peligroso usar == con float o double)

    double latitudPos = obtenerLatitud(posicion);
    double longitudPos = obtenerLongitud(posicion);
    nombre res;

    for (int i = 0; i < g.size() ; ++i) {
        if((latitudPos == obtenerLatitud(get<0>(g[i]))) && (longitudPos == obtenerLongitud(get<1>(g[i])))){
            res = get<2>(g[i]);
        }
    }
    return res;
}


double velocidad(tuple<tiempo,gps> p1 , tuple<tiempo,gps> p2){
    return ((distEnKM(obtenerPosicion(p1),obtenerPosicion(p2))) / ((obtenerTiempo(p2) - obtenerTiempo(p1)) / 3600));
}



int distanciaEntreCeldas(nombre n1, nombre n2)
{
    return abs(get<0>(n1) - get<0>(n2)) + abs(get<1>(n1) - get<1>(n2)) + 1;
}


vector<nombre> obtenerPalabra(recorrido t, grilla g)
{
    vector<nombre> palabra;
    for (int i = 0; i < t.size(); ++i) {
        palabra.push_back(nombreEnGrilla(t[i],g));
    }

    return palabra;
}


recorrido obtenerRecorrido(viaje v)
{
    viaje vOrd = ordenarViajeBurbuja(v);

    recorrido r;
    for (int i = 0; i < vOrd.size(); i++) r.push_back(obtenerPosicion(vOrd[i]));
    return r;
}