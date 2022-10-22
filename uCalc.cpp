#include "uCalc.h"

uVal::uVal() {
    _initUnit();
    v = 0;
    u = 0;
}

uVal::uVal(typeCalc a, typeCalc b) {
    _initUnit();
    v = a;
    u = abs(b);
}

uVal::uVal(typeCalc a,typeCalc b, int powerOfTen) {
    _initUnit();
    typeCalc p = pow(10, powerOfTen);
    v = a*p;
    u = abs(b)*p;
}

// uVal::uVal(typeCalc,typeCalc,char*)
// {

// }

// uVal::uVal(typeCalc,typeCalc,int,char*)
// {

// }


string uVal::str()
{
    return to_string(v) + " " + (char)241 + " " + to_string(u);
}

string uVal::stra()
{
    int cnDecPlac;
    if(u == 0) cnDecPlac = 0;
    else cnDecPlac = correctNumbDecimalPlaces(roundTo(u, correctNumbDecimalPlaces(u)));

    char formt[10];
    char formatedStr[50];
    if(cnDecPlac < 0)
    {
        sprintf (formatedStr, "%.0f %c %.0f", roundTo(v, cnDecPlac), (char)241, roundTo(u, cnDecPlac));
    }
    else
    {
        sprintf (formt, "%%.%df %c %%.%df", cnDecPlac, (char)241, cnDecPlac);
        sprintf (formatedStr, formt, v, u);
    }

    for (int i = 0; i < strlen(formatedStr); i++)
    {
        if(formatedStr[i] == '.') formatedStr[i] = ',';
    }
    
    
    return formatedStr;
    // return to_string(v) + " " + (char)241 + " " + to_string(u);
}

void uVal::print()
{
    cout << str() << endl;
}

void uVal::print(string name)
{
    cout << name << ": " << str() << endl;
}

void uVal::printa()
{
    cout << stra() << endl;
}

void uVal::printa(string name)
{
    cout << name << ": " << stra() << endl;
}

uVal uVal::operator+ (uVal p) {
    uVal temp;
    temp.v = v + p.v;
    temp.u = abs(u) + abs(p.u);
    return (temp);
}

uVal uVal::operator- (uVal p) {
    uVal temp;
    temp.v = v - p.v;
    temp.u = abs(u) + abs(p.u);
    return (temp);
}

uVal uVal::operator* (uVal p) {
    uVal temp;
    temp.v = v * p.v;
    temp.u = abs(p.v*u) + abs(v*p.u);
    return (temp);
}

uVal uVal::operator* (typeCalc p) {
    uVal temp;
    temp.v = v * p;
    temp.u = abs(u * p);
    return (temp);
}

uVal uVal::operator/ (uVal p) {
    uVal temp;
    temp.v = v / p.v;
    temp.u = (abs(p.v*u) + abs(v*p.u))/abs(p.v*p.v);
    return (temp);
}

uVal uVal::operator/ (typeCalc p) {
    uVal temp;
    temp.v = v / p;
    temp.u = abs(u/p);
    return (temp);
}

uVal uVal::operator^ (int p) {
    uVal temp;
    temp.v = pow(v, p);
    temp.u = abs(p*pow(v, p-1)*u);
    return (temp);
}

void uVal::_initUnit()
{
    this->nOfUnits[0] = 0;
    this->nOfUnits[1] = 0;   
}

void push10(char* strBase, int* strBaseQtd, char* strAdd)
{
    int strBaseLen = strlen(strBase);
    int strAddLen = strlen(strAdd);

    // printf("p10:  base:%d add:%d total:%d baseQtd:%d", strBaseLen, strAddLen, strBaseLen+strAddLen+1, *strBaseQtd);

    if(strBaseLen+strAddLen+1 > *strBaseQtd)
    {
        // printf(" muito grande");
        while(strBaseLen+strAddLen+1 > *strBaseQtd) (*strBaseQtd) += 10;
        realloc(strBase, sizeof(char) * (*strBaseQtd));
    }
    // printf("\n");

    strcpy(strBase+strBaseLen, strAdd);
}

