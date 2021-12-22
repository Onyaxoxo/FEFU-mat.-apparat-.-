#include <iostream>
#include <cstdlib> 
#include <stdio.h>
#include <ctime> 
#include <cmath>
#include <string>

#define N 10000 //500 1000
using namespace std;


float getMath(int n[], int k){

    float M = 0;
    for (int i = 0; i < k; i++) {
        if (n[i] != 0) M += (i+1) * ((float)n[i]/N);
    }

    return M;
}

float getDispersion(int n[], int k, float M){

    float D = 0;
    for (int i = 0; i < k; i++) {
        if (n[i] != 0)  D += pow(((i+1) - M), 2) * ((float)n[i]/N);
    }

    return D;
}


int main() {
    srand(static_cast<unsigned int>(time(0)));
    /*
      * На отрезке AB длиной 20 см наугад отметили точку C. Какова вероятность, что она находится на расстоянии 
      * не более 9 см от точки A и не больше 15 см от точки B?
    */
    
    int ab = 20; // число событий
    int a = 9;
    int b = 15;
   
    int n[ab]; // число успешных событий

    float M; // мат ожидаение
    float D; // дисперсия

    int nP = 0; //число событий, входящих в интервал - [5;9] 
    for (int i = 0; i < ab; i++) n[i] = 0;

    for (int i = 0; i < N; i++) {

        int ind = rand() % 20;
        n[ind] +=1; 

        if ( (ind <= a) && (ind >= (ab - b)) ) nP +=1;
    }
  
    for (int i = 0; i < ab; i++) 
        if (n[i] != 0) cout << "x[" << i+1 << "] =\t " << i+1 << "\t\tn = " << n[i] << "\t p = " << (float)n[i]/N << endl; 
    
    float sum = 0;
    for (int i = 0; i < ab; i++) 
        if (n[i] != 0) sum += (float)n[i]/N;

    cout << "\t\t\t\tp(sum) = "<< sum << endl;

    M = getMath(n, ab);
    D = getDispersion(n, ab, M);
    
    printf("\nP[5-9] = %.3f", (float)nP/N);
    printf("\nM = %.3f", M);
    printf("\nD = %.3f", D);
    cout << endl << endl;

    //for (int i = 0; i < indLast; i++) cout << i << "\t\t" << (float)n[i]/N << endl;
 
}