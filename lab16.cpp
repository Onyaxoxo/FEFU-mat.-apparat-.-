#include <iostream>
#include <cstdlib> 
#include <stdio.h>
#include <ctime> 
#include <cmath>
#include <fstream>

#define PI 3.14159265
#define E  2.71828183

#define N 100
using namespace std;


void InitializationX(float x[]) {

    for (int i = 0; i < N; i++) {
        x[i] = (float)(-50 + rand() % 100)/10;
    }

}

void InitializationFx(float fx[], float x[], float M, float Ot) {

    for (int i = 0; i < N; i++) { 
       fx[i] = ( 1 / ( Ot * sqrt( 2 * PI)) ) * pow( E, (-1 * pow((x[i] - M), 2) / (2 * pow(Ot, 2))) );
    }
}

void PrintArray(float a[]) {

    for (int i = 0; i < N; i++) {
        if (i % 25 == 0) cout << endl;
        printf("%.3f ", a[i] );
    }

}

void PrintArray2(float f[], float x[]) {
    
    ofstream outLab("lab.txt", ios::out);

    for (int i = 0; i < N; i++) {
        printf("%.3f \t\t %.3f\n", x[i], f[i] );
        outLab << x[i] << "\t" << f[i] << endl;
    }

}

void PrintArray3(float f1[], float f2[], float f3[], float f4[], float x[]) {
    
    ofstream outLab("lab.txt", ios::out);

    for (int i = 0; i < N; i++) {
        //printf("%.3f \t\t %.3f\n", x[i], f[i] );
        outLab << x[i] << "\t" << f1[i] << "\t" << f2[i] << "\t" << f3[i] << "\t" << f4[i] << endl;
    }

}


void SortArray(float fx[], float x[]) {

    float temp; // временная переменная для обмена элементов местами

    // Сортировка массива пузырьком
    for (int i = 0; i < N - 1; i++) {
        for (int j = 0; j < N - i - 1; j++) {
            if (x[j] > x[j + 1]) {
                // меняем элементы местами
                temp = x[j];
                x[j] = x[j + 1];
                x[j + 1] = temp;

                temp = fx[j];
                fx[j] = fx[j + 1];
                fx[j + 1] = temp;
            }
        }
    }

}

void SortArray2(float f1[], float f2[], float f3[], float f4[], float x[]) {

    float temp; // временная переменная для обмена элементов местами

    // Сортировка массива пузырьком
    for (int i = 0; i < N - 1; i++) {
        for (int j = 0; j < N - i - 1; j++) {
            if (x[j] > x[j + 1]) {
                // меняем элементы местами
                temp = x[j];
                x[j] = x[j + 1];
                x[j + 1] = temp;

                temp = f1[j]; f1[j] = f1[j + 1]; f1[j + 1] = temp;
                temp = f2[j]; f2[j] = f2[j + 1];  f2[j + 1] = temp;
                temp = f3[j]; f3[j] = f3[j + 1];  f3[j + 1] = temp;
                temp = f4[j]; f4[j] = f4[j + 1];  f4[j + 1] = temp;         
            }
        }
    }

}


int main() {
    srand(static_cast<unsigned int>(time(0)));
    cout.precision(3);

    float M; // мат ожидание
    float Ot; // стандартное отклонение
    cout << "Введите входные параметры : " << endl;
    cout << "Мат. ожидание = ";
    cin >> M;

    cout << "Стандартное откл. = ";
    cin >> Ot;

    float x[N]; 
    InitializationX(x);

    float fx[N]; 
    InitializationFx(fx, x, M, Ot);

    /*
    cout << "\nX :";
    PrintArray(x);

    cout << "\n\nFx:";
    PrintArray(fx);

    cout << endl << endl;
    SortArray(fx,x);
    PrintArray2(fx, x);
    */

    float fx2[N], fx3[N], fx4[N];
    InitializationFx(fx2, x, 0, 0.2);
    InitializationFx(fx3, x, 0, 5);
    InitializationFx(fx4, x, -2, 0.5);
    SortArray2(fx, fx2, fx3, fx4, x);
    PrintArray3(fx, fx2, fx3, fx4, x);
    return 0;

}