char* uVal::getUnit()
{
    int strLen = 0;
    char* txtUnit = (char*) malloc(sizeof(char) * strLen);
    
    // for (int i = 0; i < 8000; i++)
    // {
    //     printf("%d'%c'", i, i);
    // }
    
    char powerOfTwo[2];
    powerOfTwo[0] = 253;
    powerOfTwo[1] = '\0';

    for (int where = 0; where < 2; where++)
    {
        if(where != 0) push10(txtUnit, &strLen, "/");
        int jaFoi[this->nOfUnits[where]];
        for(int i = 0; i < this->nOfUnits[where]; i++) jaFoi[i] = 0;

        for (int i = 0; i < this->nOfUnits[where]; i++)
        {
            printf("vendo %2d-'%s' ", i, this->units[where][i]);


            if(jaFoi[i] == 0)
            {
                if(i != 0) push10(txtUnit, &strLen, ".");

                for (int j = 0; j < this->nOfUnits[where]; j++)
                {
                    if(strcmp(this->units[where][j], units[where][i]) == 0) jaFoi[j]++;
                }

                int count = this->_coutUnit(this->units[where][i], where);
                printf("'%d'", count);
                push10(txtUnit, &strLen, this->units[where][i]);
                if(count > 2)
                {
                    char powerStr[15];
                    itoa(count, powerStr, 10);
                    push10(txtUnit, &strLen, "^");
                    push10(txtUnit, &strLen, powerStr);
                }
                else if(count == 2)
                {
                    push10(txtUnit, &strLen, powerOfTwo);
                }
                
            }
            printf("\n");
        }   
        printf("\n\n");
    }
    // printf("final: '%s'\n", txtUnit);

    return txtUnit;
}

void uVal::addUnit(char* unit, int where)
{
    int* cmp = this->_searchUnit(unit);
    
    printf("\"%s\" ", unit);
    if(cmp[0] == -1)
    {
        printf("Ok\n");
        this->_addUnit(unit, where);
        return;
    }

    if(where != cmp[0])
    {
        printf("no lado oposto (%d-%d)\n", cmp[0], cmp[1]);
        this->_removeUnit(cmp[1], cmp[0]);
        return;
    }

    printf("no mesmo lado (%d-%d)\n", cmp[0], cmp[1]);
    this->_addUnit(unit, where);
}

void uVal::_addUnit(char* unit, int where)
{
    this->nOfUnits[where]++;

    realloc(this->units[where], sizeof(char*)*this->nOfUnits[where]);

    int len = strlen(unit)+1;
    this->units[where][this->nOfUnits[where]-1] = (char*) malloc(len*sizeof(char));
    strcpy(this->units[where][this->nOfUnits[where]-1], unit);
}

// void uVal::_removeRepUnits()
// {
//     print("comparando:\n");
//     for(int i = 0; i < this->nOfUnits[0]; i++)
//     {
//         for (int j = 0; j < this->nOfUnits[1]; j++)
//         {
//             printf("%d/%d -> \"%s\" - \"%s\"\n", i, j, this->units[0][i], this->units[1][j]);
//         }
//     }
// }

void uVal::_removeUnit(int n, int where)
{
    free(this->units[where][n]);

    this->nOfUnits[where]--;

    for (int i = n; i < this->nOfUnits[where]; i++)
    {
        units[where][i] = units[where][i+1];
    }

    realloc(this->units[where], sizeof(char*)*this->nOfUnits[where]);
}

int* uVal::_searchUnit(char* unit)
{
    int* ret = (int*) malloc(sizeof(int)*2);

    for (int i = 0; i < this->nOfUnits[0]; i++)
    {
        ret[0] = 0;
        ret[1] = i;
        if(strcmp(this->units[0][i], unit) == 0) return ret;
    }
    for (int i = 0; i < this->nOfUnits[1]; i++)
    {
        ret[0] = 1;
        ret[1] = i;
        if(strcmp(this->units[1][i], unit) == 0) return ret;
    }

    ret[0] = -1;
    return ret;
}

