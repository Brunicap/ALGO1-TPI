#include "../solucion.h"
#include "../auxiliares.h"
#include "gtest/gtest.h"

template<typename T>
bool included(T elem, vector<T> container){
    for (int i = 0; i < container.size(); ++i) {
        if (container[i] == elem){return true;}
    }
    return false;
}

template<typename T>
void ASSERT_ELEMENTS(vector<T> container, vector<T> elems) {
    for(int i = 0; i < elems.size(); i++ ) {
        ASSERT_TRUE(included(elems[i], container));
    }

}

using namespace std;


TEST(construirGrillaTEST, grillaPequena){
    int n = 1;
    int m = 1;
    gps esq1 = puntoGps(0,0);
    gps esq2 = puntoGps(1,1);
    grilla res = construirGrilla(esq1,esq2,n,m);
    nombre name = make_tuple(1,1);
    celda c = make_tuple(puntoGps(0,0),puntoGps(1,1),name);

    EXPECT_EQ(res.size(),1);
    ASSERT_ELEMENTS(res,{c});
}

TEST(construirGrillaTEST, grillaMasGrande ){
    int n = 2;
    int m = 2;
    gps esq1 = puntoGps(0,0);
    gps esq2 = puntoGps(2,2);
    grilla res = construirGrilla(esq1,esq2,n,m);
    grilla g = {make_tuple(puntoGps(0,0),puntoGps(1,1),make_tuple(1,1)),
                make_tuple(puntoGps(0,1),puntoGps(1,2),make_tuple(1,2)),
                make_tuple(puntoGps(1,0),puntoGps(2,1),make_tuple(2,1)),
                make_tuple(puntoGps(1,1),puntoGps(2,2),make_tuple(2,2))};

    EXPECT_EQ(res.size(),4);
    ASSERT_ELEMENTS(res,g);
}
