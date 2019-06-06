#include "solucion.h"
#include "auxiliares.h"
#include <iostream>
#include <algorithm>
#include <fstream>
#include <iomanip>

using namespace std;

//--------------------Auxiliares suministrados por la cátedra--------------------//
//decidimos sólo copiar aquellos que no están declarados en auxiliares.h
//para permitir la correcta ejecución del código

gps obtenerEsquinaSuperior(celda c) {
    return get<1>(c);
}

gps obtenerEsquinaInferior(celda c) {
    return get<0>(c);
}

nombre obtenerNombre(celda c) {
    return get<2>(c);
}
//-------------------------------------------------------------------------------//




//--------------------Auxiliares escritos por nosotros--------------------//
//pegados acá para poder entregar un único archivo
viaje ordenarViajeBurbuja(viaje v)
{
    //ordenamos por burbuja
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
    while (i < v.size() &&  (distMts(obtenerPosicion(v[i]),p) >= u))
        i++;

    return (i < v.size());
}


nombre nombreEnGrilla (gps posicion, grilla g){

    double latitudPos = obtenerLatitud(posicion);
    double longitudPos = obtenerLongitud(posicion);
    nombre res = make_tuple(0, 0);

    for (int i = 0; i < g.size() && res == make_tuple(0, 0); ++i) {
        gps esqInf = obtenerEsquinaInferior(g[i]);
        gps esqSup = obtenerEsquinaSuperior(g[i]);

        if(obtenerLatitud(esqInf) <= latitudPos && latitudPos < obtenerLatitud(esqSup) &&
           obtenerLongitud(esqInf) <= longitudPos && longitudPos < obtenerLongitud(esqSup)){
            res = obtenerNombre(g[i]);
        }
    }
    return res;
}


double velocidad(tuple<tiempo,gps> p1 , tuple<tiempo,gps> p2){
    return ((distEnKM(obtenerPosicion(p1),obtenerPosicion(p2))) / ((obtenerTiempo(p2) - obtenerTiempo(p1)) / 3600));
}


vector<nombre> obtenerPalabra(recorrido t, grilla g)
{
    vector<nombre> palabra;
    for (int i = 0; i < t.size(); ++i)
        palabra.push_back(nombreEnGrilla(t[i],g));

    return palabra;
}


recorrido obtenerRecorrido(viaje v) {
    viaje vOrd = ordenarViajeBurbuja(v);

    recorrido r;
    for (int i = 0; i < vOrd.size(); i++) r.push_back(obtenerPosicion(vOrd[i]));
    return r;

}

int distanciaEntreCeldas(nombre n1, nombre n2){
    return abs(get<0>(n1) - get<0>(n2)) + abs(get<1>(n1) - get<1>(n2)) - 1;
}
//----------------------------------------------------------------------------//




void escribirGrilla(grilla g, string nombreArchivo){

    ofstream fout;
    fout.open(nombreArchivo);
    if(fout.fail()) {
        cout << "error" << endl;
    }
    else {
        //forzar la salida a precisión de 6 dígitos significativos
        //con 6 evitamos que se redondee el 5to dígito
        //siendo entonces los primeros 5 dígitos si o si correctos
        fout << std::fixed << setprecision(6);

        for (int i = 0; i < g.size(); ++i) {
            fout << obtenerLatitud(get<0>(g[i])) << '\t';
            fout << obtenerLongitud(get<0>(g[i])) << '\t';
            fout << obtenerLatitud(get<1>(g[i])) << '\t';
            fout << obtenerLongitud(get<1>(g[i])) << '\t';
            fout << "(" << get<0>(obtenerNombre(g[i])) << "," << get<1>(obtenerNombre(g[i])) << ")" << endl;
        }
        fout.close();
    }
}

void escribirRecorridos(vector<recorrido> recorridos, string nombreArchivo){

    ofstream fout;
    fout.open(nombreArchivo);
    if(fout.fail()){
        cout << "error" << endl;
    }
    else {
        fout << std::fixed << setprecision(6);

        for (int i = 0; i < recorridos.size(); ++i) {
            for (int j = 0; j < recorridos[i].size(); ++j) {
                fout << i << '\t';
                fout << obtenerLatitud(recorridos[i][j]) << '\t';
                fout << obtenerLongitud(recorridos[i][j]) << endl;
            }
        }
        fout.close();
    }
}

/*****************************+***** EJERCICIO excesoDeVelocidad **********************************/
bool excesoDeVelocidad(viaje v) {
    //ordenar viaje es O(n^2)
    v = ordenarViajeBurbuja(v);

    int i = 1;
    while( i < v.size() && velocidad(v[i-1],v[i]) < 80.0 ) i++;
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
    //ordenar viaje es O(n^2)
    v = ordenarViajeBurbuja(v);

    distancia d = 0.0;
    for (int i = 1; i < v.size(); i++)
        d += distEnKM(obtenerPosicion(v[i]), obtenerPosicion(v[i-1]));
    return d;
}

/***************************************** EJERCICIO flota ***************************************/
int flota(vector<viaje> f, tiempo t0, tiempo tf) {
    int res = 0;

    for (int i = 0; i < f.size(); i++)
        if (viajeEnFranjaHoraria(f[i], t0, tf))
            res++;

    return res;
}

/************************************ EJERCICIO recorridoCubierto *******************************/
vector<gps> recorridoNoCubierto(viaje v, recorrido r, distancia u) {
    recorrido res;

    for (int i = 0; i < r.size(); ++i) {
        if(!puntoCubierto(v, u, r[i]))
            res.push_back(r[i]);
    }
    return res;
}

/************************************** EJERCICIO construirGrilla *******************************/
grilla construirGrilla(gps esq1, gps esq2, int n, int m) {
    grilla gOut;

    double latEsq1 = obtenerLatitud(esq1);
    double longEsq1 = obtenerLongitud(esq1);

    double deltaLat = fabs(latEsq1 - obtenerLatitud(esq2));
    double deltaLong = fabs(longEsq1 - obtenerLongitud(esq2));

    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++)
        {
            gps e1 = puntoGps(latEsq1 + (deltaLat / n) * (i-1), longEsq1 + (deltaLong / m) * (j-1));
            gps e2 = puntoGps(latEsq1 + (deltaLat / n) * i, longEsq1 + (deltaLong / m) * j);

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