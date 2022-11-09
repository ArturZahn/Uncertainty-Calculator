#ifndef UCALC_H
#define UCALC_H

#include <cstring>
#include <iostream>
#include <math.h>

using namespace std;

// #define typeCalc long double
#define typeCalc double
// #define typeCalc float

class uVal {
public:
    typeCalc v,u;
    uVal ();
    uVal (typeCalc,typeCalc);
    uVal (typeCalc,typeCalc,int);
    // uVal (typeCalc,typeCalc,char*);
    // uVal (typeCalc,typeCalc,int,char*);
    uVal operator + (uVal);
    uVal operator - (uVal);
    uVal operator * (uVal);
    uVal operator * (typeCalc);
    uVal operator / (uVal);
    uVal operator / (typeCalc);
    uVal operator ^ (typeCalc);

    string str();
    string stra();
    void print();
    void printa();
    void print(string);
    void printa(string);
    void saveRounded();
    uVal getRounded();

    // units handling
    
    #define NUMERATOR 0
    #define DENOMINATOR 1

    // int nOfNumerators;
    // int nOfDenominator;
    // char** numerator;
    // char** denominator;
    int nOfUnits[2];
    char** units[2];

    void _initUnit();
    char* getUnit();
    void addUnit(char*, int);
    void _addUnit(char*, int);
    // void _removeRepUnits();
    int* _searchUnit(char*);
    int _coutUnit(char*,int);
    void _removeUnit(int n, int where);
    void _printUnits();
};

#define printuv(val) (val).print(# val)
#define printsuv(val, str) (val).print(str)
#define printuva(val) (val).printa(# val)
#define printsuva(val, str) (val).printa(str)

#define printv(val) _printv(val, # val)
#define printsv(val, str) _printv(val, str)

typeCalc roundTo(float, int);
int correctNumbDecimalPlaces(float);

void _printv(typeCalc, const char *);

uVal sin(uVal p);
uVal cos(uVal p);
// uVal log(uVal p, typeCalc c);
uVal ln(uVal p);

typeCalc DegToRad(typeCalc);
typeCalc RadToDeg(typeCalc);

uVal DegToRad(uVal);
uVal RadToDeg(uVal);


///////////
// uVal array conversions
#define uValArrayToVArray(arr) _uValArrayToVArray(sizeof(arr)/sizeof((arr)[0]), (arr))
typeCalc* _uValArrayToVArray(int, uVal*);
#define uValArrayToUArray(arr) _uValArrayToUArray(sizeof(arr)/sizeof((arr)[0]), (arr))
typeCalc* _uValArrayToUArray(int, uVal*);

#define VAndUArrayTouValArray(arr1,arr2) _VAndUArrayTouValArray(sizeof(arr1)/sizeof((arr1)[0]),(arr1),(arr2));
uVal* _VAndUArrayTouValArray(int,typeCalc*,typeCalc*);
#define uValArray(arr1) _VAndUArrayTouValArray(sizeof(arr1)/sizeof((arr1)[0]),(arr1));
uVal* _VAndUArrayTouValArray(int, typeCalc[][2]);
uVal* _VAndUArrayTouValArray(int, const typeCalc[][2]);
///////////

#define valorMedio(arr) _valorMedio(arr, sizeof(arr)/sizeof(arr[0]))
typeCalc _valorMedio(typeCalc values[], int size);

#define desvioMedio(arr) _desvioMedio(arr, sizeof(arr)/sizeof(arr[0]))
typeCalc _desvioMedio(typeCalc values[], int size);

#define desvioPadrao(arr) _desvioPadrao(arr, sizeof(arr)/sizeof(arr[0]))
typeCalc _desvioPadrao(typeCalc values[], int size);


// #define medidaMedia_desvioPadrao(arr) _medidaMedia_desvioPadrao((arr), sizeof(arr)/sizeof(arr[0]))
#define medidaMedia_desvioPadrao(arr) _medidaMedia_desvioPadrao((arr), sizeof(arr)/sizeof(arr[0]), #arr)
uVal _medidaMedia_desvioPadrao(typeCalc values[], int size);
uVal _medidaMedia_desvioPadrao(typeCalc values[], int size, string varName);
uVal _medidaMedia_desvioPadrao(uVal values[], int size);
uVal _medidaMedia_desvioPadrao(uVal values[], int size, string varName);

// #define medidaMedia_desvioMedio(arr) _medidaMedia_desvioMedio(arr, sizeof(arr)/sizeof(arr[0]))
#define medidaMedia_desvioMedio(arr) _medidaMedia_desvioMedio(arr, sizeof(arr)/sizeof(arr[0]), #arr)
uVal _medidaMedia_desvioMedio(typeCalc values[], int size);
uVal _medidaMedia_desvioMedio(uVal values[], int size);



// comparacao entre valores
#define compararValores(a, b) _campararValores((a), # a, (b), # b)
void _campararValores(uVal, string, uVal, string);
void _campararValores(typeCalc, string, uVal, string);
void _campararValores(uVal, string, typeCalc, string);
// calcular k
typeCalc calcKBetweenValues(uVal, uVal);
typeCalc calcKBetweenValues(typeCalc, uVal);
typeCalc calcKBetweenValues(uVal, typeCalc);



#define minimosQuadrados(arr1, arr2, ca, cb) _minimosQuadrados(arr1, arr2, sizeof(arr1)/sizeof(arr1[0]), (ca), (cb))
void _minimosQuadrados(typeCalc x[], typeCalc y[], int size, uVal *pcoefA, uVal *pcoefB);



const typeCalc t_tabelado_95[] = {
    0,
    12.706,
    4.303,
    3.183,
    2.776,
    2.571,
};


#endif