int uVal::_coutUnit(char* unit, int where)
{
    int count = 0;
    for (int i = 0; i < this->nOfUnits[where]; i++)
    {
        if(strcmp(this->units[where][i], unit) == 0) count++;
    }

    return count;
}

void uVal::_printUnits()
{
    printf("\nUnidades:\n");
    for (int i = 0; i < this->nOfUnits[0]; i++) printf("%s ", this->units[0][i]);
    printf("\n----------------------\n");
    for (int i = 0; i < this->nOfUnits[1]; i++) printf("%s ", this->units[1][i]);
    printf("\n\n");
}




uVal sin(uVal p)
{
    uVal temp;
    temp.v = sin(p.v);
    temp.u = abs(cos(p.v)*p.u);
    return temp;
}

uVal cos(uVal p)
{
    uVal temp;
    temp.v = cos(p.v);
    temp.u = abs(sin(p.v)*p.u);
  
    return temp;
}


typeCalc roundTo(float value, int dec)
{
    float mult = pow(10, dec);
    return round(value*mult)/mult;
}

int correctNumbDecimalPlaces(float value)
{
    return ceil(-log10(value));
}

typeCalc _printv( typeCalc num, const char * name )
{
     std::cout << name << ": " << to_string(num) << std::endl;
}


typeCalc DegToRad(typeCalc val)
{
    return val*M_PI/180;
}
typeCalc RadToDeg(typeCalc val)
{
    return val*180/M_PI;
}

uVal DegToRad(uVal val)
{
    val.v = DegToRad(val.v);
    val.u = abs(DegToRad(val.u));
    return val;
}
uVal RadToDeg(uVal val)
{
    val.v = RadToDeg(val.v);
    val.u = abs(RadToDeg(val.u));
    return val;
}




typeCalc* _uValArrayToVArray(int n, uVal* uValArray)
{
    typeCalc* valuesArray = (typeCalc*)malloc(n*sizeof(typeCalc));

    for (int i = 0; i < n; i++)
    {
        valuesArray[i] = uValArray[i].v;
    }
    
    return valuesArray;
}

typeCalc* _uValArrayToUArray(int n, uVal* uValArray)
{
    typeCalc* valuesArray = (typeCalc*)malloc(n*sizeof(typeCalc));

    for (int i = 0; i < n; i++)
    {
        valuesArray[i] = uValArray[i].u;
    }
    
    return valuesArray;
}
uVal* _VAndUArrayTouValArray(int n, typeCalc* v,typeCalc* u)
{
    uVal* uValArray = (uVal*)malloc(n*sizeof(uVal));
    for (int i = 0; i < n; i++)
    {
        uValArray[i] = uVal(v[i], u[i]);
    }
    return uValArray;
}

uVal* _VAndUArrayTouValArray(int n, typeCalc vu[][2])
{
    uVal* uValArray = (uVal*)malloc(n*sizeof(uVal));
    for (int i = 0; i < n; i++)
    {
        uValArray[i] = uVal(vu[i][0], vu[i][1]);
    }
    return uValArray;
}

uVal* _VAndUArrayTouValArray(int n,const typeCalc vu[][2])
{
    uVal* uValArray = (uVal*)malloc(n*sizeof(uVal));
    for (int i = 0; i < n; i++)
    {
        uValArray[i] = uVal(vu[i][0], vu[i][1]);
    }
    return uValArray;
}



typeCalc _valorMedio(typeCalc values[], int size)
{
    typeCalc sum = 0;
    for (int i = 0; i < size; i++)
    {
        sum += values[i];
    }
    return sum/size;
}

typeCalc _desvioMedio(typeCalc values[], int size)
{
    typeCalc valMed = _valorMedio(values, size);
    typeCalc sum = 0;
    
    for (int i = 0; i < size; i++)
    {
        sum += abs(values[i]-valMed);
    }
    return sum/size;
}

