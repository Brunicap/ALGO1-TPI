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

    //  !!faltaria ordenar v!!.

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
    distancia d = 0.0;
    tiempo minT = minimoTiempo(v);
    for (int i = 1; i < v.size(); i++)
    {
        if (obtenerTiempo(v[i]) != minT)
            d += distMts(obtenerPosicion(v[i]), obtenerPosicion(encontrarAnterior(v, i)));
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

}

/***************************************** EJERCICIO aPalabra **********************************/
vector<nombre> aPalabra(recorrido t, grilla g) {
        vector<nombre> palabra;
        for (int i = 0; i < t.size() ; ++i) {
            //palabra.push_back(nombreEnGrilla(t[i],g));
        }
        return palabra;
}

/************************************* EJERCICIO cantidadDeSaltos ******************************/
int cantidadDeSaltos(grilla g, viaje v) {

}


