#include "solucion.h"
#include "auxiliares.h"
#include <iostream>
#include <algorithm>
#include <fstream>
#include <iomanip>

using namespace std;

void escribirGrilla(grilla g, string nombreArchivo){

}

void escribirRecorridos(vector<recorrido> recorridos, string nombreArchivo){

}

/*****************************+***** EJERCICIO excesoDeVelocidad **********************************/
bool excesoDeVelocidad(viaje v) {

    //ordenar viaje por O(n2)
    v = ordenarViajeBurbuja(v);

    int i = 1;
    while( i < v.size() && velocidad(v[i-1],v[i]) < 80.0 ) {
            i++;
    }
    return i < v.size();
}

/******++++**************************** EJERCICIO tiempoTotal ***********+++***********************/
tiempo tiempoTotal(viaje v) {
    double max = maximoTiempo(v);
    double min = minimoTiempo(v);
    double res = max - min;

    return  res;
}

/************++*********************** EJERCICIO distanciaTotal ************++*********************/
distancia distanciaTotal(viaje v) {

    //ordenar viaje por O(n2)
    v = ordenarViajeBurbuja(v);

    distancia d = 0.0;
    tiempo minT = minimoTiempo(v);
    for (int i = 1; i < v.size(); i++)
    {
        d += distEnKM(obtenerPosicion(v[i]), obtenerPosicion(v[i-1]));
    }
    return d;
}

/***************************************** EJERCICIO flota ***************************************/
int flota(vector<viaje> f, tiempo t0, tiempo tf) {
    int res = 0;
    for (int i = 0; i < f.size(); i++) {
        if (viajeEnFranjaHoraria(f[i], t0, tf))
            res++;
    }

    return res;
}

/************************************ EJERCICIO recorridoCubierto *******************************/
vector<gps> recorridoNoCubierto(viaje v, recorrido r, distancia u) {

}

/************************************** EJERCICIO construirGrilla *******************************/
grilla construirGrilla(gps esq1, gps esq2, int n, int m) {
    grilla gOut;
    double deltaLat = fabs(obtenerLatitud(esq1) - obtenerLatitud(esq2));
    double deltaLong = fabs(obtenerLongitud(esq1) - obtenerLongitud(esq2));
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++)
        {
            gps e1 = puntoGps(obtenerLatitud(esq1) + deltaLat * i, obtenerLongitud(esq1) + deltaLong * j);
            gps e2 = puntoGps(obtenerLatitud(esq1) + deltaLat * (i+1), obtenerLongitud(esq1) + deltaLong * (j+1));

            nombre name = make_tuple(i, j);
            celda c = make_tuple(e1, e2, name);
            gOut.push_back(c);
        }

    return gOut;
}

/***************************************** EJERCICIO aPalabra **********************************/
vector<nombre> aPalabra(recorrido t, grilla g) {
        vector<nombre> palabra;
        for (int i = 0; i < t.size() ; ++i) {
            palabra.push_back(nombreEnGrilla(t[i],g));
        }
        return palabra;
}

/************************************* EJERCICIO cantidadDeSaltos ******************************/
int cantidadDeSaltos(grilla g, viaje v) {
    v = ordenarViajeBurbuja(v);


}


