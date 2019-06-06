#include "../solucion.h"
#include "../auxiliares.h"
#include "../ejemplos.h"
#include "gtest/gtest.h"
#include <fstream>

using namespace std;

TEST(SalidaTEST, escribirGrillaNombreDeArchivoValido){
    grilla g = construirGrilla(puntoGps(0.0, 0.0), puntoGps(1.0, 1.0), 1, 1);
    string str = "grillaWriteTest.csv";

    EXPECT_NO_FATAL_FAILURE(escribirGrilla(g, str));

    ifstream file;

    //abrir archivo
    file.open(str);
    EXPECT_TRUE(file.is_open());

    //probar que el archivo contiene las lineas correctas
    std::stringstream buffer;
    buffer << file.rdbuf();

    string fileStr = buffer.str();

    EXPECT_EQ(fileStr.compare("0.000000\t0.000000\t1.000000\t1.000000\t(1,1)\n"),0);
}

TEST(SalidaTEST, escribirGrillaNombreDeArchivoInvalido)
{
    grilla g = construirGrilla(CORDOBA_ESQ1, CORDOBA_ESQ2, 10, 10);
    string str = "";

    EXPECT_NO_FATAL_FAILURE(escribirGrilla(g, str));
}




TEST(SalidaTEST, escribirRecorridosNombreDeArchivoValido){
    vector<recorrido> rv = {{puntoGps(0.0, 0.0), puntoGps(1.0, 1.0)}, {puntoGps(0.0, 0.0), puntoGps(2.0, 2.0)}};

    string str = "recorridosWriteTest.csv";
    EXPECT_NO_FATAL_FAILURE(escribirRecorridos(rv, str));


    ifstream file;

    //abrir archivo
    file.open(str);
    EXPECT_TRUE(file.is_open());

    //probar que el archivo contiene las lineas correctas
    std::stringstream buffer;
    buffer << file.rdbuf();

    string fileStr = buffer.str();

    EXPECT_EQ(fileStr.compare("0\t0.000000\t0.000000\n"
                              "0\t1.000000\t1.000000\n"
                              "1\t0.000000\t0.000000\n"
                              "1\t2.000000\t2.000000\n"),0);
}

TEST(SalidaTEST, escribirRecorridosNombreDeArchivoInvalido)
{
    vector<recorrido> rv = {};
    string str = "";

    EXPECT_NO_FATAL_FAILURE(escribirRecorridos(rv, str));
}