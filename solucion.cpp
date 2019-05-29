#include "solucion.h"
#include "auxiliares.h"
#include <iostream>
#include <algorithm>
#include <fstream>
#include <iomanip>
#include <w32api/evntprov.h>

using namespace std;

void escribirGrilla(grilla g, string nombreArchivo){

    ofstream fout;
    fout.open("nombreArchivo");
    if(fout.fail()){
        cout << "error" << endl;
    }

    for (int i = 0; i < g.size() ; ++i) {
        fout << obtenerLatitud(get<0>(g[i])) << '\t';
        fout << obtenerLongitud(get<0>(g[i])) << '\t';
        fout << obtenerLatitud(get<1>(g[i])) << '\t';
        fout << obtenerLongitud(get<1>(g[i])) << '\t';
        fout << obtenerNombre(g[i]) << endl;
    }
    fout.close();
}

void escribirRecorridos(vector<recorrido> recorridos, string nombreArchivo){

    ofstream fout;
    fout.open("nombreArchivo");
    if(fout.fail()){
        cout << "error" << endl;
    }

    for (int i = 0; i < recorridos.size(); ++i) {
        for (int j = 0; j < recorridos[i].size() ; ++j) {
            fout << i << \t;
            fout << obtenerLatitud(recorridos[i][j]) << '\t';
            fout << obtenerLongitud(recorridos[i][j]) << endl;
        }
    }
    fout.close();
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
    // faltaria ordenar v!!
    vector<gps> res;

    for (int i = 0; i < recorrido; ++i) {
        if(puntoNoEstaCubierto(vOrd,u,recorrido[i])){
            res.push_back(recorrido[i]);
        }
    }
    return res;
}

/************************************** EJERCICIO construirGrilla *******************************/
grilla construirGrilla(gps esq1, gps esq2, int n, int m) {

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

}


