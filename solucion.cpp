#include "solucion.h"
#include "auxiliares.h"
#include <iostream>
#include <algorithm>
#include <fstream>
#include <iomanip>

using namespace std;

void escribirGrilla(grilla g, string nombreArchivo){

    ofstream fout;
    fout.open(nombreArchivo);
    if(fout.fail()){
        cout << "error" << endl;
    }

    for (int i = 0; i < g.size() ; ++i) {
        fout << obtenerLatitud(get<0>(g[i])) << '\t';
        fout << obtenerLongitud(get<0>(g[i])) << '\t';
        fout << obtenerLatitud(get<1>(g[i])) << '\t';
        fout << obtenerLongitud(get<1>(g[i])) << '\t';
        fout << "(" << get<0>(get<2>(g[i])) << "," << get<1>(get<2>(g[i])) << ")" << endl;
    }
    fout.close();
}

void escribirRecorridos(vector<recorrido> recorridos, string nombreArchivo){

    ofstream fout;
    fout.open(nombreArchivo);
    if(fout.fail()){
        cout << "error" << endl;
    }

    for (int i = 0; i < recorridos.size(); ++i) {
        for (int j = 0; j < recorridos[i].size() ; ++j) {
            fout << i << '\t';
            fout << obtenerLatitud(recorridos[i][j]) << '\t';
            fout << obtenerLongitud(recorridos[i][j]) << endl;
        }
    }
    fout.close();
}

/*****************************+***** EJERCICIO excesoDeVelocidad **********************************/
bool excesoDeVelocidad(viaje v) {

    //ordenar viaje por O(n2)
    v = ordenarViajeBurbuja(v);

    int i = 1;
    while( i < v.size() && velocidad(v[i-1],v[i]) < 80.0 )
    {
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

    recorrido res;

    for (int i = 0; i < r.size(); ++i) {
        if(!puntoCubierto(v, u, r[i])){
            res.push_back(r[i]);
        }
    }
    return res;
}

/************************************** EJERCICIO construirGrilla *******************************/
grilla construirGrilla(gps esq1, gps esq2, int n, int m) {

    //ver bien después con un test los + y - para lat y long

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
        return obtenerPalabra(t, g);
}

/************************************* EJERCICIO cantidadDeSaltos ******************************/
int cantidadDeSaltos(grilla g, viaje v) {
    int cantSaltos = 0;

    recorrido r = obtenerRecorrido(v);
    vector<nombre> palabra = obtenerPalabra (r, g);

    for (int i = 1; i < palabra.size(); i++)
    {
        if (distanciaEntreCeldas(palabra[i-1], palabra[i]) > 1)
            cantSaltos++;
    }

    return cantSaltos;
}