typeCalc _desvioPadrao(typeCalc values[], int size)
{
    typeCalc valMed = _valorMedio(values, size);
    typeCalc sum = 0;
    
    for (int i = 0; i < size; i++)
    {
        sum += pow(values[i]-valMed, 2);
    }
    return sqrt(sum/(size-1));
}

uVal _medidaMedia_desvioPadrao(typeCalc values[], int size)
{
    printf("\nAtencao, calculo da medida media foi feito sem considerar as incertezas dos valores originais.\n\n");
    return uVal(_valorMedio(values, size), _desvioPadrao(values, size));
}

uVal _medidaMedia_desvioPadrao(uVal values[], int size)
{
    typeCalc* vs = _uValArrayToVArray(size, values);
    typeCalc* us = _uValArrayToUArray(size, values);

    typeCalc medUncert = _valorMedio(us, size);
    typeCalc desvPadrao = _desvioPadrao(vs, size);

    uVal finalValue;
    finalValue.v = _valorMedio(vs, size);

    if(medUncert > desvPadrao)
    {
        printf("\nAtencao, a media das incertezas foi usada como incerteza do valor calculado. Isso porque ela eh maior que o desvio padrao dos valores originais.\n\n");
        finalValue.u = medUncert;
    }
    else finalValue.u = desvPadrao;

    return finalValue;
}

uVal _medidaMedia_desvioMedio(typeCalc values[], int size)
{
    printf("\nAtencao, calculo da medida media foi feito sem considerar as incertezas dos valores originais.\n\n");
    return uVal(_valorMedio(values, size), _desvioMedio(values, size));
}

uVal _medidaMedia_desvioMedio(uVal values[], int size)
{
    typeCalc* vs = _uValArrayToVArray(size, values);
    typeCalc* us = _uValArrayToUArray(size, values);

    typeCalc medUncert = _valorMedio(us, size);
    typeCalc desvMedio = _desvioMedio(vs, size);

    uVal finalValue;
    finalValue.v = _valorMedio(vs, size);

    if(medUncert > desvMedio)
    {
        printf("\nAtencao, a media das incertezas foi usada como incerteza do valor calculado. Isso porque ela eh maior que o desvio medio dos valores originais.\n\n");
        finalValue.u = medUncert;
    }
    else finalValue.u = desvMedio;

    return finalValue;

    // return uVal(_valorMedio(values, size), _desvioMedio(values, size));
}


void _compararK(typeCalc k, string a_name, string b_name)
{
    printf("\n\nValores \"%s\" e \"%s\" ", a_name.c_str(), b_name.c_str());
    if(k <= 2) printf("sao equivalentes pois k = %lf que eh menor ou igual a 2\n\n", k);
    else if(k <= 3) printf("talvez sejam equivalentes pois k = %lf que eh menor ou igual a 3, porem eh maior que 2\n\n", k);
    else printf("nao sao equivalentes pois k = %lf que eh maior que 3\n\n", k);
}

void _campararValores(uVal a, string a_name, uVal b, string b_name)
{
    _compararK(calcKBetweenValues(a, b), a_name, b_name);
}

void _campararValores(typeCalc a, string a_name, uVal b, string b_name)
{
    _compararK(calcKBetweenValues(a, b), a_name, b_name);
}

void _campararValores(uVal a, string a_name, typeCalc b, string b_name)
{
    _compararK(calcKBetweenValues(a, b), a_name, b_name);
}

typeCalc calcKBetweenValues(uVal a, uVal b)
{
    return abs(a.v-b.v)/abs(a.u+b.u);
}

typeCalc calcKBetweenValues(typeCalc a, uVal b)
{
    return abs(a-b.v)/abs(b.u);
}

typeCalc calcKBetweenValues(uVal a, typeCalc b)
{
    return calcKBetweenValues(b, a);
}

