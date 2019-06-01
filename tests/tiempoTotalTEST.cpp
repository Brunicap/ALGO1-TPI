#include "../solucion.h"
#include "../auxiliares.h"
#include "gtest/gtest.h"

using namespace std;

TEST(tiempoTotalTEST, viajeOrdenado){
    gps p1 = puntoGps(-33, -34);
    gps p2 = desviarPunto(p1, 2000, 0);
    gps p3 = desviarPunto(p2, 2000, 0);

    viaje v = {medicion(1.5, p1),
               medicion(1.6, p2),
               medicion(2.7, p3)};

    EXPECT_NEAR(tiempoTotal(v), 1.2, 0.01);
}

TEST(tiempoTotalTEST, viajeDesordenado){
    gps p1 = puntoGps(-33, -34);
    gps p2 = desviarPunto(p1, 2000, 0);
    gps p3 = desviarPunto(p2, 2000, 0);

    viaje v = {medicion(1.6, p2),
               medicion(1.5, p1),
               medicion(1.7, p3)};

    EXPECT_NEAR(tiempoTotal(v), 0.2, 0.01);
}

TEST(tiempoTotalTEST, viajeParado){
    gps p1 = puntoGps(-33, -34);

    viaje v = {medicion(1.1, p1),
               medicion(1.5, p1),
               medicion(1.2, p1),
               medicion(1.9, p1)};
    EXPECT_NEAR(tiempoTotal(v), 0.8, 0.01);
}

TEST(tiempoTotalTEST, viajeVaYVuelve){
    gps p1 = puntoGps(-33, -34);
    gps p2 = desviarPunto(p1, 2000, 0);
    gps p3 = p1;

    viaje v = {medicion(1.6, p2),
               medicion(1.5, p1),
               medicion(1.7, p3)};
    EXPECT_NEAR(tiempoTotal(v), 0.2, 0.01);
}