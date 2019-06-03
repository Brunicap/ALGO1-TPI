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

TEST(aPalabraTEST, recorridoVacio){
    vector<gps> r;

    int n = 1;
    int m = 1;
    gps esq1 = puntoGps(0,0);
    gps esq2 = puntoGps(1,1);
    grilla g = construirGrilla(esq1,esq2,n,m);
    vector<nombre> res = aPalabra(r,g);

    EXPECT_EQ(res.size(),0);
    ASSERT_ELEMENTS(res,{});
}

TEST(aPalabraTEST, recorridoNoVacio){
    gps p1 = puntoGps(0,0);
    gps p2 = puntoGps(1.5,0);
    gps p3 = puntoGps(1.5,1.5);

    vector<gps> r = {p1,p2,p3};

    int n = 2;
    int m = 2;
    gps esq1 = puntoGps(0,0);
    gps esq2 = puntoGps(2,2);
    grilla g = construirGrilla(esq1,esq2,n,m);
    vector<nombre> res = aPalabra(r,g);

    EXPECT_EQ(res.size(),3);
    ASSERT_ELEMENTS(res,{make_tuple(1,1),make_tuple(2,1),make_tuple(2,2)});
}