void _minimosQuadrados(typeCalc x[], typeCalc y[], int size)
{
    #define columnsOfTable 8
    typeCalc tab[columnsOfTable][size], sum[columnsOfTable];

    for (int i = 0; i < columnsOfTable; i++) sum[i] = 0;

    typeCalc xMed = _valorMedio(x, size);
    typeCalc yMed = _valorMedio(y, size);
    
    for (int i = 0; i < size; i++)
    {
        tab[0][i] = x[i];
        tab[1][i] = y[i];
        tab[2][i] = tab[0][i]-xMed;
        tab[3][i] = pow(tab[0][i], 2);
        tab[4][i] = tab[2][i]*tab[1][i];
        tab[5][i] = pow(tab[2][i], 2);

        for (int j = 0; j < 6; j++)
        {
            sum[j] += tab[j][i];
        }
    }

    uVal coefA, coefB;
    typeCalc dispersaoMediaY;

    coefA.v = sum[4]/sum[5];
    coefB.v = yMed - (coefA.v*xMed);
    
    dispersaoMediaY = 0;
    for (int i = 0; i < size; i++)
    {
        dispersaoMediaY += pow((coefA.v*tab[0][i])+coefB.v-tab[1][i], 2);
    }
    dispersaoMediaY = sqrt(dispersaoMediaY/(size-2));
    
    coefA.u = dispersaoMediaY/sqrt(sum[5]);
    coefB.u = (sqrt(sum[3]/(size*sum[5])))*dispersaoMediaY;

    for (int i = 0; i < size; i++)
    {
        tab[6][i] = coefA.v*x[i] + coefB.v;
        tab[7][i] = pow(tab[6][i]-tab[1][i], 2);

        sum[6] += tab[6][i];
        sum[7] += tab[7][i];
    }
    
    
    // printf(" %15s", "Xi");
    // printf(" %15s", "Yi");
    // printf(" %15s", "Xi-Xm");
    // printf(" %15s", "Xi^2");
    // printf(" %15s", "(Xi-Xm)Yi");
    // printf(" %15s", "(Xi-Xm)^2");
    // printf(" %15s", "Yci");
    // printf(" %15s\n", "(Yci-Yi)^2");
    // for (int i = 0; i < size; i++)
    // {
    //     printf(" %15f", tab[0][i]);
    //     printf(" %15f", tab[1][i]);
    //     printf(" %15f", tab[2][i]);
    //     printf(" %15f", tab[3][i]);
    //     printf(" %15f", tab[4][i]);
    //     printf(" %15f", tab[5][i]);
    //     printf(" %15f", tab[6][i]);
    //     printf(" %15f\n", tab[7][i]);
    // }
    // printf(" %15f", sum[0]);
    // printf(" %15f", sum[1]);
    // printf(" %15f", sum[2]);
    // printf(" %15f", sum[3]);
    // printf(" %15f", sum[4]);
    // printf(" %15f", sum[5]);
    // printf(" %15f", sum[6]);
    // printf(" %15f\n", sum[7]);
    printf("%s", "Xi");
    printf("@%s", "Yi");
    printf("@%s", "Xi-Xm");
    printf("@%s", "Xi^2");
    printf("@%s", "(Xi-Xm)Yi");
    printf("@%s", "(Xi-Xm)^2");
    printf("@%s", "Yci");
    printf("@%s\n", "(Yci-Yi)^2");
    for (int i = 0; i < size; i++)
    {
        printf("%f", tab[0][i]);
        printf("@%f", tab[1][i]);
        printf("@%f", tab[2][i]);
        printf("@%f", tab[3][i]);
        printf("@%f", tab[4][i]);
        printf("@%f", tab[5][i]);
        printf("@%f", tab[6][i]);
        printf("@%f\n", tab[7][i]);
    }
    printf("%f", sum[0]);
    printf("@%f", sum[1]);
    printf("@%f", sum[2]);
    printf("@%f", sum[3]);
    printf("@%f", sum[4]);
    printf("@%f", sum[5]);
    printf("@%f", sum[6]);
    printf("@%f\n", sum[7]);

    printf("\nResultados:\n");

    printv(dispersaoMediaY);
    printuv(coefA);
    printuv(coefB);
    printf("\nResultados finais:\n");
    printuva(coefA);
    printuva(coefB);
    
}