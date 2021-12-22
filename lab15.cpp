#include <iostream>
#include <cstdlib> 
#include <stdio.h>
#include <ctime> 
#include <cmath>
#include <fstream>

using namespace std;

int main() {
    srand(static_cast<unsigned int>(time(0)));
    ofstream outLab("lab.txt", ios::out);

    int k = 0; // пуассоновская случайная величина
    //float lamda = 4.3; //среднее число событий в ед времени
    float lamda;
    cout << "Введите лямба" << endl;
    cin >> lamda;

    float p = exp(-lamda);
    float x =  (float)(rand() % 100)/100;// случайная величина от [0; 1]
    cout << endl << "x = " << x << endl;

    cout << "k \t\t p" << endl;
    cout << k << " \t\t " << p << endl; 
    outLab << k << "\t" << p << endl;

    while (x > p) 
    {
        x -= p;
        k++;
        p *= lamda/k;
        cout << k << " \t\t " << p << endl; 
        outLab << k << "\t" << p << endl;
    }

    cout << "\nk = " << k << endl;
    cout << "p(k) = " << p << endl << endl;
    return 0;
}