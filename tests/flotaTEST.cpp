#include "../solucion.h"
#include "../auxiliares.h"
#include "gtest/gtest.h"

using namespace std;

TEST(flotaTEST, flotaVacio){
    tiempo t0 = 5.0;
    tiempo tf = 10.0;

    vector<viaje> f = {};

    int res = flota(f,t0,tf);

    EXPECT_EQ(res,0);
}

TEST(flotaTEST, ningunViajeEnLaFranja){
    tiempo t0 = 5.0;
    tiempo tf = 10.0;

    gps p1 = puntoGps(-33, -34);
    gps p2 = desviarPunto(p1, 2000, 0);
    gps p3 = desviarPunto(p2, 2000, 0);

    viaje v1 = {medicion(1.5, p1),
               medicion(1.6, p2),
               medicion(1.7, p3)};

    viaje v2 = {medicion(2.0,p1),
                medicion(2.1,p2),
                medicion(2.2,p3)};

    viaje v3 = {medicion(3.5,p1),
                medicion(3.6,p2),
                medicion(4.0,p3)};

    vector<viaje> f = {v1,v2,v3};

    int res = flota(f,t0,tf);

    EXPECT_EQ(res,0);
}

TEST(flotaTEST, algunViajeEnLaFranja){
    tiempo t0 = 3.0;
    tiempo tf = 10.0;

    gps p1 = puntoGps(-33, -34);
    gps p2 = desviarPunto(p1, 2000, 0);
    gps p3 = desviarPunto(p2, 2000, 0);

    viaje v1 = {medicion(1.5, p1),
                medicion(1.6, p2),
                medicion(1.7, p3)};

    viaje v2 = {medicion(2.0,p1),
                medicion(2.1,p2),
                medicion(2.2,p3)};

    viaje v3 = {medicion(3.5,p1),
                medicion(3.6,p2),
                medicion(4.0,p3)};

    vector<viaje> f = {v1,v2,v3};

    int res = flota(f,t0,tf);

    EXPECT_EQ(res,1);
}

TEST(flotaTEST, todoViajeEnLaFranja){
    tiempo t0 = 1.0;
    tiempo tf = 10.0;

    gps p1 = puntoGps(-33, -34);
    gps p2 = desviarPunto(p1, 2000, 0);
    gps p3 = desviarPunto(p2, 2000, 0);

    viaje v1 = {medicion(1.5, p1),
                medicion(1.6, p2),
                medicion(1.7, p3)};

    viaje v2 = {medicion(2.0,p1),
                medicion(2.1,p2),
                medicion(2.2,p3)};

    viaje v3 = {medicion(3.5,p1),
                medicion(3.6,p2),
                medicion(4.0,p3)};

    vector<viaje> f = {v1,v2,v3};

    int res = flota(f,t0,tf);

    EXPECT_EQ(res,3);
}
