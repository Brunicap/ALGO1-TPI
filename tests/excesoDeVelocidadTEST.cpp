#include "../solucion.h"
#include "../auxiliares.h"
#include "gtest/gtest.h"

using namespace std;


TEST(excesoDeVelocidadTEST, viajeOrdenadoSinExceso){
    gps p1 = puntoGps(-33, -34);
    gps p2 = desviarPunto(p1, 10, 0);
    gps p3 = desviarPunto(p2, 10, 0);

    viaje v = {medicion(1.5, p1),
               medicion(2.5, p2),
               medicion(3.5, p3)};

    bool res = excesoDeVelocidad(v);

    EXPECT_EQ(res,false);
}

TEST(excesoDeVelocidadTEST, viajeOrdenadoConExceso){
    gps p1 = puntoGps(-33, -34);
    gps p2 = desviarPunto(p1, 4000, 0);
    gps p3 = desviarPunto(p2, 2000, 0);

    viaje v = {medicion(1.5, p1),
               medicion(1.6, p2),
               medicion(1.7, p3)};

    bool res = excesoDeVelocidad(v);

    EXPECT_EQ(res,true);
}

TEST(excesoDeVelocidadTEST, viajeDesordenadoSinExceso){
    gps p1 = puntoGps(-33, -34);
    gps p2 = desviarPunto(p1, 10, 0);
    gps p3 = desviarPunto(p2, 10, 0);

    viaje v = {medicion(2.5, p2),
               medicion(1.5, p1),
               medicion(3.5, p3)};

    bool res = excesoDeVelocidad(v);

    EXPECT_EQ(res,false);
}

TEST(excesoDeVelocidadTEST, viajeDesordenadoConExceso){
    gps p1 = puntoGps(-33, -34);
    gps p2 = desviarPunto(p1, 1000, 0);
    gps p3 = desviarPunto(p2, 1000, 0);

    viaje v = {medicion(1.6, p2),
               medicion(1.5, p1),
               medicion(1.7, p3)};

    bool res = excesoDeVelocidad(v);

    EXPECT_EQ(res,true);
}

TEST(excesoDeVelocidadTEST, viajeParado){
    gps p1 = puntoGps(-33, -34);

    viaje v = {medicion(1.1, p1),
               medicion(1.5, p1),
               medicion(1.2, p1),
               medicion(1.9, p1)};
    bool res = excesoDeVelocidad(v);

    EXPECT_EQ(res,false);
}

TEST(excesoDeVelocidadTEST, viajeVaYVuelveSinExceso){
    gps p1 = puntoGps(-33, -34);
    gps p2 = desviarPunto(p1, 10, 0);
    gps p3 = p1;

    viaje v = {medicion(2.5, p2),
               medicion(1.5, p1),
               medicion(3.5, p3)};

    bool res = excesoDeVelocidad(v);

    EXPECT_EQ(res,false);
}

TEST(excesoDeVelocidadTEST, viajeVaYVuelveConExceso){
    gps p1 = puntoGps(-33, -34);
    gps p2 = desviarPunto(p1, 1000, 0);
    gps p3 = p1;

    viaje v = {medicion(1.6, p2),
               medicion(1.5, p1),
               medicion(1.7, p3)};

    bool res = excesoDeVelocidad(v);

    EXPECT_EQ(res,true);
}
