#include "../solucion.h"
#include "../auxiliares.h"
#include "gtest/gtest.h"

using namespace std;

TEST(cantidadDeSaltosTEST, viajeOrdenadoSinSalto){
    gps p1 = puntoGps(0,0);
    gps p2 = puntoGps(1.5,0);
    gps p3 = puntoGps(1.5,1.5);

    viaje v = {medicion(1.5, p1),
               medicion(1.6, p2),
               medicion(1.7, p3)};

    int n = 3;
    int m = 3;
    gps esq1 = puntoGps(0,0);
    gps esq2 = puntoGps(3,3);
    grilla g = construirGrilla(esq1,esq2,n,m);
    vector<nombre> palabra = aPalabra(recorridoDeV(v),g);

    int res = cantidadDeSaltos(g,v);

    EXPECT_EQ(res,0);
}

TEST(cantidadDeSaltosTEST, viajeOrdenadoConSalto){
    gps p1 = puntoGps(0,0);
    gps p2 = puntoGps(2.5,0);
    gps p3 = puntoGps(1.5,1.5);

    viaje v = {medicion(1.5, p1),
               medicion(1.6, p2),
               medicion(1.7, p3)};

    int n = 3;
    int m = 3;
    gps esq1 = puntoGps(0,0);
    gps esq2 = puntoGps(3,3);
    grilla g = construirGrilla(esq1,esq2,n,m);

    int res = cantidadDeSaltos(g,v);

    EXPECT_EQ(res,1);
}

TEST(cantidadDeSaltosTEST, viajeDesordenadoSinSalto){
    gps p1 = puntoGps(0,0);
    gps p2 = puntoGps(1.5,0);
    gps p3 = puntoGps(1.5,1.5);

    viaje v = {medicion(1.6, p2),
               medicion(1.5, p1),
               medicion(1.7, p3)};

    int n = 3;
    int m = 3;
    gps esq1 = puntoGps(0,0);
    gps esq2 = puntoGps(3,3);
    grilla g = construirGrilla(esq1,esq2,n,m);

    int res = cantidadDeSaltos(g,v);

    EXPECT_EQ(res,0);
}

TEST(cantidadDeSaltosTEST, viajeDesordenadoConSalto){
    gps p1 = puntoGps(0,0);
    gps p2 = puntoGps(2.5,0);
    gps p3 = puntoGps(1.5,1.5);

    viaje v = {medicion(1.6, p2),
               medicion(1.5, p1),
               medicion(1.7, p3)};

    int n = 3;
    int m = 3;
    gps esq1 = puntoGps(0,0);
    gps esq2 = puntoGps(3,3);
    grilla g = construirGrilla(esq1,esq2,n,m);

    int res = cantidadDeSaltos(g,v);

    EXPECT_EQ(res,1);
}